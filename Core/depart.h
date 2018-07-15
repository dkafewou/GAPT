#ifndef DEPART_H
#define DEPART_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Depart
    {
    public:
        Depart();

    //getters and setters
        QString getCode() const;
        void setCode(const QString &value);

        QString getType() const;
        void setType(const QString &value);

        QString getAgent() const;
        void setAgent(const QString &value);

        QString getMotif() const;
        void setMotif(const QString &value);

        QDate getDdep() const;
        void setDdep(const QDate &value);

        bool getSuppr() const;
        void setSuppr(bool value);

    //methodes
        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Existe();
        void Clone(Depart *T);
        bool Equal(Depart *T);
        QString generate();

    private:
        QString code;
        QString type;
        QString agent;
        QString motif;
        QDate Ddep;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // DEPART_H
