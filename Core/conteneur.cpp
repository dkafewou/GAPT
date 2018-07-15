#include "conteneur.h"

using namespace Core;

Conteneur::Conteneur()
{
    query = new QSqlQuery;
}

QString Conteneur::getCode() const
{
    return code;
}

void Conteneur::setCode(const QString &value)
{
    code = value;
}

QString Conteneur::getRep() const
{
    return rep;
}

void Conteneur::setRep(const QString &value)
{
    rep = value;
}

QString Conteneur::getNumero() const
{
    return numero;
}

void Conteneur::setNumero(const QString &value)
{
    numero = value;
}

QString Conteneur::getType() const
{
    return type;
}

void Conteneur::setType(const QString &value)
{
    type = value;
}

QString Conteneur::getMarchandise() const
{
    return marchandise;
}

void Conteneur::setMarchandise(const QString &value)
{
    marchandise = value;
}

bool Conteneur::getSuppr() const
{
    return suppr;
}

void Conteneur::setSuppr(bool value)
{
    suppr = value;
}

bool Conteneur::save()
{
    query->clear();
    query->prepare("insert into conteneur values(?,?,?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getRep());
    query->bindValue(2,this->getNumero());
    query->bindValue(3,this->getMarchandise());
    query->bindValue(4,this->getType());
    query->bindValue(5,this->getSuppr());
    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Conteneur::update()
{
    query->clear();
    query->prepare("update conteneur set NumeroCont=?,Marchandise=?,Type=? where CodeConteneur=?");
    query->bindValue(0,this->getNumero());
    query->bindValue(1,this->getMarchandise());
    query->bindValue(2,this->getType());
    query->bindValue(3,this->getCode());
    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Conteneur::remove()
{
    query->clear();
    query->prepare("update conteneur set SupprConteneur=1 where CodeConteneur=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Conteneur::restore()
{
    query->clear();
    query->prepare("update conteneur set SupprConteneur=0 where CodeConteneur=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Conteneur::Delete()
{
    query->clear();
    query->prepare("delete from conteneur where CodeConteneur=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not deleted" << query->lastError();
        return false;
    }
}

bool Conteneur::Existe()
{
    query->clear();
    query->prepare("select * from conteneur where RepDossier=? and NumeroCont=?");
    query->bindValue(0,this->getRep());
    query->bindValue(1,this->getNumero());

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

void Conteneur::Clone(Conteneur *T)
{
    this->setCode(T->getCode());
    this->setRep(T->getRep());
    this->setNumero(T->getNumero());
    this->setMarchandise(T->getMarchandise());
    this->setType(T->getType());
}

bool Conteneur::Equal(Conteneur *T)
{
    if(this->code==T->getCode()&&this->rep==T->getRep()
            &&this->numero==T->getNumero()&&this->marchandise==T->getMarchandise()&&this->type==T->getType())
        return true;
    return false;
}

QString Conteneur::generate()
{
    query->clear();
    query->prepare("select count(*) from conteneur");
    if(query->exec()){
        query->first();
        return "Cont"+QString::number(query->value(0).toInt()+1);
    }
    return this->getRep()+"Cont0";
}
