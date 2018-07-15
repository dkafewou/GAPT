#include "formation.h"

using namespace Core;

Formation::Formation()
{
    query =new QSqlQuery;
}

QString Formation::getCode() const
{
    return code;
}

void Formation::setCode(const QString &value)
{
    code = value;
}

QString Formation::getLibelle() const
{
    return libelle;
}

void Formation::setLibelle(const QString &value)
{
    libelle = value;
}

QString Formation::getVille() const
{
    return ville;
}

void Formation::setVille(const QString &value)
{
    ville = value;
}

QString Formation::getPays() const
{
    return pays;
}

void Formation::setPays(const QString &value)
{
    pays = value;
}

QDate Formation::getDebut() const
{
    return debut;
}

void Formation::setDebut(const QDate &value)
{
    debut = value;
}

QDate Formation::getFin() const
{
    return fin;
}

void Formation::setFin(const QDate &value)
{
    fin = value;
}

QDate Formation::getReel() const
{
    return reel;
}

void Formation::setReel(const QDate &value)
{
    reel = value;
}

bool Formation::getSuppr() const
{
    return suppr;
}

void Formation::setSuppr(bool value)
{
    suppr = value;
}

bool Formation::save()
{
    query->clear();
    query->prepare("insert into formation values(?,?,?,?,?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getLibelle());
    query->bindValue(2,this->getVille());
    query->bindValue(3,this->getPays());
    query->bindValue(4,this->getDebut());
    query->bindValue(5,this->getFin());
    query->bindValue(6,this->getReel());
    query->bindValue(7,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Formation::update()
{
    query->clear();
    query->prepare("update formation set LibelleFormation=?,Ville=?,Pays=?,DateDebut=?,DateFin=?,DateFinEffectif=? where CodeFormation=?");
    query->bindValue(0,this->getLibelle());
    query->bindValue(1,this->getVille());
    query->bindValue(2,this->getPays());
    query->bindValue(3,this->getDebut());
    query->bindValue(4,this->getFin());
    query->bindValue(5,this->getReel());
    query->bindValue(6,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Formation::remove()
{
    query->clear();
    query->prepare("update formation set SupprFormation=1 where CodeFormation=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Formation::restore()
{
    query->clear();
    query->prepare("update formation set SupprFormation=0 where CodeFormation=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Formation::Existe()
{
    query->clear();
    query->prepare("select * from formation where LibelleFormation=? and Ville=? and Pays=? and DateDebut=?");
    query->bindValue(0,this->getLibelle());
    query->bindValue(1,this->getVille());
    query->bindValue(2,this->getPays());
    query->bindValue(3,this->getDebut());

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

void Formation::Clone(Formation *T)
{
    this->setCode(T->getCode());
    this->setLibelle(T->getLibelle());
    this->setVille(T->getVille());
    this->setPays(T->getPays());
    this->setDebut(T->getDebut());
    this->setFin(T->getFin());
    this->setReel(T->getReel());
}

bool Formation::Equal(Formation *T)
{
    if(this->code==T->getCode()&&this->libelle==T->getLibelle()
            &&this->ville==T->getVille()&&this->pays==T->getPays()
            &&this->debut==T->getDebut()&&this->fin==T->getFin()
            &&this->reel==T->getReel())
        return true;
    return false;
}

QString Formation::generate()
{
    query->clear();
    query->prepare("select count(*) from formation");
    if(query->exec()){
        query->first();
        return "Form-"+QString::number(query->value(0).toInt()+1);
    }
    return "RASS";
}

bool Core::Formation::Delete()
{
    query->clear();
        query->prepare("delete from formation where CodeFormation=?");
        query->bindValue(0,this->getCode());

        if(query->exec())
            return true;
        else{
            qDebug() << "Not restored" << query->lastError();
            return false;
        }
}
