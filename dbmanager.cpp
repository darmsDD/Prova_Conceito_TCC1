#include "dbmanager.h"

DBManager::DBManager(const QString & path)
{

    this->prova_conceito_database = QSqlDatabase::addDatabase("QSQLITE");
    this->prova_conceito_database.setDatabaseName(path);

    if(this->prova_conceito_database.open())
    {
        qDebug() << "Banco de dados: " << path << " criado.";
    } else{
        qDebug() << "Erro ao criar o banco. " << this->prova_conceito_database.lastError();
    }

}

DBManager::~DBManager()
{
    if(this->prova_conceito_database.isOpen())
    {
        this->prova_conceito_database.close();
    }
}

bool DBManager::isOpen() const
{
    return this->prova_conceito_database.isOpen();
}

bool DBManager::createTable(const QString & table_name)
{
    bool success = false;
    QSqlQuery query;
    QString command = QString("CREATE TABLE %1 (id INTEGER PRIMARY KEY, beginDate TEXT, finishDate TEXT, author TEXT);").arg(table_name);
    query.prepare(command);

    if(query.exec())
    {
        qDebug() << "Tabela " << table_name << " criada.";
        success = true;
    } else{
        qDebug() << "Erro ao criar tabela: " << query.lastError();
    }
    this->table_name = table_name;
    return success;
}

bool DBManager::tableExists()
{
    bool success = false;
    QSqlQuery query;
    QString command = QString("SELECT EXISTS ( SELECT name FROM sqlite_schema WHERE type='table' AND name='%1')").arg(this->table_name);
    query.prepare(command);

    if(query.exec()){
        while(query.next()){
            if(query.value(0) == 1)
            {
                qDebug() << "A tabela "<< this->table_name << " existe.";
                success = true;
            } else{
                qDebug() << "A tabela "<< this->table_name << " não existe.";
                success = false;
            }

        }
    } else{
        qDebug() << "Erro na seleção da tabela " << this->table_name << ": " << query.lastError();
    }
    return success;
}

bool DBManager::dropTable()
{
    bool success = false;
    QSqlQuery query;
    QString command = QString("DROP TABLE %1;").arg(this->table_name);
    query.prepare(command);

    if(query.exec()){
        qDebug() << "Tabela "<< this->table_name << "Deletada com sucesso.";
        success = true;
    } else{
        qDebug() << "Erro na deleção da tabela " << this->table_name << ": " << query.lastError();
    }
    return success;

}

bool DBManager::insertIntoTable(const QString & begin_date, const QString & finish_date, const QString & author)
{
    bool success = false;
    QSqlQuery query;
    //INSERT INTO people (id, name) Values (:id,:name)
    QString command = QString("INSERT INTO %1 (beginDate, finishDate, author) Values (:begin_date,:finish_date,:author)").arg(this->table_name);
    query.prepare(command);
    query.bindValue(":begin_date",begin_date);
    query.bindValue(":finish_date",finish_date);
    query.bindValue(":author",author);

    if(query.exec()){
        qDebug() << "Inserção concluída com sucesso.";
        success = true;
    } else{
        qDebug() << "Erro na inserção da tabela " << this->table_name << ": " << query.lastError();
    }
    return success;

}
bool DBManager::selectAllFromTable()
{
    bool success = false;
    QSqlQuery query;
    QString command = QString("SELECT * FROM  %1;").arg(this->table_name);
    query.prepare(command);

    if(query.exec()){
        int begin_date_index = query.record().indexOf("beginDate");
        int finish_date_index = query.record().indexOf("finishDate");
        int author_index = query.record().indexOf("author");

        while(query.next()){
               qDebug() << "Data de Inicio: " << query.value(begin_date_index).toString() << "| Data de Fim: "
                << query.value(finish_date_index).toString() << "| Autor:" << query.value(author_index).toString();
        }

        success = true;
    } else{
        qDebug() << "Erro na seleção da tabela " << this->table_name << ": " << query.lastError();
    }
    return success;
}
bool DBManager::deleteAllFromTable()
{

    bool success = false;
    QSqlQuery query;
    QString command = QString("DELETE FROM %1;").arg(this->table_name);
    query.prepare(command);

    if(query.exec()){
        qDebug() << "Dados da tabela " << this->table_name << " apagados.";

        success = true;
    } else{
        qDebug() << "Erro na deleção de dados da tabela " << this->table_name << ": " << query.lastError();
    }
    return success;

}

