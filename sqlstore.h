#include <QString>
#include <QtSql>
#include <QSqlDatabase>

#ifndef SQLSTORE_H
#define SQLSTORE_H


class sqlstore
{
public:
    sqlstore(QSqlDatabase *dbase);
    bool createTables(void);
    bool isEmpty(void);
    bool speedUp(void);
    bool speedDown(void);
    bool testFillDb(void);
    bool beginTransaction(void);
    bool endTransaction(void);
    bool addStation(QString name, int uid, int sp_id, int res_id, int np_id);
    bool addSp(int id, QString name);
    bool addRes(int id, QString name, int sp_id);
    bool addNp(int id, QString name);
private:
    QSqlDatabase *db;
};

#endif // SQLSTORE_H
