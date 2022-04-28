#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

class DBManager
{
public:
    DBManager(const QString & path);
    ~DBManager();
    bool isOpen() const;
    bool createTable(const QString & table_name);
    bool tableExists();
    bool dropTable();
    bool insertIntoTable(const QString & begin_date, const QString & finish_date, const QString & author);
    bool selectAllFromTable();
    bool deleteAllFromTable();


private:
    QSqlDatabase prova_conceito_database;
    QString table_name = "experimento";

};
#endif // DBMANAGER_H
