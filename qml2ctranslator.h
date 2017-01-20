#ifndef QML2CTRANSLATOR_H
#define QML2CTRANSLATOR_H

#include <QObject>
#include <QQmlApplicationEngine>

class qml2Ctranslator : public QObject
{
    Q_OBJECT
public:
    explicit qml2Ctranslator(QObject *parent = 0);
    void setEngine(QQmlApplicationEngine *data);
    void setSpList(void);

signals:

public slots:
   void searchGorod(QString text);

private:
    QQmlApplicationEngine *engine;
    QStringList *sp_list;
};

#endif // QML2CTRANSLATOR_H
