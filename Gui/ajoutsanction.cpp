#include "ajoutsanction.h"

using namespace Gui;

AjoutSanction::AjoutSanction(QSqlRelationalTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
    datesanctionEdit->setDate(QDate::currentDate());
}

bool AjoutSanction::champsVide()
{
    if(agentEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir l'agent");
        btAgent->setFocus();
        return true;
    }
    if(motifTextEdit->toPlainText().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le motif");
        motifTextEdit->setFocus();
        return true;
    }
    if(datesanctionEdit->date().operator >(QDate::currentDate())){
        QMessageBox::critical(this,"ERREUR 11810","La Date n'est pas valide");
        datesanctionEdit->setFocus();
        return true;
    }
    return false;
}

void Gui::AjoutSanction::on_btAgent_clicked()
{
    agent = new Core::Agent;
    FenListeAgent = new Gui::ListeAgent(agent,agentEdit,this);
    FenListeAgent->showNormal();
}

void Gui::AjoutSanction::on_btValider_clicked()
{
    if(champsVide())
        return;
    Sanction = new Core::sanction;
    Sanction->setAgent(agent->getIdAgent());
    Sanction->setMotif(motifTextEdit->toPlainText());
    Sanction->setDate(datesanctionEdit->date());
    Sanction->setSuppr(false);
    Sanction->setCode(Sanction->generate());
    if(Sanction->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Cette sanction existe déjà "));
        return;
    }
    if(Sanction->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Sanction  enregistrée"));
        agentEdit->clear();
        motifTextEdit->clear();
        datesanctionEdit->setDate(QDate::currentDate());
        model->select();
    }
}
