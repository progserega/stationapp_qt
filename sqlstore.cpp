#include "sqlstore.h"
#include <QtSql>
#include <QTime>
#include <QSqlDatabase>

bool sqlstore::testFillDb(void)
{
    beginTransaction();
    qDebug() << QTime::currentTime().toString() << __FUNCTION__ << ":" << __LINE__ << "Start fill db";
    QTime t;
    t.start();

    // СП
    if (!addSp(1,"СП ЮЭС"))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error add record to db!";
        return false;
    }

    if (!addSp(2,"СП ЦЭС"))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error add record to db!";
        return false;
    }

    // РЭС-ы
    if (!addRes(1,"РЭС-6",1))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error add record to db!";
        return false;
    }
    if (!addRes(2,"РЭС-7",1))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error add record to db!";
        return false;
    }
    if (!addRes(3,"РЭС-5",2))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error add record to db!";
        return false;
    }
    // Населённые пункты:
     if (!addNp(1,"Владивосток"))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error add record to db!";
        return false;
    }
    if (!addNp(2,"Находка"))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error add record to db!";
        return false;
    }
    if (!addNp(3,"Уссурийск"))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error add record to db!";
        return false;
    }


    if (!addStation(QString("station_name_1"),1,1,1,1))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error add record to db!";
        return -1;
    }
    if (!addStation(QString("station_name_2"),2,1,1,2))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error add record to db!";
        return -1;
    }

    for (int x=5;x<10;x++)
    {
        if (!addStation(QString("station_name_%1").arg(x),x,2,1,3))
        {
            qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error add record to db!";
            return -1;
        }
    }

    endTransaction();
    qDebug("Time elapsed: %d ms", t.elapsed());
    qDebug() << QTime::currentTime().toString() << __FUNCTION__ << ":" << __LINE__ << "End fill db";
    return 0;
}

sqlstore::sqlstore(QSqlDatabase *dbase)
{
    db = dbase;
  /*  sdb = new QSqlDatabase;
    sdb->addDatabase("QSQLITE");
    sdb->setDatabaseName(path);

    if (!sdb->open()) {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error open db (" << path << "). QT error: " << sdb->lastError().text();
    }
    else
    {
        dbOpened=true;
    }
    */
/*
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
        dbase.setDatabaseName(path);
        if (!dbase.open()) {
            qDebug() << "Что-то пошло не так!";
        }

        QSqlQuery a_query;
        // DDL query
        QString str = "CREATE TABLE my_table ("
                "number integer PRIMARY KEY NOT NULL, "
                "address VARCHAR(255), "
                "age integer"
                ");";
        bool b = a_query.exec(str);
        if (!b) {
            qDebug() << "Вроде не удается создать таблицу, провертье карманы!";
        }

        // DML
        QString str_insert = "INSERT INTO my_table(number, address, age) "
                "VALUES (%1, '%2', %3);";
        str = str_insert.arg("14")
                .arg("hello world str.")
                .arg("37");
        b = a_query.exec(str);
        if (!b) {
            qDebug() << "Кажется данные не вставляются, проверьте дверь, может она закрыта?";
        }
        //.....
        if (!a_query.exec("SELECT * FROM my_table")) {
            qDebug() << "Даже селект не получается, я пас.";
        }
        QSqlRecord rec = a_query.record();
            int number = 0,
                    age = 0;
            QString address = "";

            while (a_query.next()) {
                number = a_query.value(rec.indexOf("number")).toInt();
                age = a_query.value(rec.indexOf("age")).toInt();
                address = a_query.value(rec.indexOf("address")).toString();

                qDebug() << "number is " << number
                         << ". age is " << age
                         << ". address" << address;
            }
            */
}

bool sqlstore::speedUp(void)
{
    db->exec("PRAGMA synchronous = OFF");
    db->exec("PRAGMA journal_mode = MEMORY");
    return true;
}

bool sqlstore::speedDown(void)
{
    db->exec("PRAGMA synchronous = FULL");
    db->exec("PRAGMA journal_mode = DELETE");
    return true;
}

