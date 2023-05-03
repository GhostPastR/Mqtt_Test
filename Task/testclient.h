#ifndef TESTCLIENT_H
#define TESTCLIENT_H

#include <QObject>

class Client;

class TestClient : public QObject
{
    Q_OBJECT
public:
    TestClient(QObject *parent = nullptr);

private slots:
    void test();

    void finished();
    void errorMessage(QString message);
    void okTransmission(qulonglong indexp, qulonglong index);

private:
    Client *client_{};
};

#endif // TESTCLIENT_H
