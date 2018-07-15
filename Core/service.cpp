#include "service.h"

using namespace Core;

service::service()
{
    query=new QSqlQuery;
}

QString service::getCode() const
{
    return code;
}

void service::setCode(const QString &value)
{
    code = value;
}

QString service::getLibelle() const
{
    return libelle;
}

void service::setLibelle(const QString &value)
{
    libelle = value;
}

double service::getPrime() const
{
    return prime;
}

void service::setPrime(double value)
{
    prime = value;
}

bool service::getSuppr() const
{
    return suppr;
}

void service::setSuppr(bool value)
{
    suppr = value;
}

bool service::save()
{
    query->clear();
    query->prepare("insert into service values(?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getLibelle());
    query->bindValue(2,this->getPrime());
    query->bindValue(3,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool service::update(QString value)
{
    query->clear();
    query->prepare("update service set CodeService=?,LibelleService=?,PrimeChef=? where CodeService=?");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getLibelle());
    query->bindValue(2,this->getPrime());
    query->bindValue(3,value);

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool service::remove()
{
    query->clear();
    query->prepare("update service set SupprService=1 where CodeService=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool service::restore()
{
    query->clear();
    query->prepare("update service set SupprService=0 where CodeService=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool service::Existe()
{
    query->clear();
    query->prepare("select * from service where LibelleService=? and PrimeChef=? ");
    query->bindValue(0,this->getLibelle());
    query->bindValue(1,this->getPrime());

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

void service::Clone(service *T)
{
    this->setCode(T->getCode());
    this->setLibelle(T->getLibelle());
    this->setPrime(T->getPrime());
}

bool service::Equal(service *T)
{
    if(this->code==T->getCode()&&this->libelle==T->getLibelle()&&this->prime==T->getPrime())
        return true;
    return false;
}
