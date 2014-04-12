#ifndef TABLE_H
#define TABLE_H

#include<QWidget>
#include<QLabel>
#include<QTableWidget>
#include<QHeaderView>
#include<QStringList>
#include<QString>
#include<QDate>
#include<QComboBox>
#include<vector>
#include<stdio.h>
#include"Case.h"
#include "Label.h"
#include "Organiseur.h"

class Table : public QTableWidget     // On hérite de QTableWidget
{
    Q_OBJECT

public:
    Table(QWidget *parent);
    static int funcPremierMois(int mois, int annee);                   // Rang du 1er jours du mois dans la semaine
                                                                       // dimanche -> 0 ... samedi -> 7
    static int nbreJoursAnnee(int annee);                              // Nombre de jours de l'annee
    static int nbreJoursMoisAnnee(int mois, int annee);                // Nombre de jours entre le le 1er du mois
                                                                       // et le 1er janvier
    static int nbreJoursMoisAnnee2012(int mois, int annee);            // Nombre de jours entre le 1er du mois
                                                                       // et le 1er janvier 2012

    static void determineNumSemaine(QStringList &v_labels, int mois, int annee); // numero Semaine
    static int nbreCaseAnnee(int annee);

    static bool inMonth(int indexCase, int mois, int annee);

public slots:
    void caseClicked(int row, int column);
    void moisPrecedent();
    void moisSuivant();
    void changeMonth(int mois);
    void changeYear(int annee);
    void showOrganiseur(int row, int column);
    void aboutUs();

private:
    void repartirDate(int premierMois, int mois, int annee);
    void changerMois(int mois, int annee);

    int moisCourant;
    int anneeCourante;

    Label *label;
    QComboBox *listMois;
    QComboBox *listAnnee;

    Organiseur *organiseur;

    std::vector<Case*>dates;
    QDate date;
    int rang;
};

#endif // TABLE_H
