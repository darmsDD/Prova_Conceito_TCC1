#include "mainwindow.h"
#include "dbmanager.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const QString path ="./prova_conceito.db";
    DBManager my_db(path);
    if(my_db.isOpen())
    {
        if(!my_db.tableExists()){my_db.createTable("experimento");}
        my_db.insertIntoTable("26/04/2022 18:30:30","27/04/2022 18:30:30","Ivan Diniz Dobbin1");
        my_db.insertIntoTable("27/04/2022 18:30:30","28/04/2022 18:30:30","Ivan Diniz Dobbin2");
        my_db.insertIntoTable("28/04/2022 18:30:30","29/04/2022 18:30:30","Ivan Diniz Dobbin3");
        my_db.selectAllFromTable();
        //my_db.deleteAllFromTable();
        //my_db.dropTable();
    }
    MainWindow w;
    QSqlTableModel * model = new QSqlTableModel;
    model->setTable("experimento");
    model->select();

    QTableView *view = new QTableView;
    view->setModel(model);
    view->resizeColumnsToContents();

    w.setCentralWidget(view);
    w.setWindowTitle("Histórico");

    w.show();
    return a.exec();
}
