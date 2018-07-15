#include "modservice.h"

using namespace Gui;

ModService::ModService(QSqlTableModel *mod, Core::service *serv, QWidget *parent) :
    QDialog(parent),model(mod),modServ(serv)
{
    setupUi(this);
    initComposant();
}

void ModService::initComposant()
{
    validator = new QDoubleValidator(0,999999999,3,this);
    primeEdit->setValidator( validator );

    codeEdit->setText(modServ->getCode());
    libelleEdit->setText(modServ->getLibelle());
    primeEdit->setText(QString::number(modServ->getPrime()));
}

bool ModService::champsVide()
{
    if(codeEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le Code");
                codeEdit->setFocus();
                return true;
            }
    if(libelleEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le libelle");
                libelleEdit->setFocus();
                return true;
            }
    if(primeEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner la prime");
                primeEdit->setFocus();
                return true;
            }
    return false;
}

void Gui::ModService::on_btValider_clicked()
{
    if(champsVide())
        return;
    service = new Core::service;
    service->setCode(codeEdit->text());
    service->setLibelle(libelleEdit->text());
    service->setPrime(primeEdit->text().toDouble());
    service->setSuppr(false);
    if(service->Equal(modServ)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        codeEdit->setFocus();
        delete service;
        return;
    }
    if(service->update(modServ->getCode())){
        QMessageBox::information(this,tr("SUCCES"),tr("Données de Service modifiées"));
        model->select();
        delete service;
        delete modServ;
        this->close();
    }
}
