#include "transport.h"

using namespace Core;

transport::transport()
{
    query=new QSqlQuery;
}

QString transport::getCode() const
{
    return code;
}

void transport::setCode(const QString &value)
{
    code = value;
}

QString transport::getConteneur() const
{
    return conteneur;
}

void transport::setConteneur(const QString &value)
{
    conteneur = value;
}

QString transport::getTransporteur() const
{
    return transporteur;
}

void transport::setTransporteur(const QString &value)
{
    transporteur = value;
}

QDate transport::getDatetransp() const
{
    return datetransp;
}

void transport::setDatetransp(const QDate &value)
{
    datetransp = value;
}

QDate transport::getDateretour() const
{
    return dateretour;
}

void transport::setDateretour(const QDate &value)
{
    dateretour = value;
}

bool transport::getSuppr() const
{
    return suppr;
}

void transport::setSuppr(bool value)
{
    suppr = value;
}

bool transport::save()
{
    query->clear();
    query->prepare("insert into transport values(?,?,?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getConteneur());
    query->bindValue(2,this->getTransporteur());
    query->bindValue(3,this->getDatetransp());
    query->bindValue(4,this->getDateretour());
    query->bindValue(5,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool transport::update()
{
    query->clear();
    query->prepare("update transport set DateTransp=?,DateRetour=? where CodeTransp=?");
    query->bindValue(0,this->getDatetransp());
    query->bindValue(1,this->getDateretour());
    query->bindValue(2,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool transport::remove()
{
    query->clear();
    query->prepare("update transport set SupprTansp=1 where CodeTransp=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool transport::restore()
{
    query->clear();
    query->prepare("update transport set SupprTansp=0 where CodeTransp=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool transport::Delete()
{
    query->clear();
    query->prepare("delete from transport where CodeTransp=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not deleted" << query->lastError();
        return false;
    }
}
bool transport::Existe()
{
    query->clear();
    query->prepare("select * from transport where CodeConteneur=? and CodeTransporteur=? and DateTransp=? and DateRetour=?");
    query->bindValue(0,this->getConteneur());
    query->bindValue(1,this->getTransporteur());
    query->bindValue(2,this->getDatetransp());
    query->bindValue(3,this->getDateretour());

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

void transport::Clone(transport *T)
{
    this->setCode(T->getCode());
    this->setConteneur(T->getConteneur());
    this->setTransporteur(T->getTransporteur());
    this->setDatetransp(T->getDatetransp());
    this->setDateretour(T->getDateretour());
}

bool transport::Equal(transport *T)
{
    if(this->code==T->getCode()&&this->conteneur==T->getConteneur()&&this->transporteur==T->getTransporteur()&&this->datetransp==T->getDatetransp()&&this->dateretour==T->getDateretour())
        return true;
    return false;
}

QString transport::generate()
{
    query->clear();
    query->prepare("select count(*) from transport");
    if(query->exec()){
        query->first();
        return "Tran0"+QString::number(query->value(0).toInt()+1);
    }
    return "TransOO";
}
