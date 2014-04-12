#ifndef ORGANISEUR_H
#define ORGANISEUR_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "TableEditor.h"

class Organiseur : public QDialog
{
public:
    Organiseur(QWidget *parent, int jour, int mois, int annee);
private:
    TableEditor *editor;
    QLabel *label;
    QLabel *evenement;
    QLabel *croix;
    QLabel *saint;
    QLabel *moonPhase;
};

#endif // ORGANISEUR_H
