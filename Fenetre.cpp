#include "Fenetre.h"
#include "Table.h"
#include "Bouton.h"
#include "Clock.h"

Fenetre::Fenetre()
    :QWidget()
{
    this->setFixedSize(450, 250);
    QLabel* fond = new QLabel(this);
    fond->resize(500, 500);
    fond->move(0, -30);
    fond->setPixmap(QPixmap("fond.png"));
    Table * m_case;
    m_case = new Table(this);
    m_case -> move(30, 70);

    Bouton *p_bouton;
    p_bouton = new Bouton("<", this);
    p_bouton->setGeometry(30, 40, 30, 20);

    Bouton *n_bouton;
    n_bouton = new Bouton(">", this);
    n_bouton->setGeometry(205, 40, 30, 20);

    Bouton *about;
    about = new Bouton("About Us", this);
    about->setGeometry(315, 40, 60, 20);

    Clock *clock;
    clock = new Clock(150, this);
    clock->move(270, 75);

    QObject::connect(p_bouton, SIGNAL(clicked()), m_case, SLOT(moisPrecedent()));
    QObject::connect(n_bouton, SIGNAL(clicked()), m_case, SLOT(moisSuivant()));

    QObject::connect(about, SIGNAL(clicked()), m_case, SLOT(aboutUs()));
}
