#include "writer.h"
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>
#include <QDebug>
#include <QFile>

std::string writer::encryptToString(CBC_Mode<AES>::Encryption &encryptor, const std::string &plaintext)
{
    std::string ciphertext;
    ArraySource ss(plaintext,true,
                        new StreamTransformationFilter(encryptor,
                            new Base64Encoder(new StringSink(ciphertext))));
    return ciphertext;
}
QString writer::encryptToQString(CBC_Mode<AES>::Encryption &encryptor, const QString &plaintext)
{
    QByteArray data=plaintext.toUtf8();
    std::string ciphertext;
    ArraySource ss((const byte*)data.data(), data.size(), true,
                        new StreamTransformationFilter(encryptor,
                            new Base64Encoder(new StringSink(ciphertext))));

    return QString::fromUtf8((ciphertext.c_str()));
}

void writer::write(database d, const QString & filename)
{
    CBC_Mode<AES>::Encryption encryptor(d.key, d.key.size(), d.iv);
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
//        QMessageBox::information(this,tr("Unable to open file"),file.errorString());
        return;
    }

    QDataStream out(&file);
    out<<QString::fromStdString(d.masteriv);
    out<<QString::fromStdString(d.encidentifier);
    out<<QString::fromStdString(d.encryptedkey);
    out<<QString::fromStdString(d.encryptediv);

    for(auto &x:d.data)
    {
        x.label=encryptToQString(encryptor,x.getLabel());
        x.user=encryptToQString(encryptor,x.getUser());
        x.pass=encryptToQString(encryptor,x.getPass());
        x.note=encryptToQString(encryptor,x.getNote());
    }
    out<<d.data;
    file.close();
}
