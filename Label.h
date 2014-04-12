#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <string>
#include <stdio.h>

class Label : public QLabel
{
public:
    Label(int mois, int annee, QWidget *parent);
};

#endif // LABEL_H
