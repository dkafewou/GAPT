#ifndef DOSSIER_H
#define DOSSIER_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Dossier
    {
    public:
        Dossier();

        QString getRep() const;
        void setRep(const QString &value);

        QString getClient() const;
        void setClient(const QString &value);

        QDate getDateRec() const;
        void setDateRec(const QDate &value);

        QDate getDateArr() const;
        void setDateArr(const QDate &value);

        bool getSuppr() const;
        void setSuppr(bool value);

        bool save();
        bool update(QString rep);
        bool remove();
        bool restore();
        bool Delete();
        bool Existe();
        void Clone(Dossier *T);
        bool Equal(Dossier *T);

    private:
        QString rep;
        QString client;
        QDate dateRec;
        QDate dateArr;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // DOSSIER_H
