#ifndef SANCTION_H
#define SANCTION_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {

class sanction
{
public:
    sanction();

    QString getCode() const;
    void setCode(const QString &value);

    QString getAgent() const;
    void setAgent(const QString &value);

    QString getMotif() const;
    void setMotif(const QString &value);

    QString getLibelle() const;
    void setLibelle(const QString &value);

    QDate getDate() const;
    void setDate(const QDate &value);

    bool getSuppr() const;
    void setSuppr(bool value);

    bool save();
    bool update();
    bool remove();
    bool restore();
    bool Delete();
    bool Existe();
    void Clone(sanction *T);
    bool Equal(sanction *T);
    QString generate();

private:
    QString code;
    QString agent;
    QString motif;
    QString libelle;
    QDate date;
    bool suppr;

QSqlQuery *query;
};


}

#endif // SANCTION_H
