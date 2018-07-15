#include "modtranqporteur.h"

using namespace Gui;

ModTranqporteur::ModTranqporteur(QSqlTableModel *mod, Core::transporteur *tr, QWidget *parent) :
    QDialog(parent),model(mod),transporteur(tr)
{
    setupUi(this);
    initComposant();
}

void ModTranqporteur::initComposant()
{
    validator = new QDoubleValidator(0,999999999,0,this);
    telEdit->setValidator( validator );

    nomEdit->setText(transporteur->getNom());
    prenomEdit->setText(transporteur->getPrenom());
    telEdit->setText(transporteur->getTel());
    adresseEdit->setPlainText(transporteur->getAdresse());
}

bool ModTranqporteur::champsVide()
{
    if(nomEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le nom");
        nomEdit->setFocus();
        return true;
    }
    if(telEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le telephone");
        telEdit->setFocus();
        return true;
    }
    if(adresseEdit->toPlainText().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner l'adresse");
        adresseEdit->setFocus();
        return true;
    }
    return false;
}

void Gui::ModTranqporteur::on_btVlider_clicked()
{
    if(champsVide())
        return;
    ModTransp = new Core::transporteur;
    ModTransp->setNom(nomEdit->text());
    ModTransp->setPrenom(prenomEdit->text());
    ModTransp->setTel(telEdit->text());
    ModTransp->setAdresse(adresseEdit->toPlainText());
    ModTransp->setSuppr(false);
    ModTransp->setCode(transporteur->getCode());
    if(ModTransp->Equal(transporteur)){
        QMessageBox::critical(this,tr("Doublon"),tr("Aucune modification n'a été effectuer"));
        nomEdit->setFocus();
        delete ModTransp;
        return;
    }
    if(ModTransp->update()){
        QMessageBox::information(this,tr("SUCCES"),tr("Données de transporteur modifiées"));
        delete ModTransp;
        delete transporteur;
        model->select();
        this->close();
    }
}
