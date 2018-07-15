#include "transporteur.h"

using namespace Core;

transporteur::transporteur()
{
    query=new QSqlQuery;
}

QString transporteur::getCode() const
{
    return code;
}

void transporteur::setCode(const QString &value)
{
    code = value;
}

QString transporteur::getNom() const
{
    return nom;
}

void transporteur::setNom(const QString &value)
{
    nom = value;
}

QString transporteur::getPrenom() const
{
    return prenom;
}

void transporteur::setPrenom(const QString &value)
{
    prenom = value;
}

QString transporteur::getTel() const
{
    return tel;
}

void transporteur::setTel(const QString &value)
{
    tel = value;
}

QString transporteur::getAdresse() const
{
    return adresse;
}

void transporteur::setAdresse(const QString &value)
{
    adresse = value;
}

bool transporteur::getSuppr() const
{
    return suppr;
}

void transporteur::setSuppr(bool value)
{
    suppr = value;
}

bool transporteur::save()
{
    query->clear();
    query->prepare("insert into transporteur values(?,?,?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getNom());
    query->bindValue(2,this->getPrenom());
    query->bindValue(3,this->getTel());
    query->bindValue(4,this->getAdresse());
    query->bindValue(5,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool transporteur::update()
{
    query->clear();
    query->prepare("update transporteur set NomTransporteur=?,PrenomTransporteur=?,TelTransporteur=?,AdresseTransporteur=? where CodeTransporteur=?");
    query->bindValue(0,this->getNom());
    query->bindValue(1,this->getPrenom());
    query->bindValue(2,this->getTel());
    query->bindValue(3,this->getAdresse());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool transporteur::remove()
{
    query->clear();
    query->prepare("update transporteur set SupprTansporteur=1 where CodeTransporteur=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool transporteur::restore()
{
    query->clear();
    query->prepare("update transporteur set SupprTansporteur=0 where CodeTransporteur=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool transporteur::Existe()
{
    query->clear();
    query->prepare("select * from transporteur where NomTransporteur=? and TelTransporteur=?");
    query->bindValue(0,this->getNom());
    query->bindValue(1,this->getTel());

    if(query->exec()){
        if(query->first())
            return true;
        return false;
    }
    else{
        qDebug() << "Not executed" << query->lastError();
        return false;
    }
}

void transporteur::Clone(transporteur *T)
{
    this->setCode(T->getCode());
    this->setNom(T->getNom());
    this->setPrenom(T->getPrenom());
    this->setTel(T->getAdresse());
    this->setAdresse(T->getAdresse());
}

bool transporteur::Equal(transporteur *T)
{
    if(this->code==T->getCode()&&this->nom==T->getNom()&&this->prenom==T->getPrenom()&&this->tel==T->getTel()&&this->adresse==T->getAdresse())
        return true;
    return false;
}

QString transporteur::generate()
{
    query->clear();
    query->prepare("select count(*) from Transporteur");
    if(query->exec()){
        query->first();
        return "Transp/0"+QString::number(query->value(0).toInt()+1);
    }
    return "Transp/00";
}

bool Core::transporteur::Delete()
{
    query->clear();
        query->prepare("delete from transporteur where CodeTransporteur=?");
        query->bindValue(0,this->getCode());

        if(query->exec())
            return true;
        else{
            qDebug() << "Not deleted" << query->lastError();
            return false;
        }
}
