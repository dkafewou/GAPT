#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
class transport
{
public:
    transport();
    QString getCode() const;
    void setCode(const QString &value);

    QString getConteneur() const;
    void setConteneur(const QString &value);

    QString getTransporteur() const;
    void setTransporteur(const QString &value);

    QDate getDatetransp() const;
    void setDatetransp(const QDate &value);

    QDate getDateretour() const;
    void setDateretour(const QDate &value);

    bool getSuppr() const;
    void setSuppr(bool value);

    bool save();
    bool update();
    bool remove();
    bool restore();
    bool Delete();
    bool Existe();
    void Clone(transport *T);
    bool Equal(transport *T);
    QString generate();

private:
    QString code;
    QString conteneur;
    QString transporteur;
    QDate datetransp;
    QDate dateretour;
    bool suppr;

    QSqlQuery *query;

};
}

#endif // TRANSPORT_H
