#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Client
    {
    public:
        Client();

 //getters &setters
        QString getCode() const;
        void setCode(const QString &value);

        QString getNom() const;
        void setNom(const QString &value);


        QString getTel() const;
        void setTel(const QString &value);

        QString getAdr() const;
        void setAdr(const QString &value);

        QString getPays() const;
        void setPays(const QString &value);


        QString getVille() const;
        void setVille(const QString &value);

        bool getSuppr() const;
        void setSuppr(bool value);

  //methodes
        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Existe();
        void Clone(Client *T);
        bool Equal(Client *T);
        QString generate();

    private:
        QString code;
        QString nom;
        QString tel;
        QString adr;
        QString pays;
        QString ville;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // CLIENT_H
