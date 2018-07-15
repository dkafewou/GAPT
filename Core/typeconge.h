#ifndef TYPECONGE_H
#define TYPECONGE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class TypeConge
    {
    public:
        TypeConge();
        QString getCode() const;
        void setCode(const QString &value);

        QString getLibelle() const;
        void setLibelle(const QString &value);

        int getNbrjrs() const;
        void setNbrjrs(int value);

        bool getSuppr() const;
        void setSuppr(bool value);

        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Existe();
        void Clone(TypeConge *T);
        bool Equal(TypeConge *T);
        QString generate();

    private:
        QString code;
        QString libelle;
        int nbrjrs;
        bool suppr;

        QSqlQuery *query;
    };

}
#endif // TYPECONGE_H
