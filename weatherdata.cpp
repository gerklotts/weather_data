#include "weatherdata.h"

weatherdata::weatherdata()
{
    netwMan = new QNetworkAccessManager(this);
        connect(netwMan,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_netwMan(QNetworkReply*)));

    request.setUrl(QUrl("http://api.openweathermap.org/data/2.5/weather?lat=56.7333&lon=37.1667&appid=92ae7d394d59a7564e60de67e236abc8"));

    tmr = new QTimer();
    tmr->setInterval(10000);
        connect(tmr,SIGNAL(timeout()),this,SLOT(sendReq()));
    tmr->start(10000);

    qDebug()<<"Timer started";
}

weatherdata::~weatherdata()
{
    tmr->stop();
    tmr->deleteLater();

    delete netwMan;
}


void weatherdata::sendReq()
{
    qDebug()<<"OK";
    netwMan->get(request);
}

void weatherdata::slot_netwMan(QNetworkReply *rep)
{
    rep->waitForReadyRead(1000);

    doc = QJsonDocument::fromJson(rep->readAll(), &docEr);

    if(docEr.errorString() == "no error occurred")
    {
        temp = doc.object().value("main").toObject();

        qDebug()<<"Temp: "<<temp.value("temp").toDouble()-273;
        qDebug()<<"Data: "<<QDateTime::currentDateTime().date();
        qDebug()<<"Time: "<<QDateTime::currentDateTime().time().toString();
    }
    else
    {
        qDebug()<<"False ";
    }

    rep->deleteLater();
}
