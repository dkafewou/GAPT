#ifndef FONCTION_H
#define FONCTION_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Fonction
    {
    public:
        Fonction();

        QString getCode() const;
        void setCode(const QString &value);

        QString getLibelle() const;
        void setLibelle(const QString &value);

        bool getSuppr() const;
        void setSuppr(bool value);

        bool save();
        bool update(QString value);
        bool remove();
        bool restore();
        bool Existe();
        void Clone(Fonction *T);
        bool Equal(Fonction *T);

    private:
        QString code;
        QString libelle;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // FONCTION_H
