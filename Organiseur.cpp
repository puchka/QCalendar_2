#include "Organiseur.h"
#include "Table.h"
#include "Moon.h"

Organiseur::Organiseur(QWidget *parent, int jour, int mois, int annee)
    :QDialog(parent)
{
    setFixedSize(360, 600);
    setWindowTitle("Organiser");
    editor = new TableEditor(this, jour, mois, annee);

    label = new QLabel(this);
    QString strJour;
    strJour.append(QString("%1").arg(jour));
    QString months[12]={"January", "February", "March", "April",
                        "May", "June", "July", "August",
                        "September", "October", "November", "December"};
    QString strAnnee;
    strAnnee.append(QString("%1").arg(annee));
    label->setText(months[mois]+" "+strJour+", "+strAnnee);

    QString strMois;
    strMois.append(QString("%1").arg(mois));

    evenement = new QLabel(this);
    croix = new QLabel(this);
    croix->setFixedWidth(32);
    saint = new QLabel(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bdd");
    if (db.open())
    {
        QSqlQuery query;
        if (query.exec("select count(*) as n from events where d="+
                       strJour+" and m="+strMois))
        {
            query.next();
            if (query.value(0).toInt()==1)
            {
                if (query.exec("select * from events where d="+
                               strJour+" and m="+strMois))
                {
                    query.next();
                    evenement->setText(query.value(2).toString());
                }
                else
                    QMessageBox::warning(this, "Warning",
                                         "select a échoué");
            }
        }
        else
        {
            QMessageBox::warning(this, "Warning",
                                 "count a échoué");
        }
        if (query.exec("select count(*) as n from saints where d="+
                       strJour+" and m="+strMois))
        {
            query.next();
            if (query.value(0).toInt()==1)
            {
                croix->setPixmap(QPixmap("croix.png"));
                if (query.exec("select * from saints where d="+
                               strJour+" and m="+strMois))
                {
                    query.next();
                    saint->setText(saint->text()+
                                   query.value(2).toString()+
                                   " "+query.value(3).toString());
                }
                else
                    QMessageBox::warning(this, "Warning",
                                         "select a échoué");
            }
        }
        else
        {
            QMessageBox::warning(this, "Warning",
                                 "count a échoué");
        }
        db.close();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Connexion échouée");
    }
    evenement->setStyleSheet("padding-left: 5px; font-weight: bold;");

    // Date de Pacques
    int m = annee;
    int c = m/100;
    int n = (11*(m%19)+14-c+c/4+((8*c+13)/25))%30;
    int q = (30+(m%19)/11-n)/30;
    int p = 51-n-q+(n+q+4*(m%7)+2*(m%4)+6*(c%7)+2*(c%4)+3)%7;
    if (p<=31 && mois==2 && jour==p)
        evenement->setText("Pâcques");
    else if ((p<31 && mois==2 && jour==p+1) ||
             (p==31 && mois==3 && jour==1))
        evenement->setText("Lundi de Pâcques");
    else if (p>31 && mois==3 && jour==p-31)
        evenement->setText("Pâcques");
    else if (p>31 && mois==3 && jour==p-30)
        evenement->setText("Lundi de Pâcques");

    // Date de Pentecote
    if (p-31-30+49<31 && mois==4 && jour==p-31-30+49)
        evenement->setText("Pentecôte");
    else if (p-30-31+49>31 && mois==5 && jour==p-30-31+49-31)
        evenement->setText("Pentecôte");
    else if (p-31-30+49+1<31 && mois==4 && jour==p-31-30+49+1)
        evenement->setText("Lundi de Pentecôte");
    else if (p-30-31+49+1>31 && mois==5 && jour==p-30-31+49-31+1)
        evenement->setText("Lundi de Pentecôte");

    // Date de l'Ascension
    if (p-31-30+39<31 && mois==4 && jour==p-31-30+39)
        evenement->setText("Ascension");
    else if (p-30-31+39>31 && mois==5 && jour==p-30-31+39-31)
        evenement->setText("Ascension");
    else if (p==22 && mois==3 && jour==30)
        evenement->setText("Ascension");

    // Date fête des mères
    int firstMay = Table::funcPremierMois(mois, annee);
    int i;
    std::vector<int>dim;
    for (i=0;i<31;i++)
    {
        if ((firstMay+i)%7==0)
            dim.push_back(i);
    }
    if (jour==dim[dim.size()-1]+1 && mois==4)
    {
        if (evenement->text()!="")
            evenement->setText(evenement->text()+"\nFête des mères");
        else
            evenement->setText("Fête des mères");
    }

    // Date fête des pères
    int firstJune = Table::funcPremierMois(mois, annee);
    std::vector<int>dim2;
    for (i=0;i<31;i++)
    {
        if ((firstJune+i)%7==0)
            dim2.push_back(i);
    }
    if (jour==dim2[2]+1 && mois==5)
    {
        if (evenement->text()!="")
            evenement->setText(evenement->text()+"\nFête des pères");
        else
            evenement->setText("Fête des pères");
    }

    moonPhase = new QLabel(this);
    int tab[3];
    float j;
    for (i=mois;i<=mois+1;i++)
    {
        for (j=0;j<=0.75;j+=0.25)
        {
            Moon::j2g(Moon::jde(i, annee, j), tab);
            if (jour==tab[0] && mois+1==tab[1])
            {
                if (j==0)
                    moonPhase->setPixmap(QPixmap("nl.png"));
                else if (j==0.25)
                    moonPhase->setPixmap(QPixmap("pq.png"));
                else if (j==0.5)
                    moonPhase->setPixmap(QPixmap("pl.png"));
                else
                    moonPhase->setPixmap(QPixmap("dq.png"));
            }
        }
    }

    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    vLayout->addWidget(label);
    vLayout->addWidget(evenement);
    hLayout->addWidget(croix);
    hLayout->addWidget(saint);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(moonPhase);
    vLayout->addWidget(editor);
    setLayout(vLayout);
}
