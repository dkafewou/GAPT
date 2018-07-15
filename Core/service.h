#ifndef SERVICE_H
#define SERVICE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
class service
{
public:
    service();
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
    void Clone(service *T);
    bool Equal(service *T);

private:
    QString code;
    QString libelle;
    double prime;
    bool suppr;

    QSqlQuery *query;
};
}

#endif // SERVICE_H
