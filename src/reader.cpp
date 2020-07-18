#include "reader.h"
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>
#include <QDebug>
#include <QFile>


std::string reader::decryptToString(CBC_Mode<AES>::Decryption &decryptor, const QString & ciphertext)
{
    std::string plaintext;
    QByteArray data=ciphertext.toUtf8();


    ArraySource ss((const byte*)data.data(), data.size(), true,
                    new Base64Decoder(
                        new StreamTransformationFilter(decryptor,
                                                       new StringSink(plaintext))));
    return plaintext;
}

std::string reader::decryptToString(CBC_Mode<AES>::Decryption &decryptor, const std::string & ciphertext)
{
    std::string plaintext;

    ArraySource ss(ciphertext, true,
                    new Base64Decoder(
                        new StreamTransformationFilter(decryptor,
                                                       new StringSink(plaintext))));
    return plaintext;
}
QString reader::decryptToQString(CBC_Mode<AES>::Decryption &decryptor, const QString & ciphertext)
{
    std::string plaintext;
    QByteArray data=ciphertext.toUtf8();

    ArraySource ss((const byte*)data.data(), data.size(), true,
                    new Base64Decoder(
                        new StreamTransformationFilter(decryptor,
                                                       new StringSink(plaintext))));
    return QString::fromUtf8(plaintext.c_str());
}

bool reader::read(database &d, const QString & filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
//        QMessageBox::information(this,tr("Unable to open file"),file.errorString());
          return false;
    }
    QDataStream in(&file);
    QString msiv;
    in>>msiv;

    d.masteriv=std::string(msiv.toUtf8());

    std::string decmsiv;
    ArraySource ss((const byte*)d.masteriv.data(), d.masteriv.size(), true,
                    new Base64Decoder(new StringSink(decmsiv)));

    SecByteBlock masteriv=SecByteBlock((const byte*)decmsiv.data(), decmsiv.size());
    CBC_Mode<AES>::Decryption decryptorMaster(d.masterkey, d.masterkey.size(), masteriv);


    QString encidentifier;
    in>>encidentifier;

    std::string identifier=decryptToString(decryptorMaster,encidentifier);
    if(identifier!=d.identifier){
        qDebug()<<"Identifier: "<<QString::fromStdString(identifier)<<"\n";
        return false;
    }

    QString enckey,enciv;
    in>>enckey>>enciv;

    std::string skey=decryptToString(decryptorMaster, enckey);
    std::string siv=decryptToString(decryptorMaster, enciv);

    d.key=SecByteBlock((const byte*)(skey.data()),skey.size());
    d.iv=SecByteBlock((const byte*)(siv.data()),siv.size());
    CBC_Mode<AES>::Decryption decryptor(d.key, d.key.size(), d.iv);
    in>>d.data;
    for(auto &x:d.data)
    {
        x.label=decryptToQString(decryptor,x.getLabel());
        x.user=decryptToQString(decryptor, x.getUser());
        x.pass=decryptToQString(decryptor, x.getPass());
        x.note=decryptToQString(decryptor, x.getNote());
    }
    file.close();
    return true;
}
