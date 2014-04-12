#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QTableWidget>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QtSql>

class TableEditor : public QTableWidget
{
    Q_OBJECT
public:
    TableEditor(QWidget *parent, int i_jour, int i_mois, int i_annee);
public slots:
    void changeToDo(int row, int column);
private:
    QLabel *labels[24];
    int jour;
    int mois;
    int annee;
};

#endif // TABLEEDITOR_H
