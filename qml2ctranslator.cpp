#include "qml2ctranslator.h"
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QGuiApplication>


qml2Ctranslator::qml2Ctranslator(QObject *parent) : QObject(parent)
{
    // список СП
    sp_list = new QStringList;
}

void qml2Ctranslator::setEngine(QQmlApplicationEngine *data)
{
    engine=data;
}

// обновить список городов в интерфейсе qml из списка listGorod:
void qml2Ctranslator::setSpList(void)
{
    sp_list->append("test");
    qDebug() << "sp_list:" << sp_list;
    engine->rootContext()->setContextProperty("sp_selector", QVariant::fromValue(*sp_list));
}

void qml2Ctranslator::searchGorod(QString text)
{
    qDebug() << __FUNCTION__ << ":" << __LINE__;
    qDebug() << "C++ method called!" << text;
    //listGorod->append("test c++ append" + text);
    //listGorod->append(text);
 /*   listGorod->clear();

    // Берём список городов:
    if(asutpData->getNasPunkts(listGorod,text)==NULL)
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << ": Error! get nasPunkts == NULL";
        return;
    }
    else
    {
        updateGorodList();
    }*/
}
