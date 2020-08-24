#include <QtTest/QtTest>
#include <QObject>
#include "crypto.h"

class CryptoTest : public QObject {
    Q_OBJECT

private slots:

    void base64encrypt();
    void base64decrypt();
};
