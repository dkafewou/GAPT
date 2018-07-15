#include "modifiersanction.h"

using namespace Gui;

ModifierSanction::ModifierSanction(Core::sanction *Sanc, QSqlRelationalTableModel *mod, QWidget *parent) :
    QDialog(parent),Sanction(Sanc),model(mod)
{
    setupUi(this);
    agentEdit->setText(Sanction->getAgent());
    motifTextEdit->setPlainText(Sanction->getMotif());
    datesanctionEdit->setDate(Sanction->getDate());
}

bool ModifierSanction::champVide()
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
    return false;
}

void Gui::ModifierSanction::on_btValider_clicked()
{
    if(champVide())
        return;
    ModSanc = new Core::sanction;
    ModSanc->setCode(Sanction->getCode());
    ModSanc->setAgent(Sanction->getAgent());
    ModSanc->setMotif(motifTextEdit->toPlainText());
    ModSanc->setDate(datesanctionEdit->date());
    if(ModSanc->Equal(Sanction)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        motifTextEdit->setFocus();
        return ;
    }
    if(ModSanc->update()){
        QMessageBox::information(this, tr("Succès"), tr("<B>Sanction modifiée</B>") ) ;
        this->close();
        model->select();
    }
}
