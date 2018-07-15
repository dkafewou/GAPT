#include "sanction.h"

using namespace Core;
sanction::sanction()
{
    query = new QSqlQuery;
}

QString sanction::getCode() const
{
    return code;
}

void sanction::setCode(const QString &value)
{
    code = value;
}

QString sanction::getAgent() const
{
    return agent;
}

void sanction::setAgent(const QString &value)
{
    agent = value;
}

QString sanction::getMotif() const
{
    return motif;
}

void sanction::setMotif(const QString &value)
{
    motif = value;
}

QString sanction::getLibelle() const
{
    return libelle;
}

void sanction::setLibelle(const QString &value)
{
    libelle = value;
}

QDate sanction::getDate() const
{
    return date;
}

void sanction::setDate(const QDate &value)
{
    date = value;
}

bool sanction::getSuppr() const
{
    return suppr;
}

void sanction::setSuppr(bool value)
{
    suppr = value;
}

bool sanction::save()
{
    query->clear();
    query->prepare("insert into sanction values(?,?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getAgent());
    query->bindValue(2,this->getMotif());
    query->bindValue(3,this->getDate());
    query->bindValue(4,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool sanction::update()
{
    query->clear();
    query->prepare("update sanction set MotifSanction=?,DateSanction=? where CodeSanction=?");
    query->bindValue(0,this->getMotif());
    query->bindValue(1,this->getDate());
    query->bindValue(2,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool sanction::remove()
{
    query->clear();
    query->prepare("update sanction set SupprSanction=1 where CodeSanction=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool sanction::restore()
{
    query->clear();
    query->prepare("update sanction set SupprSanction=0 where CodeSanction=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool sanction::Existe()
{
    query->clear();
    query->prepare("select * from sanction where IdAgent=? and MotifSanction=? and DateSanction=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getMotif());
    query->bindValue(3,this->getDate());

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

void sanction::Clone(sanction *T)
{
    this->setCode(T->getCode());
    this->setAgent(T->getAgent());
    this->setMotif(T->getMotif());
    this->setDate(T->getDate());
}

bool sanction::Equal(sanction *T)
{
    if(this->code==T->getCode()&&this->agent==T->getAgent()&&this->motif==T->getMotif()&&this->date==T->getDate())
        return true;
    return false;
}

QString sanction::generate()
{
    query->clear();
    query->prepare("select count(*) from sanction where IdAgent=?");
    query->bindValue(0,this->getAgent());
    if(query->exec()){
        query->first();
        return this->agent.left(3)+"/"+"Sanc"+QString::number(query->value(0).toInt()+1);
    }
    return "Sanc001";
}

bool Core::sanction::Delete()
{
    query->clear();
        query->prepare("delete from sanction where CodeSanction=?");
        query->bindValue(0,this->getCode());

        if(query->exec())
            return true;
        else{
            qDebug() << "Not restored" << query->lastError();
            return false;
        }
}
