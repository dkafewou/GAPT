#include "client.h"

using namespace Core;

Client::Client()
{
    query = new QSqlQuery;
}

QString Client::getCode() const
{
    return code;
}

void Client::setCode(const QString &value)
{
    code = value;
}

QString Client::getNom() const
{
    return nom;
}

void Client::setNom(const QString &value)
{
    nom = value;
}

QString Client::getTel() const
{
    return tel;
}

void Client::setTel(const QString &value)
{
    tel = value;
}

QString Client::getAdr() const
{
    return adr;
}

void Client::setAdr(const QString &value)
{
    adr = value;
}

QString Client::getPays() const
{
    return pays;
}

void Client::setPays(const QString &value)
{
    pays = value;
}

QString Client::getVille() const
{
    return ville;
}

void Client::setVille(const QString &value)
{
    ville = value;
}

bool Client::getSuppr() const
{
    return suppr;
}

void Client::setSuppr(bool value)
{
    suppr = value;
}

bool Client::save()
{
    query->clear();
    query->prepare("insert into client values(?,?,?,?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getNom());
    query->bindValue(2,this->getTel());
    query->bindValue(3,this->getAdr());
    query->bindValue(4,this->getPays());
    query->bindValue(5,this->getVille());
    query->bindValue(6,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Client::update()
{
    query->clear();
    query->prepare("update client set NomClient=?,TelClient=?,AdresseClient=?,Pays=?,Ville=? where CodeClient=?");
    query->bindValue(0,this->getNom());
    query->bindValue(1,this->getTel());
    query->bindValue(2,this->getAdr());
    query->bindValue(3,this->getPays());
    query->bindValue(4,this->getVille());
    query->bindValue(5,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Client::remove()
{
    query->clear();
    query->prepare("update client set SupprClient=1 where CodeClient=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Client::restore()
{
    query->clear();
    query->prepare("update client set SupprClient=0 where CodeClient=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Client::Existe()
{
    query->clear();
    query->prepare("select * from client where NomClient=?");
    query->bindValue(0,this->getNom());

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

void Client::Clone(Client *T)
{
    this->setCode(T->getCode());
    this->setNom(T->getNom());
    this->setTel(T->getTel());
    this->setAdr(T->getAdr());
    this->setPays(T->getPays());
    this->setVille(T->getVille());
}

bool Client::Equal(Client *T)
{
    if(this->code==T->getCode()&&this->nom==T->getNom()
            &&this->tel==T->getTel()&&this->adr==T->getAdr()
            &&this->pays==T->getPays()&&this->ville==T->getVille())
        return true;
    return false;
}

QString Client::generate()
{
    query->clear();
    query->prepare("select count(*) from client");
    if(query->exec()){
        query->first();
        return "Client0"+QString::number(query->value(0).toInt()+1);
    }
    return "Client00";
}

