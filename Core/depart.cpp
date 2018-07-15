#include "depart.h"

using namespace Core;

Depart::Depart()
{
    query = new QSqlQuery;
}

QString Depart::getCode() const
{
    return code;
}

void Depart::setCode(const QString &value)
{
    code = value;
}

QString Depart::getType() const
{
    return type;
}

void Depart::setType(const QString &value)
{
    type = value;
}

QString Depart::getAgent() const
{
    return agent;
}

void Depart::setAgent(const QString &value)
{
    agent = value;
}

QString Depart::getMotif() const
{
    return motif;
}

void Depart::setMotif(const QString &value)
{
    motif = value;
}

QDate Depart::getDdep() const
{
    return Ddep;
}

void Depart::setDdep(const QDate &value)
{
    Ddep = value;
}

bool Depart::getSuppr() const
{
    return suppr;
}

void Depart::setSuppr(bool value)
{
    suppr = value;
}

bool Depart::save()
{
    query->clear();
    query->prepare("insert into depart values(?,?,?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getType());
    query->bindValue(2,this->getAgent());
    query->bindValue(3,this->getMotif());
    query->bindValue(4,this->getDdep());
    query->bindValue(5,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Depart::update()
{
    query->clear();
    query->prepare("update depart set CodeTypeDepart=?,MotifDepart=?,DateDepart=? where CodeDepart=?");
    query->bindValue(0,this->getType());
    query->bindValue(1,this->getMotif());
    query->bindValue(2,this->getDdep());
    query->bindValue(3,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Depart::remove()
{
    query->clear();
    query->prepare("update depart set SupprDepart=1 where CodeDepart=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Depart::restore()
{
    query->clear();
    query->prepare("update depart set SupprDepart=0 where CodeDepart=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Depart::Existe()
{
    query->clear();
    query->prepare("select * from depart where CodeTypeDepart=? and IdAgent=?");
    query->bindValue(0,this->getType());
    query->bindValue(1,this->getAgent());

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

void Depart::Clone(Depart *T)
{
    this->setCode(T->getCode());
    this->setType(T->getType());
    this->setAgent(T->getAgent());
    this->setMotif(T->getMotif());
    this->setDdep(T->getDdep());
}

bool Depart::Equal(Depart *T)
{
    if(this->code==T->getCode()&&this->type==T->getType()
            &&this->agent==T->getAgent()&&this->motif==T->getMotif()
            &&this->Ddep==T->getDdep())
        return true;
    return false;
}

QString Depart::generate()
{
    query->clear();
    query->prepare("select count(*) from depart");
    if(query->exec()){
        query->first();
        return "Dep00"+QString::number(query->value(0).toInt()+1);
    }
    return "Dep000";
}
