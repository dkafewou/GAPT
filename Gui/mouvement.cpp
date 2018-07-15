#include "mouvement.h"

using namespace Gui;

Mouvement::Mouvement(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initAffectation();
    initNomination();
}

void Mouvement::initAffectation()
{
    modelAfec = new QSqlRelationalTableModel(this);
    modelAfec->setTable("travail");
    modelAfec->setHeaderData(0,Qt::Horizontal,tr("Agent"));
    modelAfec->setHeaderData(1,Qt::Horizontal,tr("Fonction"));
    modelAfec->setHeaderData(2,Qt::Horizontal,tr("Service"));
    modelAfec->setHeaderData(3,Qt::Horizontal,tr("Debut"));
    modelAfec->setHeaderData(4,Qt::Horizontal,tr("Fin"));
    modelAfec->setRelation(0, QSqlRelation("agent", "IdAgent", "NomAgent"));
    modelAfec->setRelation(1, QSqlRelation("fonction", "CodeFonction", "LibelleFonction"));
    modelAfec->setRelation(2, QSqlRelation("service", "CodeService", "LibelleService"));
    modelAfec->select();

    affectationTableView->setModel(modelAfec);
    affectationTableView->show();
}

void Mouvement::initNomination()
{
    modelNom = new QSqlRelationalTableModel(this);
    modelNom->setTable("dirige");
    modelNom->setHeaderData(0,Qt::Horizontal,tr("Agent"));
    modelNom->setHeaderData(1,Qt::Horizontal,tr("Drection"));
    modelNom->setHeaderData(2,Qt::Horizontal,tr("Debut"));
    modelNom->setHeaderData(3,Qt::Horizontal,tr("Fin"));
    modelNom->setHeaderData(4,Qt::Horizontal,tr("suppr"));
    modelNom->setRelation(0, QSqlRelation("agent", "IdAgent", "NomAgent"));
    modelNom->setRelation(1, QSqlRelation("direction", "CodeDirection", "LibelleDirection"));
    modelNom->setFilter("SupprD=0");
    modelNom->select();

    nominationTableView->setModel(modelNom);
    nominationTableView->hideColumn(4);
    nominationTableView->show();
}
//Nomination
void Gui::Mouvement::on_agenEdit_textChanged(const QString &arg1)
{
    modelNom->setFilter("SupprD=0 and NomAgent like '"+arg1+"%' and LibelleDirection like '"+directionEdit->text()+"%'");
    listeN.clear();
}

void Gui::Mouvement::on_directionEdit_textChanged(const QString &arg1)
{
    modelNom->setFilter("SupprD=0 and NomAgent like '"+agenEdit->text()+"%' and LibelleDirection like '"+arg1+"%'");
    listeN.clear();
}
//Affectation

void Gui::Mouvement::on_agentEdit_textChanged(const QString &arg1)
{
    modelAfec->setFilter("NomAgent like '"+arg1+"%' and LibelleFonction like '"+fonctionEdit->text()+"%' and LibelleService like '"+serviceEdit->text()+"%'");
    listeA.clear();
}

void Gui::Mouvement::on_fonctionEdit_textChanged(const QString &arg1)
{
    modelAfec->setFilter("NomAgent like '"+agentEdit->text()+"%' and LibelleFonction like '"+arg1+"%' and LibelleService like '"+serviceEdit->text()+"%'");
    listeA.clear();
}

void Gui::Mouvement::on_serviceEdit_textChanged(const QString &arg1)
{
    modelAfec->setFilter("NomAgent like '"+agentEdit->text()+"%' and LibelleFonction like '"+fonctionEdit->text()+"%' and LibelleService like '"+arg1+"%'");
    listeA.clear();
}

void Gui::Mouvement::on_btApercu_clicked()
{
    QSqlQuery query;
    query.clear();
    query.prepare("select a.NomAgent,a.PrenomAgent,f.LibelleFonction,s.LibelleService,t.Date_debut,t.Date_Fin from agent a,fonction f,service s, travail t where a.IdAgent=t.IdAgent and f.CodeFonction=t.CodeFonction and s.CodeService=t.CodeService and a.NomAgent like'"+agentEdit->text()+"%' and f.LibelleFonction like'"+fonctionEdit->text()+"%' and s.LibelleService like'"+serviceEdit->text()+"%'");
    if(query.exec()){
        modelEtat = new QSqlQueryModel;
        modelEtat->setQuery(query);
        modelEtat->setHeaderData(0,Qt::Horizontal,tr("Nom"));
        modelEtat->setHeaderData(1,Qt::Horizontal,tr("Prénom"));
        modelEtat->setHeaderData(2,Qt::Horizontal,tr("Fonction"));
        modelEtat->setHeaderData(3,Qt::Horizontal,tr("Service"));
        modelEtat->setHeaderData(4,Qt::Horizontal,tr("Debut"));
        modelEtat->setHeaderData(5,Qt::Horizontal,tr("Fin"));

        etat = new Reports::EtatNomination("Liste des affectations",modelEtat);
    }
}

void Gui::Mouvement::on_btAper_clicked()
{
    etat = new Reports::EtatNomination("Liste des directeurs",modelNom);
}
