#include <QFile>
#include <QDebug>
#include "writer.h"
#include "crypto.h"


bool zero::Writer::write(database d, const QString& filename)
{
    Crypto crypto;

    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return false;
    }

    try {
        QDataStream out(&file);

        QString master_iv, salt, identifier, db_key, db_iv;

        master_iv = QString::fromStdString(crypto.base64Encrypt(d.master_iv));
        salt      = QString::fromStdString(crypto.base64Encrypt(d.salt));

        crypto.setEncryptor(d.master_key, d.master_iv);
        identifier = QString::fromStdString(crypto.encrypt(d.identifier));
        db_key     = QString::fromStdString(crypto.encrypt(d.db_key));
        db_iv      = QString::fromStdString(crypto.encrypt(d.db_iv));

        out << master_iv << salt << identifier << db_key << db_iv;

        crypto.setEncryptor(d.db_key, d.db_iv);

        for (auto& x:d.data)
        {
            x.label =
                QString::fromStdString(crypto.encrypt(std::string(
                                                          x.label.toUtf8())));
            x.user =
                QString::fromStdString(crypto.encrypt(std::string(
                                                          x.user.toUtf8())));
            x.pass =
                QString::fromStdString(crypto.encrypt(std::string(
                                                          x.pass.toUtf8())));
            x.note =
                QString::fromStdString(crypto.encrypt(std::string(
                                                          x.note.toUtf8())));
        }
        out << d.data;
    }
    catch (std::exception& e)
    {
        file.close();
        qDebug() << e.what();
        return false;
    }
    file.close();
    return true;
}
