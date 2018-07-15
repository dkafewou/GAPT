#ifndef TYPEDEPART_H
#define TYPEDEPART_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class TypeDepart
    {
    public:
        TypeDepart();
        QString getCode() const;
        void setCode(const QString &value);

        QString getLibelle() const;
        void setLibelle(const QString &value);

        bool getSuppr() const;
        void setSuppr(bool value);

        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Existe();
        void Clone(TypeDepart *T);
        bool Equal(TypeDepart *T);
        QString generate();

    private:
        QString code;
        QString libelle;
        bool suppr;

        QSqlQuery *query;
    };

}
#endif // TYPEDEPART_H
