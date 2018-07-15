#include "permission.h"

using namespace Core;

Permission::Permission()
{
    query =new QSqlQuery;
}

QString Permission::getCode() const
{
    return code;
}

void Permission::setCode(const QString &value)
{
    code = value;
}

QString Permission::getAgent() const
{
    return agent;
}

void Permission::setAgent(const QString &value)
{
    agent = value;
}

QString Permission::getType() const
{
    return type;
}

void Permission::setType(const QString &value)
{
    type = value;
}

QString Permission::getMotif() const
{
    return motif;
}

void Permission::setMotif(const QString &value)
{
    motif = value;
}

QDate Permission::getDebut() const
{
    return debut;
}

void Permission::setDebut(const QDate &value)
{
    debut = value;
}

QDate Permission::getFin() const
{
    return fin;
}

void Permission::setFin(const QDate &value)
{
    fin = value;
}

QDate Permission::getRetour() const
{
    return retour;
}

void Permission::setRetour(const QDate &value)
{
    retour = value;
}

bool Permission::getSuppr() const
{
    return suppr;
}

void Permission::setSuppr(bool value)
{
    suppr = value;
}

bool Permission::save()
{
    query->clear();
    query->prepare("insert into permission values(?,?,?,?,?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getAgent());
    query->bindValue(2,this->getType());
    query->bindValue(3,this->getMotif());
    query->bindValue(4,this->getDebut());
    query->bindValue(5,this->getFin());
    query->bindValue(6,this->getRetour());
    query->bindValue(7,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Permission::update()
{
    query->clear();
    query->prepare("update permission set CodeTypepermission=?,MotifPermission=?,DateDebut=?,DateFin=?,DateRetourEffect=? where CodePermission=?");
    query->bindValue(0,this->getType());
    query->bindValue(1,this->getMotif());
    query->bindValue(2,this->getDebut());
    query->bindValue(3,this->getFin());
    query->bindValue(4,this->getRetour());
    query->bindValue(5,this->getCode());
    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Permission::remove()
{
    query->clear();
    query->prepare("update permission set SupprPermission=1 where CodePermission=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Permission::restore()
{
    query->clear();
    query->prepare("update permission set SupprPermission=0 where CodePermission=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Permission::Existe()
{
    query->clear();
    query->prepare("select * from permission where IdAgent=? and CodeTypepermission=? and DateDebut=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getType());
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

void Permission::Clone(Permission *T)
{
    this->setCode(T->getCode());
    this->setAgent(T->getAgent());
    this->setMotif(T->getMotif());
    this->setDebut(T->getDebut());
    this->setFin(T->getFin());
    this->setRetour(T->getRetour());
}

bool Permission::Equal(Permission *T)
{
    if(this->code==T->getCode()&&this->agent==T->getAgent()
            &&this->motif==T->getMotif()&&this->debut==T->getDebut()
            &&this->fin==T->getFin()&&this->retour==T->getRetour())
        return true;
    return false;
}

QString Core::Permission::generate()
{
    query->clear();
    query->prepare("select count(*) from permission");
    if(query->exec()){
        query->first();
        return "Perm-"+QString::number(query->value(0).toInt()+1);
    }
    return "Perm-0";
}
