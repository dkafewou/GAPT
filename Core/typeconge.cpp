#include "typeconge.h"

using namespace Core;

TypeConge::TypeConge()
{
    query=new QSqlQuery;
}

QString TypeConge::getCode() const
{
    return code;
}

void TypeConge::setCode(const QString &value)
{
    code = value;
}

QString TypeConge::getLibelle() const
{
    return libelle;
}

void TypeConge::setLibelle(const QString &value)
{
    libelle = value;
}

int TypeConge::getNbrjrs() const
{
    return nbrjrs;
}

void TypeConge::setNbrjrs(int value)
{
    nbrjrs = value;
}

bool TypeConge::getSuppr() const
{
    return suppr;
}

void TypeConge::setSuppr(bool value)
{
    suppr = value;
}

bool TypeConge::save()
{
    query->clear();
    query->prepare("insert into typeconge values(?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getLibelle());
    query->bindValue(2,this->getNbrjrs());
    query->bindValue(3,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}


bool TypeConge::update()
{
    query->clear();
    query->prepare("update typeconge set LibelleConge=?,NbreJours=? where CodeTypeConge=?");
    query->bindValue(0,this->getLibelle());
    query->bindValue(1,this->getNbrjrs());
    query->bindValue(2,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool TypeConge::remove()
{
    query->clear();
    query->prepare("update typeconge set SupprTypeConge=1 where CodeTypeConge=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool TypeConge::restore()
{
    query->clear();
    query->prepare("update typeconge set SupprTypeConge=0 where CodeTypeConge=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool TypeConge::Existe()
{
    query->clear();
    query->prepare("select * from typeconge where LibelleConge=?");
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

void TypeConge::Clone(TypeConge *T)
{
    this->setCode(T->getCode());
    this->setLibelle(T->getLibelle());
    this->setNbrjrs(T->getNbrjrs());
}

bool TypeConge::Equal(TypeConge *T)
{
    if(this->code==T->getCode()&&this->libelle==T->getLibelle()&&this->nbrjrs==T->getNbrjrs())
        return true;
    return false;
}

QString Core::TypeConge::generate()
{
    query->clear();
    query->prepare("select count(*) from typeConge");
    if(query->exec()){
        query->first();
        return "TypC-"+QString::number(query->value(0).toInt()+1);
    }
    return "TypC-O";
}
