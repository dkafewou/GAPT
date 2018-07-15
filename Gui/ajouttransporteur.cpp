#include "ajouttransporteur.h"

using namespace Gui;

AjoutTransporteur::AjoutTransporteur(QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
    initComposant();
}

void AjoutTransporteur::initComposant()
{
    validator = new QDoubleValidator(0,999999999,0,this);
    telEdit->setValidator( validator );
}

bool AjoutTransporteur::champsVides()
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

void Gui::AjoutTransporteur::on_btVlider_clicked()
{
    if(champsVides())
        return;
    transporteur = new Core::transporteur;
    transporteur->setNom(nomEdit->text());
    transporteur->setPrenom(prenomEdit->text());
    transporteur->setTel(telEdit->text());
    transporteur->setAdresse(adresseEdit->toPlainText());
    transporteur->setSuppr(false);
    transporteur->setCode(transporteur->generate());
    if(transporteur->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Ce transporteur existe déjà "));
        delete transporteur;
        return;
    }
    if(transporteur->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Transporteur enregistré"));
        delete transporteur;
        nomEdit->clear();
        prenomEdit->clear();
        telEdit->clear();
        adresseEdit->clear();
        model->select();
    }
}
