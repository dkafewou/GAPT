#include "moddirection.h"

using namespace Gui;

ModDirection::ModDirection(QSqlTableModel *mod, Core::Direction *dir, QWidget *parent) :
    QDialog(parent),model(mod),modDirect(dir)
{
    setupUi(this);
    initComposant();
}

void ModDirection::initComposant()
{
    validator = new QDoubleValidator(0,999999999,3,this);
    primeEdit->setValidator( validator );

    codeEdit->setText(modDirect->getCode());
    libelleEdit->setText(modDirect->getLibelle());
    primeEdit->setText(QString::number(modDirect->getPrime()));
}

bool ModDirection::champsVides()
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

void Gui::ModDirection::on_btValider_clicked()
{
    if(champsVides())
        return;
    direction = new Core::Direction;
    direction->setCode(codeEdit->text());
    direction->setLibelle(libelleEdit->text());
    direction->setPrime(primeEdit->text().toDouble());
    direction->setSuppr(false);
    if(direction->Equal(modDirect)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        codeEdit->setFocus();
        delete direction;
        return;
    }
    if(direction->update(modDirect->getCode())){
        QMessageBox::information(this,tr("SUCCES"),tr("Données de direction modifiées"));
        model->select();
        delete direction;
        delete modDirect;
        this->close();
    }
}
