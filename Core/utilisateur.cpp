#include "utilisateur.h"

using namespace Core;

Utilisateur::Utilisateur()
{
    query = new QSqlQuery;
}

QString Utilisateur::getCode() const
{
    return code;
}

void Utilisateur::setCode(const QString &value)
{
    code = value;
}

QString Utilisateur::getAgent() const
{
    return agent;
}

void Utilisateur::setAgent(const QString &value)
{
    agent = value;
}

QString Utilisateur::getPseudo() const
{
    return pseudo;
}

void Utilisateur::setPseudo(const QString &value)
{
    pseudo = value;
}

QString Utilisateur::getPassword() const
{
    return password;
}

void Utilisateur::setPassword(const QString &value)
{
    password = value;
}

QString Utilisateur::getProfil() const
{
    return profil;
}

void Utilisateur::setProfil(const QString &value)
{
    profil = value;
}

QDate Utilisateur::getDate() const
{
    return date;
}

void Utilisateur::setDate(const QDate &value)
{
    date = value;
}

bool Utilisateur::getSuppr() const
{
    return suppr;
}

void Utilisateur::setSuppr(bool value)
{
    suppr = value;
}

bool Utilisateur::save()
{
    query->clear();
    query->prepare("insert into utilisateur values(?,?,?,?,?,?,?)");
    query->bindValue(0,this->getCode());
    query->bindValue(1,this->getAgent());
    query->bindValue(2,this->getPseudo());
    query->bindValue(3,this->getPassword());
    query->bindValue(4,this->getProfil());
    query->bindValue(5,this->getDate());
    query->bindValue(6,this->getSuppr());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not saved" << query->lastError();
        return false;
    }
}

bool Utilisateur::update()
{
    query->clear();
    query->prepare("update utilisateur set Pseudo=?,Password=?,Profil=? where IdUtilisateur=?");
    query->bindValue(0,this->getPseudo());
    query->bindValue(1,this->getPassword());
    query->bindValue(2,this->getProfil());
    query->bindValue(3,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not updated" << query->lastError();
        return false;
    }
}

bool Utilisateur::remove()
{
    query->clear();
    query->prepare("update utilisateur set SupprUser=1 where IdUtilisateur=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not removed" << query->lastError();
        return false;
    }
}

bool Utilisateur::restore()
{
    query->clear();
    query->prepare("update utilisateur set SupprUser=0 where IdUtilisateur=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not restored" << query->lastError();
        return false;
    }
}

bool Utilisateur::Delete()
{
    query->clear();
    query->prepare("delete from utilisateur where IdUtilisateur=?");
    query->bindValue(0,this->getCode());

    if(query->exec())
        return true;
    else{
        qDebug() << "Not deleted" << query->lastError();
        return false;
    }
}

bool Utilisateur::Existe()
{
    query->clear();
    query->prepare("select * from utilisateur where Pseudo=?");
    query->bindValue(0,this->getPseudo());

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

void Utilisateur::Clone(Utilisateur *T)
{
    this->setCode(T->getCode());
    this->setAgent(T->getAgent());
    this->setPseudo(T->getPseudo());
    this->setPassword(T->getPassword());
    this->setProfil(T->getProfil());
    this->setDate(T->getDate());
}

bool Utilisateur::Equal(Utilisateur *T)
{
    if(this->code==T->getCode()&&this->agent==T->getAgent()
            &&this->pseudo==T->getPseudo()&&this->password==T->getPassword()
            &&this->profil==T->getProfil()&&this->date==T->getDate())
        return true;
    return false;
}

bool Utilisateur::Creer(QString pseud, QString pass)
{
    query->clear();
    query->prepare("select * from utilisateur where pseudo=? and password=?");
    query->bindValue(0,pseud);
    query->bindValue(1,pass);
    if(query->exec()){
        if(query->first()){
        this->setCode(query->value(0).toString());
        this->setAgent(query->value(1).toString());
        this->setPseudo(query->value(2).toString());
        this->setPassword(query->value(3).toString());
        this->setProfil(query->value(4).toString());
        this->setDate(query->value(5).toDate());
        this->setSuppr(query->value(6).toBool());
        return true;
        }
    }
    return false;
}

QString Utilisateur::generate()
{
    query->clear();
    query->prepare("select count(*) from utilisateur");
    if(query->exec()){
        query->first();
        return "User0"+QString::number(query->value(0).toInt()+1);
    }
    return "User00";
}
