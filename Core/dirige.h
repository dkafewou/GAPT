#ifndef DIRIGE_H
#define DIRIGE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Dirige
    {
    public:
        Dirige();

    //getters & setters
        QString getAgent() const;
        void setAgent(const QString &value);

        QString getDirection() const;
        void setDirection(const QString &value);

        QDate getDebut() const;
        void setDebut(const QDate &value);

        QDate getFin() const;
        void setFin(const QDate &value);

        bool getSuppr() const;
        void setSuppr(bool value);

    //methodes
        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Existe();
        void Clone(Dirige *T);
        bool Equal(Dirige *T);

    private:
        QString agent;
        QString direction;
        QDate debut;
        QDate fin;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // DIRIGE_H
