#include "changerpassword.h"

using namespace Gui;

ChangerPassword::ChangerPassword(Core::Utilisateur *use, QWidget *parent) :
    QDialog(parent),user(use)
{
    setupUi(this);
}

bool ChangerPassword::champsVide()
{
    if(ancienPassEdit->text()!=user->getPassword()){
        QMessageBox::critical(this,"ERREUR 11810","Ancien mot de passe incorrecte");
        ancienPassEdit->clear();
        nouveauPassEdit->clear();
        confirmerPasseEdit->clear();
        ancienPassEdit->setFocus();
        return true;
    }
    if(nouveauPassEdit->text().length()<6){
        QMessageBox::critical(this,"ERREUR 11810","Le mot de passe doit être composé au minimum de six caractères");
        nouveauPassEdit->clear();
        confirmerPasseEdit->clear();
        nouveauPassEdit->setFocus();
        return true;
    }
    if(nouveauPassEdit->text()=="Elisonise2013"){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir un mot de passe différent de celui par défaut");
        nouveauPassEdit->clear();
        confirmerPasseEdit->clear();
        nouveauPassEdit->setFocus();
        return true;
    }
    if(nouveauPassEdit->text()!=confirmerPasseEdit->text()){
        QMessageBox::critical(this,"ERREUR 11810","Les deux nouveaux mots de passe ne correspondent pas");
        nouveauPassEdit->clear();
        confirmerPasseEdit->clear();
        nouveauPassEdit->setFocus();
        return true;
    }
    return false;
}

void Gui::ChangerPassword::on_btValider_clicked()
{
    if(champsVide())
        return;
    user->setPassword(nouveauPassEdit->text());
    if(user->update()){
        QMessageBox::information(this,tr("SUCCES"),tr("Mot de passe modifié"));
        this->close();
    }
}
