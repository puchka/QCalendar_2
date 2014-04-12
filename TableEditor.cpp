#include "TableEditor.h"

TableEditor::TableEditor(QWidget *parent, int i_jour, int i_mois, int i_annee)
    :QTableWidget(24, 1, parent)
{
    setColumnWidth(0, 270);
    QStringList horizontalLabel;
    horizontalLabel << "To do List";
    setHorizontalHeaderLabels(horizontalLabel);
    QStringList verticalLabels;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bdd");

    jour = i_jour;
    mois = i_mois;
    annee = i_annee;

    QString strD;
    strD.append(QString("%1").arg(jour));
    QString strM;
    strM.append(QString("%1").arg(mois));
    QString strY;
    strY.append(QString("%1").arg(annee));
    for (int i=0;i<24;i++)
    {
        QString str, str2;
        str.append(QString("%1").arg(i));
        str2.append(QString("%1").arg(i+1));
        verticalLabels << str+"-"+str2;

        labels[i] = new QLabel(this);
        labels[i]->setStyleSheet("padding-left: 5px;");
        setCellWidget(i, 0, labels[i]);

        if(db.open())
        {
            QSqlQuery query;
            if(query.exec("SELECT * FROM todolist where d="+strD
                          +" and m="+strM+" and y="+strY))
            {
                while(query.next())
                {
                    if (i==query.value(3).toInt())
                        labels[i]->setText(query.value(4).toString());
                }
            }
            else
                QMessageBox::warning(this, "Requête échouée",
                                     "La requête a échouée, désolé.");
        }
        else
        {
            QMessageBox::warning(this, "Connexion échouée",
                                 "La connexion a échouée, désolé.");
        }
    }
    db.close();
    setVerticalHeaderLabels(verticalLabels);

    QObject::connect(this, SIGNAL(cellDoubleClicked(int,int)),
                     this, SLOT(changeToDo(int, int)));
}

void TableEditor::changeToDo(int row, int column)
{
    QString str;
    str.append(QString("%1").arg(row));
    QString strD;
    strD.append(QString("%1").arg(jour));
    QString strM;
    strM.append(QString("%1").arg(mois));
    QString strY;
    strY.append(QString("%1").arg(annee));
    bool ok;
    QString text;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bdd");
    db.open();
    QSqlQuery query;
    if(query.exec("select count(*) as n from todolist where h="+str
                  +" and d="+strD+" and m="+strM+" and y="+strY))
    {
        query.next();
        if (query.value(0).toInt()==1)
        {
            if(query.exec("SELECT * FROM todolist WHERE h="+str
                          +" and d="+strD+" and m="+strM+" and y="+strY))
            {
                query.next();
                text = query.value(4).toString();
            }
            else
                QMessageBox::warning(this, "Requête échouée",
                                     "La requête a échouée, désolé.");
        }
    }
    else
        QMessageBox::warning(this, "Requête échouée",
                             "count a échouée, désolé.");
    QString todo;
    todo = QInputDialog::getText(this, "To do", "To do :",
                                 QLineEdit::Normal, text,
                                 &ok);
    if (ok)
    {
        if(query.exec("select count(*) as n from todolist where h="+str
                      +" and d="+strD+" and m="+strM+" and y="+strY))
        {
            query.next();
            if (query.value(0).toInt()==1)
            {
                if(query.exec("update todolist set todo='"+todo+"' "
                              "where h="+str+" and d="+strD+" and m="+
                              strM+" and y="+strY));
                else
                    QMessageBox::warning(this, "Requête échouée",
                                         "update a échouée, désolé.");
            }
            else
            {
                if (query.exec("insert into todolist values("+strD+", "
                               +strM+", "+strY+" ,"+str+", '"+todo+"')"));
                else
                    QMessageBox::warning(this, "Requête échouée",
                                         "La requête a échouée, désolé.");
            }
        }
        else
            QMessageBox::warning(this, "Requête échouée",
                                 "count a échouée, désolé.");
        labels[row]->setText(todo);
    }
    db.close();
}
