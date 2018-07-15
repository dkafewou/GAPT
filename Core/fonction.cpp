#include "fonction.h"

using namespace Core;

Fonction::Fonction()
{
    query = new QSqlQuery;
}

QString Fonction::getCode() const
{
    return code;
}

void Fonction::setCode(const QString &value)
{
    code = value;
}

QString Fonction::getLibelle() const
{
    return libelle;
}

void Fonction::setLibelle(const QString &value)
{
    libelle = value;
}

bool Fonction::getSuppr() const
{
    return suppr;
}

void Fonction::setSuppr(bool value)
{
    suppr = value;
}

bool Fonction::save()
{
    query->clear();
    query->prepare("insert into fonction values(?,?,?)");
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

bool Fonction::update(QString value)
{
    query->clear();
    query->prepare("update fonction set CodeFonction=?,LibelleFonction=? where CodeFonction=?");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getLibelle());
    query->bindValue(2,value);

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Fonction::remove()
{
    query->clear();
    query->prepare("update fonction set SupprFonction=1 where CodeFonction=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Fonction::restore()
{
    query->clear();
    query->prepare("update fonction set SupprFonction=0 where CodeFonction=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Fonction::Existe()
{
    query->clear();
    query->prepare("select * from fonction where LibelleFonction=?");
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

void Fonction::Clone(Fonction *T)
{
    this->setCode(T->getCode());
    this->setLibelle(T->getLibelle());
}

bool Fonction::Equal(Fonction *T)
{
    if(this->code==T->getCode()&&this->libelle==T->getLibelle())
        return true;
    return false;
}
