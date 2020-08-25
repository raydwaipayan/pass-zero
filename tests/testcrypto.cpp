#include "testcrypto.h"
#include <iostream>
#include "hasher.h"

void CryptoTest::base64encrypt() {
    QCOMPARE("S2FpYmVpd2FpM0FlU2gwcGhhZTdBaHN1aDZTaGFuZzhhaVBoMEFmdQ==",
             zero::Crypto::base64Encrypt(
                 "Kaibeiwai3AeSh0phae7Ahsuh6Shang8aiPh0Afu"));
    QCOMPARE(std::string("aGVsbG8gaXQncyBkd2Fp"),
             zero::Crypto::base64Encrypt("hello it's dwai"));
}

void CryptoTest::base64decrypt() {
    QCOMPARE("ahh3Liequoojivozai4duth0AhBoob1ohciGaech",
             zero::Crypto::base64Decrypt(
                 "YWhoM0xpZXF1b29qaXZvemFpNGR1dGgwQWhCb29iMW9oY2lHYWVjaA=="));
    QCOMPARE("welcome to dwai's land",
             zero::Crypto::base64Decrypt("d2VsY29tZSB0byBkd2FpJ3MgbGFuZA=="));
}

void CryptoTest::aesEncrypt() {
    zero::Crypto c;

    c.setEncryptor("meeThajonia5rai7veig8jiebeis9ahP", "oo6eereem4AquiPu");
    QCOMPARE(c.encrypt("Hello there!"),
             "E3gL2eQ0yqxNG2aUxXc4vQ==");
    QCOMPARE(c.encrypt("choh7Oloa1za6upiec7uzaijaeYohthe"),
             "DE0ZRD2gyOL4RYTC+6sLbNP98pjy9+QP0GjaNYScfgLwb5GMgJdD21EXuYbtHSzq");
}

void CryptoTest::aesDecrypt() {
    zero::Crypto c;

    c.setDecryptor("meeThajonia5rai7veig8jiebeis9ahP", "oo6eereem4AquiPu");
    QCOMPARE(c.decrypt("E3gL2eQ0yqxNG2aUxXc4vQ=="),
             "Hello there!");
    QCOMPARE(c.decrypt(
                 "DE0ZRD2gyOL4RYTC+6sLbNP98pjy9+QP0GjaNYScfgLwb5GMgJdD21EXuYbtHSzq"),
             "choh7Oloa1za6upiec7uzaijaeYohthe");
}

QTEST_GUILESS_MAIN(CryptoTest);
