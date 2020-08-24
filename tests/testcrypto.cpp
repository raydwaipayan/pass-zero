#include "testcrypto.h"
#include <iostream>

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

QTEST_GUILESS_MAIN(CryptoTest);
