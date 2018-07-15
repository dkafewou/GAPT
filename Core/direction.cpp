#include "direction.h"

using namespace Core;

Direction::Direction()
{
    query = new QSqlQuery;
}

QString Direction::getCode() const
{
    return code;
}

void Direction::setCode(const QString &value)
{
    code = value;
}

QString Direction::getLibelle() const
{
    return libelle;
}

void Direction::setLibelle(const QString &value)
{
    libelle = value;
}

double Direction::getPrime() const
{
    return prime;
}

void Direction::setPrime(double value)
{
    prime = value;
}

bool Direction::getSuppr() const
{
    return suppr;
}

void Direction::setSuppr(bool value)
{
    suppr = value;
}

bool Direction::save()
{
    query->clear();
    query->prepare("insert into direction values(?,?,?,?)");
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

bool Direction::update(QString value)
{
    query->clear();
    query->prepare("update direction set CodeDirection=?,LibelleDirection=?,Prime=? where CodeDirection=?");
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

bool Direction::remove()
{
    query->clear();
    query->prepare("update direction set SupprDirection=1 where CodeDirection=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Direction::restore()
{
    query->clear();
    query->prepare("update direction set SupprDirection=0 where CodeDirection=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Direction::Existe()
{
    query->clear();
    query->prepare("select * from direction where LibelleDirection=?");
    query->bindValue(0,this->getLibelle());

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

void Direction::Clone(Direction *T)
{
    this->setCode(T->getCode());
    this->setLibelle(T->getLibelle());
    this->setPrime(T->getPrime());
}

bool Direction::Equal(Direction *T)
{
    if(this->code==T->getCode()&&this->libelle==T->getLibelle()&&this->prime==T->getPrime())
        return true;
    return false;
}
