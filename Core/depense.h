#ifndef DEPENSE_H
#define DEPENSE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Depense
    {
    public:
        Depense();

        QString getCode() const;
        void setCode(const QString &value);

        QString getLibelle() const;
        void setLibelle(const QString &value);

        double getMontant() const;
        void setMontant(double value);

        bool getSuppr() const;
        void setSuppr(bool value);

        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Existe();
        void Clone(Depense *T);
        bool Equal(Depense *T);
        QString generate();

    private:
        QString code;
        QString libelle;
        double montant;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // DEPENSE_H
