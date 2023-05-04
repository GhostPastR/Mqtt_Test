#include "testclient.h"
#include "client.h"

#include <QDebug>

TestClient::TestClient(QObject *parent) : QObject(parent)
{
    client_ = new Client();
}

void TestClient::test()
{
    ParameterClient param{
        "test.mosquitto.org",
        1883,
        "",
        "",
        "piklema/test",
        "C:/Users/user/Documents/git/TestFile/1.txt"
    };


    connect(client_, &Client::finished, this, &TestClient::finished);
    connect(client_, &Client::errorMessage, this, &TestClient::errorMessage);
    connect(client_, &Client::okTransmission, this, &TestClient::okTransmission);
    client_->setParameter(param);
    client_->run();

}

void TestClient::finished()
{
    qDebug() << "1";
}

void TestClient::errorMessage(QString message)
{
    qDebug() << "2";
}

void TestClient::okTransmission(qulonglong indexp, qulonglong index)
{
    qDebug() << "3";
}
