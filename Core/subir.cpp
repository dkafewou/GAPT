#include "subir.h"

using namespace Core;

Subir::Subir()
{
    query = new QSqlQuery;
}

QString Subir::getDossier() const
{
    return dossier;
}

void Subir::setDossier(const QString &value)
{
    dossier = value;
}

QString Subir::getAgent() const
{
    return agent;
}

void Subir::setAgent(const QString &value)
{
    agent = value;
}

QString Subir::getDepense() const
{
    return depense;
}

void Subir::setDepense(const QString &value)
{
    depense = value;
}

QDate Subir::getDate() const
{
    return date;
}

void Subir::setDate(const QDate &value)
{
    date = value;
}

QTime Subir::getTime() const
{
    return time;
}

void Subir::setTime(const QTime &value)
{
    time = value;
}

double Subir::getMontant() const
{
    return montant;
}

void Subir::setMontant(double value)
{
    montant = value;
}

bool Subir::getSuppr() const
{
    return suppr;
}

void Subir::setSuppr(bool value)
{
    suppr = value;
}

bool Subir::save()
{
    query->clear();
    query->prepare("insert into subir values(?,?,?,?,?,?,?)");
    query->bindValue(0,this->getDossier());
    query->bindValue(1,this->getAgent());
    query->bindValue(2,this->getDepense());
    query->bindValue(3,this->getDate());
    query->bindValue(4,this->getTime());
    query->bindValue(5,this->getMontant());
    query->bindValue(6,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Subir::update()
{
    query->clear();
    query->prepare("update subir set DateDepense=?,HeureDepense=?,MontantReel=? where RepDossier=? and CodeDepense=?");
    query->bindValue(0,this->getDate());
    query->bindValue(1,this->getTime());
    query->bindValue(2,this->getMontant());
    query->bindValue(3,this->getDossier());
    query->bindValue(4,this->getDepense());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Subir::remove()
{
    query->clear();
    query->prepare("update subir set SupprSubir=1 where RepDossier=? and CodeDepense=? and IdAgent=?");
    query->bindValue(0,this->getDossier());
    query->bindValue(1,this->getDepense());
    query->bindValue(2,this->getAgent());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Subir::restore()
{
    query->clear();
    query->prepare("update subir set SupprSubir=0 where RepDossier=? and CodeDepense=? and IdAgent=?");
    query->bindValue(0,this->getDossier());
    query->bindValue(1,this->getDepense());
    query->bindValue(2,this->getAgent());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Subir::Delete()
{
    query->clear();
    query->prepare("delete from subir where RepDossier=? and CodeDepense=?");
    query->bindValue(0,this->getDossier());
    query->bindValue(1,this->getDepense());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not deleted" << query->lastError();
        return false;
    }
}

bool Subir::Existe()
{
    query->clear();
    query->prepare("select * from subir where RepDossier=? and CodeDepense=?");
    query->bindValue(0,this->getDossier());
    query->bindValue(1,this->getDepense());

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

void Subir::Clone(Subir *T)
{
    this->setDossier(T->getDossier());
    this->setAgent(T->getAgent());
    this->setDepense(T->getDepense());
    this->setDate(T->getDate());
    this->setTime(T->getTime());
    this->setMontant(T->getMontant());
}

bool Subir::Equal(Subir *T)
{
    if(this->dossier==T->getDossier()&&this->agent==T->getAgent()
            &&this->depense==T->getDepense()&&this->date==T->getDate()
            &&this->time==T->getTime()&&this->montant==T->getMontant())
        return true;
    return false;
}
