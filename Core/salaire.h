#ifndef SALAIRE_H
#define SALAIRE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Salaire
    {
    public:
        Salaire();
        bool save();
        QString generate();

        QString getCode() const;
        void setCode(const QString &value);

        QString getAgent() const;
        void setAgent(const QString &value);

        QDate getDateSal() const;
        void setDateSal(const QDate &value);

        double getBrute() const;
        void setBrute(double value);

        double getSocial() const;
        void setSocial(double value);

        double getAssur() const;
        void setAssur(double value);

        double getTax() const;
        void setTax(double value);

        double getConge() const;
        void setConge(double value);

        double getAv() const;
        void setAv(double value);

        double getPrime() const;
        void setPrime(double value);

        bool getSupr() const;
        void setSupr(bool value);

    private:

        QSqlQuery *query;
        QString code,agent;
        QDate dateSal;
        double brute,social,assur,tax,conge,Av,prime;
        bool supr;
    };
}

#endif // SALAIRE_H
