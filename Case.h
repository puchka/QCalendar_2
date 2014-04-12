#ifndef CASE_H
#define CASE_H

#include<QLabel>
#include<QString>
#include<string>

class Case: public QLabel
{
    Q_OBJECT

public:
    Case(const QString text, QWidget * parent);
    void setRank(int jours, int mois, int annee);
    int getRank();
    void setInMonth(int indexCase, int mois, int annee);
    bool getInMonth();
    void coloreMoi();
    void resetMoi();
signals:
    void isFocused();

private:
    int rank;           // rang du jour dans la semaine
    bool inMonth;      // true si le jour est dans le mois en cours
};

#endif // CASE_H
