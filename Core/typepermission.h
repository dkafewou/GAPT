#ifndef TYPEPERMISSION_H
#define TYPEPERMISSION_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class TypePermission
    {
    public:
        TypePermission();

        QString getCode() const;
        void setCode(const QString &value);

        QString getLibelle() const;
        void setLibelle(const QString &value);

        int getNbrJours() const;
        void setNbrJours(int value);

        bool getSuppr() const;
        void setSuppr(bool value);

        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Existe();
        void Clone(TypePermission *T);
        bool Equal(TypePermission *T);
        QString generate();

    private:
        QString code;
        QString libelle;
        int nbrJours;
        bool suppr;

        QSqlQuery *query;
    };
}

#endif // TYPEPERMISSION_H
