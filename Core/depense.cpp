#include "depense.h"

using namespace Core;

Depense::Depense()
{
    query=new QSqlQuery;
}

QString Depense::getCode() const
{
    return code;
}

void Depense::setCode(const QString &value)
{
    code = value;
}

QString Depense::getLibelle() const
{
    return libelle;
}

void Depense::setLibelle(const QString &value)
{
    libelle = value;
}

double Depense::getMontant() const
{
    return montant;
}

void Depense::setMontant(double value)
{
    montant = value;
}

bool Depense::getSuppr() const
{
    return suppr;
}

void Depense::setSuppr(bool value)
{
    suppr = value;
}

bool Depense::save()
{
    query->clear();
    query->prepare("insert into depense values(?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getLibelle());
    query->bindValue(2,this->getMontant());
    query->bindValue(3,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Depense::update()
{
    query->clear();
    query->prepare("update depense set Libelle=?,MontantDep=? where CodeDepense=?");
    query->bindValue(0,this->getLibelle());
    query->bindValue(1,this->getMontant());
    query->bindValue(2,this->getCode());
    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Depense::remove()
{
    query->clear();
    query->prepare("update depense set SupprDep=1 where CodeDepense=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Depense::restore()
{
    query->clear();
    query->prepare("update depense set SupprDep=0 where CodeDepense=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Depense::Existe()
{
    query->clear();
    query->prepare("select * from depense where Libelle=?");
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

void Depense::Clone(Depense *T)
{
    this->setCode(T->getCode());
    this->setLibelle(T->getLibelle());
    this->setMontant(T->getMontant());
}

bool Depense::Equal(Depense *T)
{
    if(this->code==T->getCode()&&this->libelle==T->getLibelle()&&this->montant==T->getMontant())
        return true;
    return false;
}

QString Depense::generate()
{
    query->clear();
    query->prepare("select count(*) from depense");
    if(query->exec()){
        query->first();
        return "Dep0"+QString::number(query->value(0).toInt()+1);
    }
    return "Dep00";
}
