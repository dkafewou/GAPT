#include "ajoutclient.h"

using namespace Gui;

AjoutClient::AjoutClient(QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
    initComposant();
}

void AjoutClient::initComposant()
{
    validator = new QDoubleValidator(0,999999999999999,0,this);
    telEdit->setValidator( validator );
}

bool AjoutClient::champsVide()
{
    if(nomEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner la raison sociale");
        nomEdit->setFocus();
        return true;
    }
    if(telEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le telephone");
        telEdit->setFocus();
        return true;
    }
    if(adresseTextEdit->toPlainText().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner l'adresse");
        adresseTextEdit->setFocus();
        return true;
    }
    if(villeEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner la ville");
        villeEdit->setFocus();
        return true;
    }
    return false;
}

void Gui::AjoutClient::on_btValider_clicked()
{
    if( champsVide() )
        return;
    client = new Core::Client;
    client->setNom(nomEdit->text());
    client->setTel(telEdit->text());
    client->setPays(paysComboBox->currentText());
    client->setVille(villeEdit->text());
    client->setAdr(adresseTextEdit->toPlainText());
    client->setSuppr(false);
    client->setCode(client->generate());
    if(client->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Le Client existe déjà "));
        delete client;
        return;
    }
    if(client->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Le client a été bien enregistré"));
        nomEdit->clear();
        telEdit->clear();
        villeEdit->clear();
        adresseTextEdit->clear();
        delete client;
        model->select();
    }
}
