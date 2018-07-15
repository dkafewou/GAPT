#ifndef AGENT_H
#define AGENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QMessageBox>

namespace Core {
    class Agent
    {
    public:
        Agent();

//getters & setters
        QString getIdAgent() const;
        void setIdAgent(const QString &value);

        QString getCodeCateg() const;
        void setCodeCateg(const QString &value);

        QString getNomAgent() const;
        void setNomAgent(const QString &value);

        QString getPrenomAgent() const;
        void setPrenomAgent(const QString &value);

        QString getSexe() const;
        void setSexe(const QString &value);

        QString getTelAgent() const;
        void setTelAgent(const QString &value);

        QString getAdrAgent() const;
        void setAdrAgent(const QString &value);

        QDate getDateNaiss() const;
        void setDateNaiss(const QDate &value);

        QDate getDateAmb() const;
        void setDateAmb(const QDate &value);

        bool getSuprAgent() const;
        void setSuprAgent(bool value);

        QString getNationalite() const;
        void setNationalite(const QString &value);

        QString getSituation() const;
        void setSituation(const QString &value);

        QString getDiplome() const;
        void setDiplome(const QString &value);

        QString getNiveau() const;
        void setNiveau(const QString &value);

//methodes
        bool save();
        bool update();
        bool remove();
        bool restore();
        bool Delete();
        bool Existe();
        void Clone(Agent *T);
        bool Equal(Agent *T);
        QString generate();

    private:
        QString idAgent;
        QString codeCateg;
        QString nomAgent;
        QString prenomAgent;
        QString sexe;
        QString telAgent;
        QString adrAgent;
        QString nationalite;
        QString situation;
        QString diplome;
        QString niveau;
        QDate dateNaiss;
        QDate dateAmb;
        bool suprAgent;

        QSqlQuery *query;
    };
}

#endif // AGENT_H
