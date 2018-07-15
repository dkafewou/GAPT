#include "agent.h"

using namespace Core;

Agent::Agent()
{
    query = new QSqlQuery;
}
QString Agent::getIdAgent() const
{
    return idAgent;
}

void Agent::setIdAgent(const QString &value)
{
    idAgent = value;
}

QString Agent::getCodeCateg() const
{
    return codeCateg;
}

void Agent::setCodeCateg(const QString &value)
{
    codeCateg = value;
}

QString Agent::getNomAgent() const
{
    return nomAgent;
}

void Agent::setNomAgent(const QString &value)
{
    nomAgent = value;
}

QString Agent::getPrenomAgent() const
{
    return prenomAgent;
}

void Agent::setPrenomAgent(const QString &value)
{
    prenomAgent = value;
}

QString Agent::getSexe() const
{
    return sexe;
}

void Agent::setSexe(const QString &value)
{
    sexe = value;
}

QString Agent::getTelAgent() const
{
    return telAgent;
}

void Agent::setTelAgent(const QString &value)
{
    telAgent = value;
}

QString Agent::getAdrAgent() const
{
    return adrAgent;
}

void Agent::setAdrAgent(const QString &value)
{
    adrAgent = value;
}

QDate Agent::getDateNaiss() const
{
    return dateNaiss;
}

void Agent::setDateNaiss(const QDate &value)
{
    dateNaiss = value;
}

QDate Agent::getDateAmb() const
{
    return dateAmb;
}

void Agent::setDateAmb(const QDate &value)
{
    dateAmb = value;
}

bool Agent::getSuprAgent() const
{
    return suprAgent;
}

void Agent::setSuprAgent(bool value)
{
    suprAgent = value;
}

QString Agent::getNationalite() const
{
    return nationalite;
}

void Agent::setNationalite(const QString &value)
{
    nationalite = value;
}

QString Agent::getSituation() const
{
    return situation;
}

void Agent::setSituation(const QString &value)
{
    situation = value;
}

QString Agent::getDiplome() const
{
    return diplome;
}

void Agent::setDiplome(const QString &value)
{
    diplome = value;
}

QString Agent::getNiveau() const
{
    return niveau;
}

void Agent::setNiveau(const QString &value)
{
    niveau = value;
}

bool Agent::save()
{
    query->clear();
    query->prepare("insert into agent values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    query->bindValue(0,this->getIdAgent());
    query->bindValue(1,this->getCodeCateg());
    query->bindValue(2,this->getNomAgent());
    query->bindValue(3,this->getPrenomAgent());
    query->bindValue(4,this->getSexe());
    query->bindValue(5,this->getDateNaiss());
    query->bindValue(6,this->getNationalite());
    query->bindValue(7,this->getSituation());
    query->bindValue(8,this->getDiplome());
    query->bindValue(9,this->getNiveau());
    query->bindValue(10,this->getTelAgent());
    query->bindValue(11,this->getAdrAgent());
    query->bindValue(12,this->getDateAmb());
    query->bindValue(13,this->getSuprAgent());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }

}

bool Agent::update()
{
    query->clear();
    query->prepare("update agent set CodeCategorie=?,NomAgent=?,PrenomAgent=?,SexeAgent=?,DateNaiss=?,Nationalite=?,Situation=?,Diplome=?,Niveau=?,TelAgent=?,AdrAgent=?,DateEmbauche=? where IdAgent=?");
    query->bindValue(0,this->getCodeCateg());
    query->bindValue(1,this->getNomAgent());
    query->bindValue(2,this->getPrenomAgent());
    query->bindValue(3,this->getSexe());
    query->bindValue(4,this->getDateNaiss());
    query->bindValue(5,this->getNationalite());
    query->bindValue(6,this->getSituation());
    query->bindValue(7,this->getDiplome());
    query->bindValue(8,this->getNiveau());
    query->bindValue(9,this->getTelAgent());
    query->bindValue(10,this->getAdrAgent());
    query->bindValue(11,this->getDateAmb());
    query->bindValue(12,this->getIdAgent());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Agent::remove()
{
    query->clear();
    query->prepare("update agent set SupprAgent=1 where IdAgent=?");
    query->bindValue(0,this->getIdAgent());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Agent::restore()
{
    query->clear();
    query->prepare("update agent set SupprAgent=0 where IdAgent=?");
    query->bindValue(0,this->getIdAgent());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Agent::Existe()
{
    query->clear();
    query->prepare("select * from agent where NomAgent=? and PrenomAgent=? and SexeAgent=? and DateNaiss=? and TelAgent=?");
    query->bindValue(0,this->getNomAgent());
    query->bindValue(1,this->getPrenomAgent());
    query->bindValue(2,this->getSexe());
    query->bindValue(3,this->getDateNaiss());
    query->bindValue(4,this->getTelAgent());

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

void Agent::Clone(Agent *T)
{
    this->setIdAgent(T->getIdAgent());
    this->setCodeCateg(T->getCodeCateg());
    this->setNomAgent(T->getNomAgent());
    this->setPrenomAgent(T->getPrenomAgent());
    this->setSexe(T->getSexe());
    this->setDateAmb(T->getDateAmb());
    this->setTelAgent(T->getTelAgent());
    this->setAdrAgent(T->getAdrAgent());
    this->setDateNaiss(T->getDateNaiss());
    this->setNationalite(T->getNationalite());
    this->setSituation(T->getSituation());
    this->setDiplome(T->getDiplome());
    this->setNiveau(T->getNiveau());
}

bool Agent::Equal(Agent *T)
{
    if(this->codeCateg==T->getCodeCateg()&&this->nomAgent==T->getNomAgent()
            &&this->prenomAgent==T->getPrenomAgent()&&this->sexe==T->getSexe()
            &&this->dateNaiss==T->getDateNaiss()&&this->telAgent==T->getTelAgent()
            &&this->adrAgent==T->getAdrAgent()&&this->dateAmb==T->getDateAmb()
            &&this->nationalite==T->getNationalite()&&this->situation==T->getSituation()
            &&this->diplome==T->getDiplome()&&this->niveau==T->getNiveau())
        return true;
    return false;
}

QString Agent::generate()
{
    query->clear();
    query->prepare("select count(*) from agent");
    if(query->exec()){
        query->first();
        return this->getNomAgent().left(3)+"-"+this->getPrenomAgent().left(3)+"-00"+QString::number(query->value(0).toInt()+1);
    }
    return "RAS";
}

bool Core::Agent::Delete()
{
    query->clear();
        query->prepare("delete from agent where IdAgent=?");
        query->bindValue(0,this->getIdAgent());

        if(query->exec())
            return true;
        else{
            qDebug() << "Not deleted" << query->lastError();
            return false;
        }
}


