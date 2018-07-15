#ifndef REGLEMENT_H
#define REGLEMENT_H

#include <QString>
#include <QDate>
#include <QTime>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Reglement
    {
    public:
        Reglement();

        QString getCode() const;
        void setCode(const QString &value);

        QString getTransport() const;
        void setTransport(const QString &value);

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
        bool Existe();
        void Clone(Reglement *T);
        bool Equal(Reglement*T);
        QString generate();

    private:
        QString code;
        QString transport;
        QDate date;
        QTime time;
        double montant;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // REGLEMENT_H
