#include "dirige.h"

using namespace Core;

Dirige::Dirige()
{
    query = new QSqlQuery;
}

QString Dirige::getAgent() const
{
    return agent;
}

void Dirige::setAgent(const QString &value)
{
    agent = value;
}

QString Dirige::getDirection() const
{
    return direction;
}

void Dirige::setDirection(const QString &value)
{
    direction = value;
}

QDate Dirige::getDebut() const
{
    return debut;
}

void Dirige::setDebut(const QDate &value)
{
    debut = value;
}

QDate Dirige::getFin() const
{
    return fin;
}

void Dirige::setFin(const QDate &value)
{
    fin = value;
}

bool Dirige::getSuppr() const
{
    return suppr;
}

void Dirige::setSuppr(bool value)
{
    suppr = value;
}

bool Dirige::save()
{
    query->clear();
    query->prepare("insert into dirige values(?,?,?,?,?)");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getDirection());
    query->bindValue(2,this->getDebut());
    query->bindValue(3,this->getFin());
    query->bindValue(4,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Dirige::update()
{
    query->clear();
    query->prepare("update dirige set Date_FinD=? where IdAgent=? and CodeDirection=?");
    query->bindValue(0,this->getFin());
    query->bindValue(1,this->getAgent());
    query->bindValue(2,this->getDirection());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Dirige::remove()
{
    query->clear();
    query->prepare("update dirige set SupprD=1 where IdAgent=?and CodeDirection=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getDirection());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Dirige::restore()
{
    query->clear();
    query->prepare("update dirige set SupprD=0 where IdAgent=?and CodeDirection=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getDirection());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Dirige::Existe()
{
    query->clear();
    query->prepare("select * from dirige where IdAgent=? and CodeDirection=? and Date_Deb=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getDirection());
    query->bindValue(2,this->getDebut());

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

void Dirige::Clone(Dirige *T)
{
    this->setAgent(T->getAgent());
    this->setDirection(T->getDirection());
    this->setDebut(T->getDebut());
    this->setFin(T->getFin());
}

bool Dirige::Equal(Dirige *T)
{
    if(this->agent==T->getAgent()&&this->direction==T->getDirection()
            &&this->debut==T->getDebut()&&this->fin==T->getFin())
        return true;
    return false;
}
