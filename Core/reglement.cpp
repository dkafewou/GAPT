#include "reglement.h"

using namespace Core;

Reglement::Reglement()
{
    query = new QSqlQuery;
}

QString Reglement::getCode() const
{
    return code;
}

void Reglement::setCode(const QString &value)
{
    code = value;
}

QString Reglement::getTransport() const
{
    return transport;
}

void Reglement::setTransport(const QString &value)
{
    transport = value;
}

QDate Reglement::getDate() const
{
    return date;
}

void Reglement::setDate(const QDate &value)
{
    date = value;
}

QTime Reglement::getTime() const
{
    return time;
}

void Reglement::setTime(const QTime &value)
{
    time = value;
}

double Reglement::getMontant() const
{
    return montant;
}

void Reglement::setMontant(double value)
{
    montant = value;
}

bool Reglement::getSuppr() const
{
    return suppr;
}

void Reglement::setSuppr(bool value)
{
    suppr = value;
}

bool Reglement::save()
{
    query->clear();
    query->prepare("insert into reglement values(?,?,?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getTransport());
    query->bindValue(2,this->getDate());
    query->bindValue(3,this->getTime());
    query->bindValue(4,this->getMontant());
    query->bindValue(5,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Reglement::update()
{
    query->clear();
    query->prepare("update reglement set DateRegl=?,HeureRegl=?,MontantRegl=? where CodeRegl=?");
    query->bindValue(0,this->getDate());
    query->bindValue(1,this->getTime());
    query->bindValue(2,this->getMontant());
    query->bindValue(3,this->getCode());
    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Reglement::remove()
{
    query->clear();
    query->prepare("update reglement set SupprRegl=1 where CodeRegl=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Reglement::restore()
{
    query->clear();
    query->prepare("update reglement set SupprRegl=0 where CodeRegl=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Reglement::Existe()
{
    query->clear();
    query->prepare("select * from reglement where CodeTransp=? and DateRegl=?");
    query->bindValue(0,this->getTransport());
    query->bindValue(1,this->getDate());

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

void Reglement::Clone(Reglement *T)
{
    this->setCode(T->getCode());
    this->setTransport(T->getTransport());
    this->setDate(T->getDate());
    this->setTime(T->getTime());
    this->setMontant(T->getMontant());
}

bool Reglement::Equal(Reglement *T)
{
    if(this->code==T->getCode()&&this->transport==T->getTransport()
            &&this->date==T->getDate()&&this->time==T->getTime()&&this->montant==T->getMontant())
        return true;
    return false;
}

QString Reglement::generate()
{
    query->clear();
    query->prepare("select count(*) from reglement");
    if(query->exec()){
        query->first();
        return "Regl-0"+QString::number(query->value(0).toInt()+1);
    }
    else {
        qDebug() << "Not generate" << query->lastError();
    }
    return "Regl-00";
}
