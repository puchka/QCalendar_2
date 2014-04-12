#include "Table.h"

Table::Table(QWidget *parent)
    : QTableWidget(6, 7, parent)
{
    setFixedSize(208, 151);// taille de la Table
    resizeColumnsToContents();
    resizeRowsToContents();

    horizontalHeader() -> setResizeMode(QHeaderView::Fixed);
    verticalHeader() -> setResizeMode(QHeaderView::Fixed);
    horizontalHeader() -> setClickable(false);
    verticalHeader() -> setClickable(false);
    verticalHeader() -> setFixedWidth(21);
    horizontalHeader() -> setStyleSheet("background-color:#8397dc; border:none; ");
    verticalHeader() -> setStyleSheet("Background-color: #a6bb33; border:none;");
    setCornerButtonEnabled(false);      // Désactiver le bouton du coin droite en haut


    // On récupère la date actuelle
    date = QDate::currentDate();
    int mois = date.month() - 1;
    int annee = date.year();
    rang = funcPremierMois(mois, annee);

    repartirDate(rang, mois, annee);     // On repartit les dates dans les cases

    moisCourant = mois;
    anneeCourante = annee;

    //On n'affiche pas les grilles
    setShowGrid(false);

    // On Modifie les étiquette de l'entete horizontal
    QStringList h_labels;
    h_labels <<"S"<<"M" << "T" << "W" << "T" << "F" << "S";
    setHorizontalHeaderLabels(h_labels);

    // On Modifie les étiquette de l'entet verticale (un peu compliqué ;))
    QStringList v_labels;

    determineNumSemaine(v_labels, mois, annee);
    setVerticalHeaderLabels(v_labels);

    label = new Label(moisCourant, anneeCourante, parent);
    label->setStyleSheet("color: #56e5f6");

    listMois = new QComboBox(parent);
    QString months[12] = {"January", "February", "March", "April",
                        "May", "June", "July", "August",
                         "September", "October", "November", "December"};
    for (int i=0;i<12;++i)
    {
        listMois->addItem(months[i]);
    }
    listMois->setCurrentIndex(mois);
    listMois->move(55, 10);

    listAnnee = new QComboBox(parent);
    for (int i=1582;i<=2100;++i)
    {
        QString str;
        str.append(QString("%1").arg(i));
        listAnnee->addItem(str);
    }
    listAnnee->setCurrentIndex(annee-1582);
    listAnnee->move(155, 10);

    QObject::connect(listMois, SIGNAL(currentIndexChanged(int)), this, SLOT(changeMonth(int)));
    QObject::connect(listAnnee, SIGNAL(currentIndexChanged(int)), this, SLOT(changeYear(int)));

    QObject::connect(this, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(showOrganiseur(int,int)));
}

