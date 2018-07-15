#include "moduser.h"

using namespace Gui;

ModUser::ModUser(QSqlRelationalTableModel *mod, Core::Utilisateur *use, QWidget *parent) :
    QDialog(parent),model(mod),modUse(use)
{
    setupUi(this);
    initcompsant();
}

void ModUser::initcompsant()
{
    agentEdit->setText(modUse->getAgent());
    pseudoEdit->setText(modUse->getPseudo());
    passwordEdit->setText(modUse->getPassword());
    profilComboBox->setCurrentIndex(profilComboBox->findText(modUse->getProfil()));
    dateEdit->setDate(modUse->getDate());
}

bool ModUser::champsVides()
{
    if(agentEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir de l'agent");
        btAgent->setFocus();
        return true;
    }
    if(pseudoEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le pseudo");
        pseudoEdit->setFocus();
        return true;
    }
    if(passwordEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le mot de passe");
        passwordEdit->setFocus();
        return true;
    }
    return false;
}

void Gui::ModUser::on_btValider_clicked()
{
    if(champsVides())
        return;
    user = new Core::Utilisateur;
    user->setAgent(modUse->getAgent());
    user->setPseudo(pseudoEdit->text());
    user->setPassword(passwordEdit->text());
    user->setProfil(profilComboBox->currentText());
    user->setDate(dateEdit->date());
    user->setCode(modUse->getCode());
    user->setSuppr(false);
    if(user->Equal(modUse)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        profilComboBox->setFocus();
        delete user;
        return ;
    }
    if( user->update()){
        QMessageBox::information(this,tr("SUCCES"),tr("Utilisateur modifié"));
        this->close();
        delete user;
        delete modUse;
        model->select();
    }
}
