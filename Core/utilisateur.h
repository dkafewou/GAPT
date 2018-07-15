#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Utilisateur
    {
    public:
        Utilisateur();

        QString getCode() const;
        void setCode(const QString &value);

        QString getAgent() const;
        void setAgent(const QString &value);

        QString getPseudo() const;
        void setPseudo(const QString &value);

        QString getPassword() const;
        void setPassword(const QString &value);

        QString getProfil() const;
        void setProfil(const QString &value);

        QDate getDate() const;
        void setDate(const QDate &value);

        bool getSuppr() const;
        void setSuppr(bool value);

        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Delete();
        bool Existe();
        void Clone(Utilisateur *T);
        bool Equal(Utilisateur*T);
        bool Creer(QString pseud, QString pass);
        QString generate();

    private:
        QString code;
        QString agent;
        QString pseudo;
        QString password;
        QString profil;
        QDate date;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // UTILISATEUR_H
