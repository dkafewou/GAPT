#ifndef CATEGORIE_H
#define CATEGORIE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Categorie
    {
    public:
        Categorie();

  //getters & setters
        QString getCode() const;
        void setCode(const QString &value);

        QString getLibelle() const;
        void setLibelle(const QString &value);

        double getSalaire() const;
        void setSalaire(double value);

        bool getSuppr() const;
        void setSuppr(bool value);

  //methodes
        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Existe();
        void Clone(Categorie *T);
        bool Equal(Categorie *T);

    private:
        QString code;
        QString libelle;
        double salaire;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // CATEGORIE_H
