#include "ajoutservice.h"

using namespace Gui;

AjoutService::AjoutService(QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
    initComposant();
}

void AjoutService::initComposant()
{
    validator = new QDoubleValidator(0,999999999,3,this);
    primeEdit->setValidator( validator );
}

bool AjoutService::champsVides()
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

void Gui::AjoutService::on_btValider_clicked()
{
    if(champsVides())
        return;
    service =new Core::service;
    service->setCode(codeEdit->text());
    service->setLibelle(libelleEdit->text());
    service->setPrime(primeEdit->text().toDouble());
    service->setSuppr(false);
    if(service->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Ce Service existe déjà "));
        return;
    }
    if(service->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Service enregistré"));
        model->select();
        codeEdit->clear();
        libelleEdit->clear();
        primeEdit->clear();
    }
}
