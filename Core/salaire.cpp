#include "salaire.h"

using namespace Core;

Salaire::Salaire()
{
}

bool Salaire::save()
{
    query = new QSqlQuery;
    query->clear();
    query->prepare("insert into salaire values(?,?,?,?,?,?,?,?,?,?,?)");
    query->bindValue(0,this->generate());
    query->bindValue(1,this->getAgent());
    query->bindValue(2,this->getDateSal());
    query->bindValue(3,this->getBrute());
    query->bindValue(4,this->getSocial());
    query->bindValue(5,this->getTax());
    query->bindValue(6,this->getAssur());
    query->bindValue(7,this->getConge());
    query->bindValue(8,this->getAv());
    query->bindValue(9,this->getPrime());
    query->bindValue(10,this->getSupr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }

}

QString Salaire::getCode() const
{
    return code;
}

void Salaire::setCode(const QString &value)
{
    code = value;
}

QString Salaire::getAgent() const
{
    return agent;
}

void Salaire::setAgent(const QString &value)
{
    agent = value;
}

QDate Salaire::getDateSal() const
{
    return dateSal;
}

void Salaire::setDateSal(const QDate &value)
{
    dateSal = value;
}

double Salaire::getBrute() const
{
    return brute;
}

void Salaire::setBrute(double value)
{
    brute = value;
}

double Salaire::getSocial() const
{
    return social;
}

void Salaire::setSocial(double value)
{
    social = value;
}

double Salaire::getAssur() const
{
    return assur;
}

void Salaire::setAssur(double value)
{
    assur = value;
}

double Salaire::getTax() const
{
    return tax;
}

void Salaire::setTax(double value)
{
    tax = value;
}

double Salaire::getConge() const
{
    return conge;
}

void Salaire::setConge(double value)
{
    conge = value;
}

double Salaire::getAv() const
{
    return Av;
}

void Salaire::setAv(double value)
{
    Av = value;
}

double Salaire::getPrime() const
{
    return prime;
}

void Salaire::setPrime(double value)
{
    prime = value;
}

bool Salaire::getSupr() const
{
    return supr;
}

void Salaire::setSupr(bool value)
{
    supr = value;
}

QString Core::Salaire::generate()
{
    query->clear();
    query->prepare("select count(*) from salaire");
    if(query->exec()){
        query->first();
        return "Sal-"+QString::number(query->value(0).toInt()+1);
    }
    return "Sal-0";
}
