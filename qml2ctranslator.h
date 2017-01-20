#ifndef QML2CTRANSLATOR_H
#define QML2CTRANSLATOR_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "xmlasutpdata.h"

class qml2Ctranslator : public QObject
{
    Q_OBJECT
public:
    explicit qml2Ctranslator(QObject *parent = 0);
    void setEngine(QQmlApplicationEngine *data);
    void setListGorod(QStringList *data);
    void setAsutpData(xmlAsutpData *data);
    void updateGorodList(void);

signals:

public slots:
   void searchGorod(QString text);

private:
    QQmlApplicationEngine *engine;
    QStringList *listGorod;
    xmlAsutpData *asutpData;
};

#endif // QML2CTRANSLATOR_H
