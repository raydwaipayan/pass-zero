#include "reader.h"
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>
#include <QDebug>
#include <QFile>

std::string reader::decryptToString(CBC_Mode<AES>::Decryption &decryptor, const QString & ciphertext)
{
    std::string plaintext;
    QByteArray data=ciphertext.toUtf8();

    try{
    ArraySource ss((const byte*)data.data(), data.size(), true,
                    new Base64Decoder(
                        new StreamTransformationFilter(decryptor,
                                                       new StringSink(plaintext))));
    }
    catch(exception &e)
    {
        qDebug()<<e.what()<<"\n";
        //throw e;
    }

    return plaintext;
}

std::string reader::decryptToString(CBC_Mode<AES>::Decryption &decryptor, const std::string & ciphertext)
{
    std::string plaintext;

    try{
    ArraySource ss(ciphertext, true,
                    new Base64Decoder(
                        new StreamTransformationFilter(decryptor,
                                                       new StringSink(plaintext))));
    }
    catch(exception &e)
    {
        qDebug()<<e.what()<<"\n";
        //throw e;
    }

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

bool reader::read(database &d, const QString & masterstring, const QString & filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
          return false;
    }
    QDataStream in(&file);
    try{
        QString msiv, salt;
        in>>msiv>>salt;

        d.masteriv=std::string(msiv.toUtf8());
        d.salt=std::string(salt.toUtf8());

        std::string decmsiv;
        std::string decsalt;
        ArraySource a1((const byte*)d.masteriv.data(), d.masteriv.size(), true,
                        new Base64Decoder(new StringSink(decmsiv)));

        ArraySource a2((const byte*)d.salt.data(), d.salt.size(), true,
                        new Base64Decoder(new StringSink(decsalt)));

        std::string mkstring=database::genKey(std::string(masterstring.toUtf8()), decsalt);
        d.masterkey=SecByteBlock((const byte*)mkstring.data(), mkstring.size());
        SecByteBlock masteriv=SecByteBlock((const byte*)decmsiv.data(), decmsiv.size());
        CBC_Mode<AES>::Decryption decryptorMaster(d.masterkey, d.masterkey.size(), masteriv);


        QString encidentifier;
        in>>encidentifier;
        d.encidentifier=std::string(encidentifier.toUtf8());

        std::string identifier=decryptToString(decryptorMaster,encidentifier);
        if(identifier!=d.identifier){
            return false;
        }

        QString enckey,enciv;
        in>>enckey>>enciv;

        d.encryptedkey=std::string(enckey.toUtf8());
        d.encryptediv=std::string(enciv.toUtf8());

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
    }
    catch(exception &e){
        file.close();
        qDebug()<<e.what()<<"\n";
        return false;
    }

    file.close();
    return true;
}
