#ifndef CONGE_H
#define CONGE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Conge
    {
    public:
        Conge();

  //getters and setters
        QString getCode() const;
        void setCode(const QString &value);

        QString getAgent() const;
        void setAgent(const QString &value);

        QString getType() const;
        void setType(const QString &value);

        QString getMotif() const;
        void setMotif(const QString &value);

        QDate getDebut() const;
        void setDebut(const QDate &value);

        QDate getFin() const;
        void setFin(const QDate &value);

        QDate getRetour() const;
        void setRetour(const QDate &value);

        bool getSuppr() const;
        void setSuppr(bool value);

  //methodes
        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Existe();
        void Clone(Conge *T);
        bool Equal(Conge *T);
        QString generate();

    private:
        QString code;
        QString agent;
        QString type;
        QString motif;
        QDate debut;
        QDate fin;
        QDate retour;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // CONGE_H
