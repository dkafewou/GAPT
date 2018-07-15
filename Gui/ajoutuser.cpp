#include "ajoutuser.h"

using namespace Gui;

AjoutUser::AjoutUser(QSqlRelationalTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
    initComposnat();
}

void AjoutUser::initComposnat()
{
    dateEdit->setDate(QDate::currentDate());
    agent = new Core::Agent;
    passwordEdit->setText("Elisonise2013");
}

bool AjoutUser::champsVide()
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

void Gui::AjoutUser::on_btAgent_clicked()
{
    FenListe = new Gui::ListeAgent(agent,agentEdit,this);
    FenListe->show();
}

void Gui::AjoutUser::on_btValider_clicked()
{
    if(champsVide())
        return;
    user = new Core::Utilisateur;
    user->setAgent(agent->getIdAgent());
    user->setPseudo(pseudoEdit->text());
    user->setPassword(passwordEdit->text());
    user->setProfil(profilComboBox->currentText());
    user->setDate(dateEdit->date());
    user->setCode(user->generate());
    user->setSuppr(false);
    if(user->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Cet utilistateur existe déjà "));
        delete user;
        return;
    }
    if( user->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Utilisateur Créer"));
        this->close();
        model->select();
    }
}
