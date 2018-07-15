#include "modclien.h"

using namespace Gui;

ModClien::ModClien(QSqlTableModel *mod, Core::Client *cli, QWidget *parent) :
    QDialog(parent),model(mod),modcli(cli)
{
    setupUi(this);
    initcomposant();
}

void ModClien::initcomposant()
{
    validator = new QDoubleValidator(0,999999999,0,this);
    telEdit->setValidator( validator );

    nomEdit->setText(modcli->getNom());
    telEdit->setText(modcli->getTel());
    adresseTextEdit->setPlainText(modcli->getAdr());
    paysComboBox->setCurrentIndex(paysComboBox->findText(modcli->getPays()));
    villeEdit->setText(modcli->getVille());
}

bool ModClien::champsVide()
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

void Gui::ModClien::on_btValider_clicked()
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
    client->setCode(modcli->getCode());
    if(client->Equal(modcli)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        nomEdit->setFocus();
        delete client;
        return ;
    }
    if(client->update()){
        QMessageBox::information(this, tr("Succès"), tr("<B>Client modifié</B>") ) ;
        delete client;
        delete modcli;
        delete validator;
        this->close();
        model->select();
    }
}
