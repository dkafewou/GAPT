#include "participant.h"

using namespace Core;

Participant::Participant()
{
    query = new QSqlQuery;
}

QString Participant::getCode() const
{
    return code;
}

void Participant::setCode(const QString &value)
{
    code = value;
}

QString Participant::getAgent() const
{
    return agent;
}

void Participant::setAgent(const QString &value)
{
    agent = value;
}

bool Participant::getSuppr() const
{
    return Suppr;
}

void Participant::setSuppr(bool value)
{
    Suppr = value;
}

bool Participant::save()
{
    query->clear();
    query->prepare("insert into participant values(?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getAgent());
    query->bindValue(2,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Participant::update()
{
    query->clear();
    query->prepare("update participant set IdAgent=? where CodeFormation=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Participant::remove()
{
    query->clear();
    query->prepare("update participant set SupprPart=1 where IdAgent=? and CodeFormation=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Participant::restore()
{
    query->clear();
    query->prepare("update participant set SupprPart=0 where IdAgent=? and CodeFormation=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Participant::Delete()
{
    query->clear();
    query->prepare("delete from participant where IdAgent=? and CodeFormation=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not deleted" << query->lastError();
        return false;
    }
}

bool Participant::Existe()
{
    query->clear();
    query->prepare("select * from participant where IdAgent=? and CodeFormation=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getCode());

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

void Participant::Clone(Participant *T)
{
    this->setCode(T->getCode());
    this->setAgent(T->getAgent());
}

bool Participant::Equal(Participant *T)
{
    if(this->code==T->getCode()&&this->agent==T->getAgent())
        return true;
    return false;
}
