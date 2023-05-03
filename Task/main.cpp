#include "widget.h"

#include <QApplication>

#define MY_TEST = 1

#ifdef MY_TEST

#include <QtTest>
#include "testclient.h"

#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef MY_TEST
    TestClient tclient;
    QTest::qExec(&tclient, argc, argv);
    return a.exec();
#else
    Widget w;
    w.show();
    return a.exec();
#endif
}
