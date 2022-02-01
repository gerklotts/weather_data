#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QDebug>

class weatherdata : public QObject
{
    Q_OBJECT

public:
    weatherdata();
    ~weatherdata();

    QTimer *tmr;

    QJsonDocument doc;
    QJsonObject temp;
    QJsonParseError docEr;

    QNetworkAccessManager* netwMan;
    QNetworkRequest request;

private slots:
    void sendReq();
    void slot_netwMan(QNetworkReply*);

};

#endif // WEATHERDATA_H
