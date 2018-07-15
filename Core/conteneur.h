#ifndef CONTENEUR_H
#define CONTENEUR_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Conteneur
    {
    public:
        Conteneur();

   //getters and setters
        QString getCode() const;
        void setCode(const QString &value);

        QString getRep() const;
        void setRep(const QString &value);

        QString getNumero() const;
        void setNumero(const QString &value);

        QString getType() const;
        void setType(const QString &value);

        QString getMarchandise() const;
        void setMarchandise(const QString &value);

        bool getSuppr() const;
        void setSuppr(bool value);

   //methodes
        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Delete();
        bool Existe();
        void Clone(Conteneur *T);
        bool Equal(Conteneur *T);
        QString generate();

    private:
        QString code;
        QString rep;
        QString numero;
        QString type;
        QString marchandise;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // CONTENEUR_H
