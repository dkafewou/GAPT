#ifndef TRANSPORTEUR_H
#define TRANSPORTEUR_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
class transporteur
{
public:
    transporteur();
    QString getCode() const;
    void setCode(const QString &value);

    QString getNom() const;
    void setNom(const QString &value);

    QString getPrenom() const;
    void setPrenom(const QString &value);

    QString getTel() const;
    void setTel(const QString &value);

    QString getAdresse() const;
    void setAdresse(const QString &value);

    bool getSuppr() const;
    void setSuppr(bool value);

    bool save();
    bool update();
    bool remove();
    bool restore();
    bool Existe();
    bool Delete();
    void Clone(transporteur *T);
    bool Equal(transporteur *T);
    QString generate();

private:
    QString code;
    QString nom;
    QString prenom;
    QString tel;
    QString adresse;
    bool suppr;

    QSqlQuery *query;
};
}

#endif // TRANSPORTEUR_H
