#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QStandardPaths>
#include <sys/utsname.h>
#include <QDir>
#include <QTime>
#include "sqlstore.h"

#define APP_NAME "stationapp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    // Определяем систему, где мы запустились:
    //qDebug() << __FUNCTION__ << ":" << __LINE__ << "OS: " << osVersion();

    // отладка путей:
    //QStandardPaths path;
    qDebug() << __FUNCTION__ << ":" << __LINE__ << "QStandardPaths::HomeLocation: " << QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    qDebug() << __FUNCTION__ << ":" << __LINE__ << "QStandardPaths::DesktopLocation: " << QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    qDebug() << __FUNCTION__ << ":" << __LINE__ << "QStandardPaths::TempLocation: " << QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    qDebug() << __FUNCTION__ << ":" << __LINE__ << "QStandardPaths::CacheLocation: " << QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    qDebug() << __FUNCTION__ << ":" << __LINE__ << "QStandardPaths::DataLocation: " << QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    qDebug() << __FUNCTION__ << ":" << __LINE__ << "QStandardPaths::ConfigLocation: " << QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    qDebug() << __FUNCTION__ << ":" << __LINE__ << "QStandardPaths::DownloadLocation" << QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    qDebug() << __FUNCTION__ << ":" << __LINE__ << "getenv(\"EXTERNAL_STORAGE\"): " << getenv("EXTERNAL_STORAGE");

    QString config_path,data_path;
    QDir dir;
#ifdef Q_OS_ANDROID
    data_path=(QString)getenv("EXTERNAL_STORAGE")+"/"+APP_NAME;
    config_path=(QString)getenv("EXTERNAL_STORAGE")+"/"+ APP_NAME + "/config";
    if(!dir.exists(config_path))
    {
        if(!dir.mkpath(config_path))
        {
            qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error create path: " << config_path;
        }
    }
    /*
    QAndroidJniObject mediaDir = QAndroidJniObject::callStaticObjectMethod("android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;");
    QString dataAbsPath = mediaDir.toString();
    QAndroidJniEnvironment env;
    if (env->ExceptionCheck())
    {
        // Handle exception here.
        env->ExceptionClear();
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "error get Android method getExternalStorageDirectory()";
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "getExternalStorageDirectory() android api: " << dataAbsPath;
    }
    */

#else
    data_path=QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    config_path=QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)+"/" + APP_NAME;
    if(!dir.exists(config_path))
    {
        if(!dir.mkpath(config_path))
        {
            qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error create path: " << config_path;
        }
    }
    if(!dir.exists(data_path))
    {
        if(!dir.mkpath(data_path))
        {
            qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error create path: " << data_path;
        }
    }
#endif

    QString db_path=data_path+"/data_db.sqlite";
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(db_path);
    if (!dbase.open()) {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error open db (" << db_path << "). QT error: " << dbase.lastError().text();
        return -1;
    }

    sqlstore *db = new sqlstore(&dbase);
    if(db->isEmpty())
    {
        if(!db->createTables())
        {
            qDebug() << __FUNCTION__ << ":" << __LINE__ << "Error create tables in sqlite! Path to sqlite db: " << db_path;
            return -1;
        }
        // fixme
        db->testFillDb();
    }

    qml2Ctranslator qml2c;
    qml2c.setEngine(&engine);
    qml2c.setAsutpData(&asutpData);
    engine.rootContext()->setContextProperty("qml2c", &qml2c);

    return app.exec();
}
