#include <QApplication>
#include "Fenetre.h"
#include "Table.h"
#include "Bouton.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    Fenetre  *fenetre;
    fenetre = new Fenetre;

    fenetre->show();

    return app.exec();
}
