#ifndef DIRECTION_H
#define DIRECTION_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Direction
    {
    public:
        Direction();

        QString getCode() const;
        void setCode(const QString &value);

        QString getLibelle() const;
        void setLibelle(const QString &value);

        double getPrime() const;
        void setPrime(double value);

        bool getSuppr() const;
        void setSuppr(bool value);

        bool save();
        bool update(QString value);
        bool remove();
        bool restore();
        bool Existe();
        void Clone(Direction *T);
        bool Equal(Direction *T);

    private:
        QString code;
        QString libelle;
        double prime;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // DIRECTION_H
