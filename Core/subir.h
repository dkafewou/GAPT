#ifndef SUBIR_H
#define SUBIR_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Subir
    {
    public:
        Subir();

        QString getDossier() const;
        void setDossier(const QString &value);

        QString getAgent() const;
        void setAgent(const QString &value);

        QString getDepense() const;
        void setDepense(const QString &value);

        QDate getDate() const;
        void setDate(const QDate &value);

        QTime getTime() const;
        void setTime(const QTime &value);

        double getMontant() const;
        void setMontant(double value);

        bool getSuppr() const;
        void setSuppr(bool value);

        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Delete();
        bool Existe();
        void Clone(Subir *T);
        bool Equal(Subir*T);

    private:
        QString dossier;
        QString agent;
        QString depense;
        QDate date;
        QTime time;
        double montant;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // SUBIR_H
