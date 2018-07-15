#include "typedepart.h"

using namespace Core;

TypeDepart::TypeDepart()
{
    query=new QSqlQuery;
}

QString TypeDepart::getCode() const
{
    return code;
}

void TypeDepart::setCode(const QString &value)
{
    code = value;
}

QString TypeDepart::getLibelle() const
{
    return libelle;
}

void TypeDepart::setLibelle(const QString &value)
{
    libelle = value;
}

bool TypeDepart::getSuppr() const
{
    return suppr;
}

void TypeDepart::setSuppr(bool value)
{
    suppr = value;
}

bool TypeDepart::save()
{
    query->clear();
    query->prepare("insert into typedepart values(?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getLibelle());
    query->bindValue(2,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool TypeDepart::update()
{
    query->clear();
    query->prepare("update typedepart set LibelleDepart=? where CodeTypeDepart=?");
    query->bindValue(0,this->getLibelle());
    query->bindValue(1,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool TypeDepart::remove()
{
    query->clear();
    query->prepare("update TypeDepart set SupprTypeDepart=1 where CodeTypeDepart=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool TypeDepart::restore()
{
    query->clear();
    query->prepare("update TypeDepart set SupprTypeDepart=0 where CodeTypeDepart=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool TypeDepart::Existe()
{
    query->clear();
    query->prepare("select * from TypeDepart where LibelleDepart=?");
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

void TypeDepart::Clone(TypeDepart *T)
{
    this->setCode(T->getCode());
    this->setLibelle(T->getLibelle());
}

bool TypeDepart::Equal(TypeDepart *T)
{
    if(this->code==T->getCode()&&this->libelle==T->getLibelle())
        return true;
    return false;
}

QString TypeDepart::generate()
{
        return this->getLibelle().left(3);
}