// Fonction qui repartit les dates dans la Table en connaissant le nombre de case vide au début
void Table::repartirDate(int premierMois, int mois, int annee)
{
    int finMoisAnnee[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,31};
    if (nbreJoursAnnee(annee)==366)
        finMoisAnnee[1]=29;


    // Mettre les jours dans la liste "dates"
    for(int i=0; i<42; i++)
    {
        if (inMonth(i, mois, annee))
        {
            QString text;
            text.append(QString("%1").arg(i-premierMois+1));

            dates.push_back(new Case(text, this));
            dates[i] -> setRank(i-premierMois+1, mois, annee);
            dates[i] -> setInMonth(i, mois, annee);
        }
        else if (i<premierMois)
        {
            int moisPrecedent, anneeMoisPrecedent;
            if (mois==0)
            {
                moisPrecedent=11;
                anneeMoisPrecedent=annee-1;
            }
            else
            {
                moisPrecedent=mois-1;
                anneeMoisPrecedent=annee;
            }
            QString text;
            int lab = finMoisAnnee[moisPrecedent]-premierMois+i+1;
            text.append(QString("%1").arg(lab));

            dates.push_back(new Case(text, this));
            dates[i] -> setRank(lab, moisPrecedent, anneeMoisPrecedent);
            dates[i] -> setInMonth(i, mois, annee);
        }
        else
        {
            int lab = i-premierMois-finMoisAnnee[mois]+1;
            QString text;
            text.append(QString("%1").arg(lab));

            dates.push_back(new Case(text, this));
            dates[i] -> setInMonth(i, mois, annee);
            int moisSuivant, anneeMoisSuivant;
            if (mois==11)
            {
                moisSuivant=0;
                anneeMoisSuivant=annee+1;
            }
            else
            {
                moisSuivant=mois+1;
                anneeMoisSuivant=annee;
            }
            dates[i] -> setRank(lab, moisSuivant, anneeMoisSuivant);
        }
    }

    // Placons maintenant les éléments de la table
    // Avec les signaux de surbrillance
    int ligne = 0;
    for(int j = 0; j<42; j++)  // parcours des dates
    {
        setCellWidget(ligne, dates[j]->getRank(), dates[j]);

        //mise en evidence des dimanches
        if(!(dates[j]->getRank()))
        {
            dates[j] -> setStyleSheet("background-color:#b572ff;"
                                      "padding-left: 5px; border:none;");
        }

        // Les jours des autres mois sont grisés
        if (!dates[j]->getInMonth() || (j<19 && mois==9 && annee==1582))
            dates[j]->setStyleSheet("color: #dddddd; padding-left: 5px;"
                                    "border:none;");

        if ((dates[j] -> getRank())==6)              // Si on atteint la 7 ème colonne...
            ligne ++;                            // ... et on passe à la ligne

    }
    // Connexion des signaux et des slots
    QObject::connect(this, SIGNAL(cellClicked(int, int)), this, SLOT(caseClicked(int, int)));

    // colorer le jour actuelle
    Case * actuelle=dates[premierMois+date.day()-1];
    actuelle->setStyleSheet("background-color:#bcd977 ;color:blue; padding-left: 5px;"
                            "border:none;");
}


// Nombre de jours dans une annee
int Table::nbreJoursAnnee(int annee)
{
    if ((annee % 4 == 0 && annee % 100 != 0)||(annee % 100 == 0 && annee % 400 ==0))
      return 366;
    else
      return 365;

}

