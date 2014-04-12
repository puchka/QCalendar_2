#include"Case.h"
#include"Table.h"

Case::Case(const QString text, QWidget * parent)
    : QLabel(text, parent)
{
    QLabel::setStyleSheet("padding-left: 5px; border:none");
    if (hasFocus())
    {
        emit isFocused();     // emettre un signal lors d'un focus
    }
}


void Case::coloreMoi()
{
    setStyleSheet("background-color: #3333cc; color: red;"
                  "padding-left: 5px; border:none; font-weight: bold");
}

void Case::resetMoi()
{
    if (this->getInMonth())
    {
        setStyleSheet("background-color: white; padding-left: 5px;"
                      "border: none;");
        if (!this->getRank())
            setStyleSheet("background-color:#b572ff; padding-left: 5px;"
                          "border:none;");
    }
    else
        setStyleSheet("background-color: white; color: #dddddd;"
                      "padding-left:5px ;border:none;");
}

// Fonction renvoyant le rang du jours dans la semaine
int Case::getRank()
{
    return rank;
}

// Fonction qui met à jour le rang du jours dans la semaine
void Case::setRank(int jours, int mois, int annee)
{
    rank = (jours - 1 + Table::funcPremierMois(mois, annee))%7;
}

bool Case::getInMonth()
{
    return inMonth;
}

void Case::setInMonth(int indexCase, int mois, int annee)
{
    inMonth = Table::inMonth(indexCase, mois, annee);
}
