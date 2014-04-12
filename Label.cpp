#include "Label.h"

Label::Label(int mois, int annee, QWidget *parent)
    :QLabel(parent)
{
    QString months[12] = {"January", "February", "March", "April",
                        "May", "June", "July", "August",
                         "September", "October", "November", "December"};
    QString str;
    str.append(QString("%1").arg(annee));
    setText(months[mois]+" "+str);
    setGeometry(100, 42, 100, 20);
}