// Nombre de jours entre le premier du mois et le 1er janvier
int Table::nbreJoursMoisAnnee(int mois, int annee)
{
    int nbreJours = 0;
    int finMois[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (nbreJoursAnnee(annee)==366)
        finMois[1] = 29;
    for(int i=0; i<mois; i++)
        nbreJours+=finMois[i];

    return nbreJours;
}

// Nombre de jour entre le 1er du mois et le 1er janvier 2012
int Table::nbreJoursMoisAnnee2012(int mois, int annee)
{
    int nbreJours = 0;
    if(annee>=2012)
    {
        for(int i_annee = 2012; i_annee<annee; i_annee++)
        {
            nbreJours+=nbreJoursAnnee(i_annee);
        }
        nbreJours += nbreJoursMoisAnnee(mois, annee);
    }
    else
    {
        for(int i_annee = annee; i_annee<2012; i_annee++)
        {
            nbreJours+=nbreJoursAnnee(i_annee);
        }
        nbreJours -= nbreJoursMoisAnnee(mois, annee);
    }

    return nbreJours;
}

// Rang du premier jour du mois dans la semaine
int Table::funcPremierMois(int mois, int annee)
{
    int rang;
    if(annee>=2012)
        rang = nbreJoursMoisAnnee2012(mois, annee) % 7;
    else
        rang = (7 - nbreJoursMoisAnnee2012(mois,annee)%7)%7;

    return rang;
}

// Determination des numeros de semaines pour un mois donné d'une année
void Table::determineNumSemaine(QStringList &v_labels, int mois, int annee)
{
    int finMois[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (nbreJoursAnnee(annee)==366)
        finMois[1] = 29;
    int tabSemaine[55] = {0};
    int indxNumSemaine[12];          // indexes du numero de semaine du debut du mois dans le tableau
    indxNumSemaine[0] = 0;
    int ligne;
    for(int k=0; k<11; k++)
    {
        if(k<=10)
            ligne = (Table::funcPremierMois(k, annee) + finMois[k] +
                     (7-Table::funcPremierMois(k+1, annee)))/7;
        else
            ligne = (Table::funcPremierMois(k, annee) + finMois[k] +
                     7 - Table::funcPremierMois(0, annee+1)) /7;

        indxNumSemaine[k+1] = indxNumSemaine[k]+ligne-1;
    }

    if (Table::funcPremierMois(0, annee)<=4)
    {
        tabSemaine[0] = 1;
        for(int i = 1; i<52; i++)
            tabSemaine[i] = i+1;
    }
    else
    {
        tabSemaine[0] = nbreCaseAnnee(annee - 1)/7;
        for(int i =1; i<=52; i++)
            tabSemaine[i] = i;
    }

    if(Table::funcPremierMois(0, annee+1)>4)
    {
        tabSemaine[52] = Table::nbreCaseAnnee(annee)/7;
        tabSemaine[53] = 1;
        tabSemaine[54] = 2;
    }
    else if (!Table::funcPremierMois(0, annee+1)){
        tabSemaine[52] = 52;
        tabSemaine[53] = 1;
        tabSemaine[54] = 2;
    }
    else
    {
        tabSemaine[52] = 1;
        tabSemaine[53] = 2;
        tabSemaine[54] = 3;
    }

    for(int j = indxNumSemaine[mois] ; j<indxNumSemaine[mois]+6; j++)
    {
        QString chaine;
        chaine.append(QString("%1").arg(tabSemaine[j]));
        v_labels << chaine;
    }
}

int Table::nbreCaseAnnee(int annee)
{
    int finMois[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (nbreJoursAnnee(annee)==366)
        finMois[1] = 29;

    int nbreCase;
    if(Table::funcPremierMois(0, annee)<=4)
        nbreCase = Table::nbreJoursAnnee(annee) + Table::funcPremierMois(0, annee) +
                   (7-Table::funcPremierMois(0, annee+1));
    else
        nbreCase = Table::nbreJoursAnnee(annee) + Table::funcPremierMois(0, annee) -
                   Table::funcPremierMois(0, annee+1);

    return nbreCase;
}

void Table::changerMois(int mois, int annee)
{
    int premierMois = funcPremierMois(mois, annee);
    int finMoisAnnee[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,31};
    if (nbreJoursAnnee(annee)==366)
        finMoisAnnee[1]=29;


    // Mettre les jours dans la liste "dates"
    for(int i=0; i<42; i++)
    {
        if (inMonth(i, mois, annee))
        {
            QString text;
            text.append(QString("%1").arg(i-premierMois+1));

            dates[i] = new Case(text, this);
            dates[i] -> setRank(i-premierMois+1, mois, annee);
            dates[i] -> setInMonth(i, mois, annee);
            dates[i]->setStyleSheet("background-color: white; padding-left: 5px;"
                                    "border: none;");
        }
        else if (i<premierMois)
        {
            int moisPrecedent, anneeMoisPrecedent;
            if (mois==0)
            {
                moisPrecedent=11;
                anneeMoisPrecedent=annee-1;
            }
            else
            {
                moisPrecedent=mois-1;
                anneeMoisPrecedent=annee;
            }
            QString text;
            int lab = finMoisAnnee[moisPrecedent]-premierMois+i+1;
            text.append(QString("%1").arg(lab));

            dates[i] = new Case(text, this);
            dates[i] -> setRank(lab, moisPrecedent, anneeMoisPrecedent);
            dates[i] -> setInMonth(i, mois, annee);
        }
        else
        {
            QString text;
            int lab = i-premierMois-finMoisAnnee[mois]+1;
            text.append(QString("%1").arg(lab));

            dates[i] = new Case(text, this);
            dates[i] -> setInMonth(i, mois, annee);
            int moisSuivant, anneeMoisSuivant;
            if (mois==11)
            {
                moisSuivant=0;
                anneeMoisSuivant=annee+1;
            }
            else
            {
                moisSuivant=mois+1;
                anneeMoisSuivant=annee;
            }
            dates[i] -> setRank(lab, moisSuivant, anneeMoisSuivant);
        }
    }

    // Placons maintenant les éléments de la table
    // Avec les signaux de surbrillance
    int ligne = 0;
    for(int j = 0; j<42; j++)  // parcours des dates
    {
        setCellWidget(ligne, dates[j]->getRank(), dates[j]);

        //mise en evidence des dimanches
        if(!(dates[j]->getRank()))
        {
            dates[j] -> setStyleSheet("background-color:#b572ff; padding-left: 5px;"
                                      "border:none;");
        }

        // Les jours des autres mois sont grisés
        if (!dates[j]->getInMonth() || (j<19 && mois==9 && annee==1582))
            dates[j]->setStyleSheet("background-color: white; color: #dddddd;"
                                    "padding-left: 5px; border:none;");

        if ((dates[j] -> getRank())==6)              // Si on atteint la 7 ème colonne...
            ligne ++;                            // ... et on passe à la ligne

    }
    // colorer le jour actuelle
    if (moisCourant==date.month()-1 && anneeCourante==date.year())
    {
        Case * actuelle=dates[premierMois+date.day()-1];
        actuelle->setStyleSheet("background-color:#bcd977 ;color:blue;"
                                "padding-left: 5px; border:none;");
    }

    QStringList v_labels;

    determineNumSemaine(v_labels, moisCourant, anneeCourante);
    setVerticalHeaderLabels(v_labels);

    QString months[12] = {"January", "February", "March", "April",
                        "May", "June", "July", "August",
                         "September", "October", "November", "December"};
    QString str;
    str.append(QString("%1").arg(annee));
    label->setText(months[mois]+" "+str);

    listMois->setCurrentIndex(moisCourant);
    listAnnee->setCurrentIndex(anneeCourante-1582);
}

void Table::moisPrecedent()
{
    if (anneeCourante==1582 && moisCourant==9);
    else
    {
        if (moisCourant==0)
        {
            moisCourant=11;
            --anneeCourante;
        }
        else
            --moisCourant;
        changerMois(moisCourant, anneeCourante);
    }
}

void Table::moisSuivant()
{
    if (anneeCourante==2100 && moisCourant==11);
    else
    {
        if (moisCourant==11)
        {
            moisCourant=0;
            ++anneeCourante;
        }
        else
            ++moisCourant;
        changerMois(moisCourant, anneeCourante);
    }
}

void Table::changeMonth(int mois)
{
    if (mois<9 && anneeCourante==1582)
        listMois->setCurrentIndex(moisCourant);
    else
    {
        moisCourant = mois;
        changerMois(moisCourant, anneeCourante);
    }
}

void Table::changeYear(int annee)
{
    if (moisCourant<9 && annee==0)
        listAnnee->setCurrentIndex(anneeCourante-1582);
    else
    {
        anneeCourante = annee+1582;
        changerMois(moisCourant, anneeCourante);
    }
}

bool Table::inMonth(int indexCase, int mois, int annee)
{
    int premierMois = Table::funcPremierMois(mois, annee);
    int finMois[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (Table::nbreJoursAnnee(annee)==366)
        finMois[1] = 29;
    int endMonth = finMois[mois];
    if (indexCase>=premierMois && indexCase<premierMois+endMonth)
        return true;
    else
        return false;
}

void Table::caseClicked(int row, int column)
{
    int i = 7*row+column;
    if (!dates[i]->getInMonth())
    {
        if (i<funcPremierMois(moisCourant, anneeCourante))
            moisPrecedent();
        else
            moisSuivant();
    }
    else if (i<19 && moisCourant==9 && anneeCourante==1582)
        moisPrecedent();
    else
    {
        if (i!=date.day()-1 || moisCourant!=date.month()-1
            || anneeCourante!=date.year())
            dates[i]->coloreMoi();
        for (int j=0; j<42; j++)
            if (j!=i && (j!=date.day()-1 || moisCourant!=date.month()-1
                || anneeCourante!=date.year()))
            {
                if (moisCourant==9 && anneeCourante==1582)
                {
                    if (j<19);
                    else
                        dates[j]->resetMoi();
                }
                else
                    dates[j]->resetMoi();
            }
    }
}

void Table::showOrganiseur(int row, int column)
{
    int jour=row*7+column-funcPremierMois(moisCourant, anneeCourante)+1;
    if (!dates[row*7+column]->getInMonth()
        || (jour<15 && moisCourant==9 && anneeCourante==1582));
    else
    {
        organiseur = new Organiseur(this, jour, moisCourant, anneeCourante);
        organiseur->show();
    }
}

void Table::aboutUs()
{
    QMessageBox::information(this, "About Us",
                             "  Coded by :\n\n"
                             "- NOMENJANAHARY Fenohasina\n"
                             "- RABENARIVO A. Marius\n"
                             "- RAMAHASINDRY J. Sami\n"
                             "- RAMBELOSON Andriatomefisoa");
}
