#include "typepermission.h"

using namespace Core;

TypePermission::TypePermission()
{
    query=new QSqlQuery;
}

QString TypePermission::getCode() const
{
    return code;
}

void TypePermission::setCode(const QString &value)
{
    code = value;
}

QString TypePermission::getLibelle() const
{
    return libelle;
}

void TypePermission::setLibelle(const QString &value)
{
    libelle = value;
}

int TypePermission::getNbrJours() const
{
    return nbrJours;
}

void TypePermission::setNbrJours(int value)
{
    nbrJours = value;
}

bool TypePermission::getSuppr() const
{
    return suppr;
}

void TypePermission::setSuppr(bool value)
{
    suppr = value;
}

bool TypePermission::save()
{
    query->clear();
    query->prepare("insert into typepermission values(?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getLibelle());
    query->bindValue(2,this->getNbrJours());
    query->bindValue(3,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool TypePermission::update()
{
    query->clear();
    query->prepare("update typepermission set LibellePermission=?,NbreJours=? where CodeTypepermission=?");
    query->bindValue(0,this->getLibelle());
    query->bindValue(1,this->getNbrJours());
    query->bindValue(2,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool TypePermission::remove()
{
    query->clear();
    query->prepare("update TypePermission set SupprTypePermission=1 where CodeTypepermission=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool TypePermission::restore()
{
    query->clear();
    query->prepare("update TypePermission set SupprTypePermission=0 where CodeTypepermission=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool TypePermission::Existe()
{
    query->clear();
    query->prepare("select * from TypePermission where LibellePermission=?");
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

void TypePermission::Clone(TypePermission *T)
{
    this->setCode(T->getCode());
    this->setLibelle(T->getLibelle());
    this->setNbrJours(T->getNbrJours());
}

bool TypePermission::Equal(TypePermission *T)
{
    if(this->code==T->getCode()&&this->libelle==T->getLibelle()&&this->nbrJours==T->getNbrJours())
        return true;
    return false;
}

QString Core::TypePermission::generate()
{
    query->clear();
    query->prepare("select count(*) from typepermission");
    if(query->exec()){
        query->first();
        return "TypP-"+QString::number(query->value(0).toInt()+1);
    }
    return "TypP-O";
}
