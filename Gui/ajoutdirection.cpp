#include "ajoutdirection.h"

using namespace Gui;

AjoutDirection::AjoutDirection(QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
    initComposant();
}

void AjoutDirection::initComposant()
{
    validator = new QDoubleValidator(0,999999999,3,this);
    primeEdit->setValidator( validator );
}

bool AjoutDirection::champsVides()
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

void Gui::AjoutDirection::on_btValider_clicked()
{
    if(champsVides())
        return;
    direction =new Core::Direction;
    direction->setCode(codeEdit->text());
    direction->setLibelle(libelleEdit->text());
    direction->setPrime(primeEdit->text().toDouble());
    direction->setSuppr(false);
    if(direction->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Cette Direction existe déjà "));
        return;
    }
    if(direction->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Direction enregistré"));
        model->select();
        codeEdit->clear();
        libelleEdit->clear();
        primeEdit->clear();
    }
}
