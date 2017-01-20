#include "qml2ctranslator.h"
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QGuiApplication>
#include "xmlasutpdata.h"


qml2Ctranslator::qml2Ctranslator(QObject *parent) : QObject(parent)
{
    // listGorod:
    listGorod = new QStringList;
}

void qml2Ctranslator::setEngine(QQmlApplicationEngine *data)
{
    engine=data;
}

void qml2Ctranslator::setAsutpData(xmlAsutpData *data)
{
    asutpData=data;
}

// обновить список городов в интерфейсе qml из списка listGorod:
void qml2Ctranslator::updateGorodList(void)
{
    engine->rootContext()->setContextProperty("listModelCitySearchId", QVariant::fromValue(*listGorod));
}

void qml2Ctranslator::searchGorod(QString text)
{
    qDebug() << __FUNCTION__ << ":" << __LINE__;
    qDebug() << "C++ method called!" << text;
    //listGorod->append("test c++ append" + text);
    //listGorod->append(text);
    listGorod->clear();

    // Берём список городов:
    if(asutpData->getNasPunkts(listGorod,text)==NULL)
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__ << ": Error! get nasPunkts == NULL";
        return;
    }
    else
    {
        updateGorodList();
    }
}
