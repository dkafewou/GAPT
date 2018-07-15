#ifndef TRAVAIL_H
#define TRAVAIL_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
class travail
{
public:
    travail();
    QString getAgent() const;
    void setAgent(const QString &value);

    QString getFonction() const;
    void setFonction(const QString &value);

    QString getService() const;
    void setService(const QString &value);

    QDate getDatedebut() const;
    void setDatedebut(const QDate &value);

    QDate getDatefin() const;
    void setDatefin(const QDate &value);

    bool getSuppr() const;
    void setSuppr(bool value);


    bool save();
    bool update();
    bool remove();
    bool restore();
    bool Existe();
    void Clone(travail *T);
    bool Equal(travail *T);


private:
    QString agent;
    QString fonction;
    QString service;
    QDate datedebut;
    QDate datefin;
    bool suppr;

    QSqlQuery *query;

};
}

#endif // TRAVAIL_H