bool sqlstore::beginTransaction(void)
{
    QSqlQuery q;
    QString sql = "begin transaction;";

    if (!q.exec(sql))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error sql exec: " << sql << ". QT error: " << db->lastError().text();
        return false;
    }
    return true;
}

bool sqlstore::endTransaction(void)
{
    QSqlQuery q;
    QString sql = "end transaction;";

    if (!q.exec(sql))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error sql exec: " << sql << ". QT error: " << db->lastError().text();
        return false;
    }
    return true;
}

bool sqlstore::addNp(int id, QString name)
{
    QSqlQuery q;
    QString sql_insert = "insert into np_tbl (id,name) values (%1,'%2');";
    QString sql = sql_insert.arg(id).arg(name);

    if (!q.exec(sql))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error sql exec: " << sql << ". QT error: " << db->lastError().text();
        return false;
    }
    return true;
}

bool sqlstore::addRes(int id, QString name, int sp_id)
{
    QSqlQuery q;
    QString sql_insert = "insert into res_tbl (id,name,sp_id) values (%1,'%2',%3);";
    QString sql = sql_insert.arg(id).arg(name).arg(sp_id);

    if (!q.exec(sql))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error sql exec: " << sql << ". QT error: " << db->lastError().text();
        return false;
    }
    return true;
}

bool sqlstore::addSp(int id, QString name)
{
    QSqlQuery q;
    QString sql_insert = "insert into sp_tbl (id,name) values (%1,'%2');";
    QString sql = sql_insert.arg(id).arg(name);

    if (!q.exec(sql))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error sql exec: " << sql << ". QT error: " << db->lastError().text();
        return false;
    }
    return true;
}

bool sqlstore::addStation(QString name, int uid, int sp_id, int res_id, int np_id)
{
    QSqlQuery q;
    QString sql_insert = "insert into station_tbl (name, uniq_id, sp_id, res_id, np_id) values ('%1',%2, %3, %4, %5);";
    QString sql = sql_insert.arg(name).arg(uid).arg(sp_id).arg(res_id).arg(np_id);

    if (!q.exec(sql))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error sql exec: " << sql << ". QT error: " << db->lastError().text();
        return false;
    }
    return true;
}

bool sqlstore::isEmpty(void)
{
    QSqlQuery q;
    QString sql = "select * from stations limit 1;";
    if (!q.exec(sql))
    {
        qDebug() << QTime::currentTime().toString() << __FUNCTION__ << ":" << __LINE__ << "Error sql exec: " << sql << ". QT error: " << db->lastError().text();
        return true;
    }
    return false;
}

bool sqlstore::createTables(void)
{
    QSqlQuery q;
    QString sql;
    // Подстанции:
    sql = "CREATE TABLE station_tbl ("
                "id integer PRIMARY KEY NOT NULL, "
                "name VARCHAR(255), "
                "uniq_id integer,"
                "sp_id integer,"
                "res_id integer,"
                "np_id integer"
                ");";
    if (!q.exec(sql))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error sql exec: " << sql << ". QT error: " << db->lastError().text();
        return false;
    }
    // СП
    sql = "CREATE TABLE sp_tbl ("
                "id integer PRIMARY KEY NOT NULL, "
                "name VARCHAR(255) "
                ");";
    if (!q.exec(sql))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error sql exec: " << sql << ". QT error: " << db->lastError().text();
        return false;
    }
    // РЭСЫ
    sql = "CREATE TABLE res_tbl ("
                "id integer PRIMARY KEY NOT NULL, "
                "name VARCHAR(255), "
                "sp_id integer"
                ");";
    if (!q.exec(sql))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error sql exec: " << sql << ". QT error: " << db->lastError().text();
        return false;
    }
    // Населённые пункты
    sql = "CREATE TABLE np_tbl ("
                "id integer PRIMARY KEY NOT NULL, "
                "name VARCHAR(255) "
                ");";
    if (!q.exec(sql))
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error sql exec: " << sql << ". QT error: " << db->lastError().text();
        return false;
    }
    return true;
}

