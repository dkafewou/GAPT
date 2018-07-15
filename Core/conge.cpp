#include "conge.h"

using namespace Core;

Conge::Conge()
{
    query = new QSqlQuery;
}

QString Conge::getCode() const
{
    return code;
}

void Conge::setCode(const QString &value)
{
    code = value;
}

QString Conge::getAgent() const
{
    return agent;
}

void Conge::setAgent(const QString &value)
{
    agent = value;
}

QString Conge::getType() const
{
    return type;
}

void Conge::setType(const QString &value)
{
    type = value;
}

QString Conge::getMotif() const
{
    return motif;
}

void Conge::setMotif(const QString &value)
{
    motif = value;
}

QDate Conge::getDebut() const
{
    return debut;
}

void Conge::setDebut(const QDate &value)
{
    debut = value;
}

QDate Conge::getFin() const
{
    return fin;
}

void Conge::setFin(const QDate &value)
{
    fin = value;
}

QDate Conge::getRetour() const
{
    return retour;
}

void Conge::setRetour(const QDate &value)
{
    retour = value;
}

bool Conge::getSuppr() const
{
    return suppr;
}

void Conge::setSuppr(bool value)
{
    suppr = value;
}

bool Conge::save()
{
    query->clear();
    query->prepare("insert into conge values(?,?,?,?,?,?,?,?)");
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

bool Conge::update()
{
    query->clear();
    query->prepare("update conge set IdAgent=?,CodeTypeConge=?,MotifConge=?,DateDebut=?,DateFin=?,DateRetourEffect=? where CodeConge=?");
    query->bindValue(0,this->getAgent());
    query->bindValue(1,this->getType());
    query->bindValue(2,this->getMotif());
    query->bindValue(3,this->getDebut());
    query->bindValue(4,this->getFin());
    query->bindValue(5,this->getRetour());
    query->bindValue(6,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Conge::remove()
{
    query->clear();
    query->prepare("update conge set SupprConge=1 where CodeConge=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Conge::restore()
{
    query->clear();
    query->prepare("update conge set SupprConge=0 where CodeConge=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Conge::Existe()
{
    query->clear();
    query->prepare("select * from conge where IdAgent=? and CodeTypeConge=? and DateDebut=?");
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

void Conge::Clone(Conge *T)
{
    this->setCode(T->getCode());
    this->setAgent(T->getAgent());
    this->setType(T->getType());
    this->setMotif(T->getMotif());
    this->setDebut(T->getDebut());
    this->setFin(T->getFin());
    this->setRetour(T->getRetour());
}

bool Conge::Equal(Conge *T)
{
    if(this->code==T->getCode()&&this->agent==T->getAgent()
            &&this->type==T->getType()&&this->motif==T->getMotif()
            &&this->debut==T->getDebut()&&this->fin==T->getFin()&&this->retour==T->getRetour())
        return true;
    return false;
}

QString Core::Conge::generate()
{
    query->clear();
    query->prepare("select count(*) from conge");
    if(query->exec()){
        query->first();
        return "Cong-"+QString::number(query->value(0).toInt()+1);
    }
    return "Cong-0";
}
