#include "categorie.h"

using namespace Core;

Categorie::Categorie()
{
    query = new QSqlQuery;
}

QString Categorie::getCode() const
{
    return code;
}

void Categorie::setCode(const QString &value)
{
    code = value;
}

bool Categorie::getSuppr() const
{
    return suppr;
}

void Categorie::setSuppr(bool value)
{
    suppr = value;
}

double Categorie::getSalaire() const
{
    return salaire;
}

void Categorie::setSalaire(double value)
{
    salaire = value;
}

QString Categorie::getLibelle() const
{
    return libelle;
}

void Categorie::setLibelle(const QString &value)
{
    libelle = value;
}

bool Categorie::save()
{
    query->clear();
    query->prepare("insert into categorie values(?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getLibelle());
    query->bindValue(2,this->getSalaire());
    query->bindValue(3,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Categorie::update()
{
    query->clear();
    query->prepare("update Categorie set LibelleCategorie=?,SalaireBrute=? where CodeCategorie=?");
    query->bindValue(0,this->getLibelle());
    query->bindValue(1,this->getSalaire());
    query->bindValue(2,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Categorie::remove()
{
    query->clear();
    query->prepare("update categorie set SupprCategorie=1 where CodeCategorie=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Categorie::restore()
{
    query->clear();
    query->prepare("update categorie set SupprCategorie=0 where CodeCategorie=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Categorie::Existe()
{
    query->clear();
    query->prepare("select * from categorie where LibelleCategorie=? and CodeCategorie=?");
    query->bindValue(0,this->getLibelle());
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

void Categorie::Clone(Categorie *T)
{
    this->setCode(T->getCode());
    this->setLibelle(T->getLibelle());
    this->setSalaire(T->getSalaire());
}

bool Categorie::Equal(Categorie *T)
{
    if(this->code==T->getCode()&&this->libelle==T->getLibelle()&&this->salaire==T->getSalaire())
        return true;
    return false;
}
