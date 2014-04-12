#ifndef BOUTON_H
#define BOUTON_H

#include <QPushButton>

class Bouton : public QPushButton
{
public:
    Bouton(const QString text, QWidget *parent);
};

#endif // BOUTON_H
