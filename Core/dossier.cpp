#include "dossier.h"

using namespace Core;

Dossier::Dossier()
{
    query = new QSqlQuery;
}

QString Dossier::getRep() const
{
    return rep;
}

void Dossier::setRep(const QString &value)
{
    rep = value;
}

QString Dossier::getClient() const
{
    return client;
}

void Dossier::setClient(const QString &value)
{
    client = value;
}

QDate Dossier::getDateRec() const
{
    return dateRec;
}

void Dossier::setDateRec(const QDate &value)
{
    dateRec = value;
}

QDate Dossier::getDateArr() const
{
    return dateArr;
}

void Dossier::setDateArr(const QDate &value)
{
    dateArr = value;
}

bool Dossier::getSuppr() const
{
    return suppr;
}

void Dossier::setSuppr(bool value)
{
    suppr = value;
}

bool Dossier::save()
{
    query->clear();
    query->prepare("insert into dossier values(?,?,?,?,?)");
    query->bindValue(0,this->getRep());
    query->bindValue(1,this->getClient());
    query->bindValue(2,this->getDateRec());
    query->bindValue(3,this->getDateArr());
    query->bindValue(4,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Dossier::update(QString rep)
{
    query->clear();
    query->prepare("update dossier set RepDossier=?,CodeClient=?,DateReception=?,DateArrive=? where RepDossier=?");
    query->bindValue(0,this->getRep());
    query->bindValue(1,this->getClient());
    query->bindValue(2,this->getDateRec());
    query->bindValue(3,this->getDateArr());
    query->bindValue(4,rep);

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Dossier::remove()
{
    query->clear();
    query->prepare("update dossier set SupprDossier=1 where RepDossier=?");
    query->bindValue(0,this->getRep());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Dossier::restore()
{
    query->clear();
    query->prepare("update dossier set SupprDossier=0 where RepDossier=?");
    query->bindValue(0,this->getRep());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Dossier::Existe()
{
    query->clear();
    query->prepare("select * from dossier where RepDossier=?");
    query->bindValue(0,this->getRep());

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

void Dossier::Clone(Dossier *T)
{
    this->setRep(T->getRep());
    this->setClient(T->getClient());
    this->setDateRec(T->getDateRec());
    this->setDateArr(T->getDateArr());
}

bool Dossier::Equal(Dossier *T)
{
    if(this->rep==T->getRep()&&this->client==T->getClient()
            &&this->dateRec==T->getDateRec()&&this->dateArr==T->getDateArr())
        return true;
    return false;
}

bool Core::Dossier::Delete()
{
    query->clear();
       query->prepare("delete from dossier where RepDossier=?");
       query->bindValue(0,this->getRep());

       if(query->exec())
           return true;
       else{
           qDebug() << "Not deleted" << query->lastError();
           return false;
       }
}
