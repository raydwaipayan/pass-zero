#include <QFile>
#include <iostream>
#include "reader.h"
#include "crypto.h"

void Reader::read(database     & d,
                  const QString& masterstring,
                  const QString& filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("Failed to open file");
    }
    QDataStream in(&file);
    Crypto crypto;

    try {
        QString q_msiv, q_salt, q_identifier, q_dbkey, q_dbiv;
        in >> q_msiv >> q_salt >> q_identifier >> q_dbkey >> q_dbiv;

        d.master_iv  = crypto.base64Decrypt(std::string(q_msiv.toUtf8()));
        d.salt       = crypto.base64Decrypt(std::string(q_salt.toUtf8()));
        d.master_key = crypto.genKey(std::string(masterstring.toUtf8()), d.salt);

        QString::fromStdString(d.master_iv);
        crypto.setDecryptor(d.master_key, d.master_iv);

        std::string identifier =
            crypto.decrypt(std::string(q_identifier.toUtf8()));

        if (identifier != d.identifier) {
            throw std::runtime_error("Wrong passcode or corrupted database");
        }
        d.db_key = crypto.decrypt(std::string(q_dbkey.toUtf8()));
        d.db_iv  = crypto.decrypt(std::string(q_dbiv.toUtf8()));

        crypto.setDecryptor(d.db_key, d.db_iv);
        in >> d.data;

        for (auto& x:d.data)
        {
            std::string label, user, pass, note;
            label   = crypto.decrypt(std::string(x.label.toUtf8()));
            user    = crypto.decrypt(std::string(x.user.toUtf8()));
            pass    = crypto.decrypt(std::string(x.pass.toUtf8()));
            note    = crypto.decrypt(std::string(x.note.toUtf8()));
            x.label = QString::fromStdString(label);
            x.user  = QString::fromStdString(user);
            x.pass  = QString::fromStdString(pass);
            x.note  = QString::fromStdString(note);
        }
    }
    catch (exception& e) {
        file.close();
        throw std::runtime_error("Incorrect password!");
    }
    file.close();
}
