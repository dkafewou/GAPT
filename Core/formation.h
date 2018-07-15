#ifndef FORMATION_H
#define FORMATION_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Formation
    {
    public:
        Formation();

        QString getCode() const;
        void setCode(const QString &value);

        QString getLibelle() const;
        void setLibelle(const QString &value);

        QString getVille() const;
        void setVille(const QString &value);

        QString getPays() const;
        void setPays(const QString &value);

        QDate getDebut() const;
        void setDebut(const QDate &value);

        QDate getFin() const;
        void setFin(const QDate &value);

        QDate getReel() const;
        void setReel(const QDate &value);

        bool getSuppr() const;
        void setSuppr(bool value);

        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Delete();
        bool Existe();
        void Clone(Formation *T);
        bool Equal(Formation *T);
        QString generate();

    private:
        QString code;
        QString libelle;
        QString ville;
        QString pays;
        QDate debut;
        QDate fin;
        QDate reel;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // FORMATION_H
