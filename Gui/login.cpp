#include "login.h"

using namespace Gui;

Login::Login(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposants();
}

bool Login::champsVide()
{
    if( pseudoEdit->text().isEmpty() ){
        loginFailedLabel->setText("Veuillez fournir un pseudo") ;
        pseudoEdit->setFocus() ;
        return true ;
    }

    if( passwordEdit->text().isEmpty() ){
        loginFailedLabel->setText("Veuillez fournir un mot de passe") ;
        passwordEdit->setFocus() ;
        return true ;
    }

    if( pseudoEdit->text().isEmpty() && passwordEdit->text().isEmpty() ) {
        loginFailedLabel->setText("Pseudo et mot de passe invalide");
        pseudoEdit->setFocus();
        return true ;
    }
    return false ;
}

void Login::initComposants()
{
    dial->setVisible(false);
    compteurErreur = 3 ;
    paletteRouge.setColor(QPalette::WindowText, Qt::red);
    loginFailedLabel->setPalette( paletteRouge ) ;
}

void Login::raz()
{
    pseudoEdit->clear();
    passwordEdit->clear();
    pseudoEdit->setFocus();
}

void Gui::Login::on_btLogin_clicked()
{
    user = new Core::Utilisateur ;
    if( champsVide() ){
        compteurErreur-- ;
        if(compteurErreur == 0){
            this->close() ;
        }
        return;
    }
    if(user->Creer(pseudoEdit->text(),passwordEdit->text()) ){
        if(user->getSuppr()){
            QMessageBox::critical(this,tr("ERREUR 20"),tr("Cet utilisateur est désactivé\nVeuiller contacter l'administrateur"));
            return;
        }
        if(user->getPassword()=="Elisonise2013"){
            QMessageBox::information(this,tr("INFORMATION"),tr("Pour des raisons de sécurité veuillez changer votre mot de passe. Merci"));
            FenChPass = new Gui::ChangerPassword(user,this);
            this->close();
            FenChPass->showNormal();
            return;
        }
        fenetrePrincipale = new MainWindow(dial,user);
        this->close();
        fenetrePrincipale->showMaximized();
        return;
    }
    else{
        loginFailedLabel->setText("Paramètres de connexion incorrecte") ;
        compteurErreur-- ;
        delete user;
        raz() ;
    }
    if(compteurErreur == 0){
        delete user;
        this->close() ;
    }
}

void Login::on_dial_valueChanged()
{
    if(dial->value()==1){
        pseudoEdit->clear();
        passwordEdit->clear();
        pseudoEdit->setFocus();
        loginFailedLabel->clear();
        compteurErreur = 3;
        fenetrePrincipale->close();
        delete fenetrePrincipale;
        delete user;
        this->show();
        dial->setValue(0);
    }
}
