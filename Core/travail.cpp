#include "travail.h"

using namespace Core;

travail::travail()
{
    query=new QSqlQuery;
}
QString travail::getAgent() const
{
    return agent;
}

void travail::setAgent(const QString &value)
{
    agent = value;
}

QString travail::getFonction() const
{
    return fonction;
}

void travail::setFonction(const QString &value)
{
    fonction = value;
}

QString travail::getService() const
{
    return service;
}

void travail::setService(const QString &value)
{
    service = value;
}

QDate travail::getDatedebut() const
{
    return datedebut;
}

void travail::setDatedebut(const QDate &value)
{
    datedebut = value;
}

QDate travail::getDatefin() const
{
    return datefin;
}

void travail::setDatefin(const QDate &value)
{
    datefin = value;
}

bool travail::getSuppr() const
{
    return suppr;
}

void travail::setSuppr(bool value)
{
    suppr = value;
}


bool travail::save()
{
    query->clear();
    query->prepare("insert into travail values(?,?,?,?,?)");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getFonction());
    query->bindValue(2,this->getService());
    query->bindValue(3,this->getDatedebut());
    query->bindValue(4,this->getDatefin());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool travail::update()
{
    query->clear();
    query->prepare("update travail set Date_Fin=? where IdAgent=? and CodeService=? and CodeFonction=? and Date_Debut=?");
    query->bindValue(0,this->getDatefin());
    query->bindValue(1,this->getAgent());
    query->bindValue(2,this->getService());
    query->bindValue(3,this->getFonction());
    query->bindValue(4,this->getDatedebut());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool travail::remove()
{
    query->clear();
    query->prepare("update travail set SupprTravail=1 where IdAgent=? and CodeFonction=? and CodeService=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getFonction());
    query->bindValue(2,this->getService());
    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool travail::restore()
{
    query->clear();
    query->prepare("update travail set SupprTravail=0 where IdAgent=? and CodeFonction=? and CodeService=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getFonction());
    query->bindValue(2,this->getService());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool travail::Existe()
{
    query->clear();
    query->prepare("select * from travail where IdAgent=? and CodeFonction=? and CodeService=? and Date_Debut=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getFonction());
    query->bindValue(2,this->getService());
    query->bindValue(3,this->getDatedebut());
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

void travail::Clone(travail *T)
{
    this->setAgent(T->getAgent());
    this->setFonction(T->getFonction());
    this->setService(T->getService());
    this->setDatedebut(T->getDatedebut());
    this->setDatefin(T->getDatefin());
}

bool travail::Equal(travail *T)
{
    if(this->agent==T->getAgent()&&this->fonction==T->getFonction()&&this->service==T->getService()&&this->datedebut==T->getDatedebut()&&this->datefin==T->getDatefin())
    return true;
    return false;
}

