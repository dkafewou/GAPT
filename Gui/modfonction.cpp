#include "modfonction.h"

using namespace Gui;

ModFonction::ModFonction(QSqlTableModel *mod, Core::Fonction *fonc, QWidget *parent) :
    QDialog(parent),model(mod),modFonct(fonc)
{
    setupUi(this);
    initComposant();
}

void ModFonction::initComposant()
{
    codeEdit->setText(modFonct->getCode());
    libelleEdit->setText(modFonct->getLibelle());
}

bool ModFonction::champsVide()
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
    return false;
}

void Gui::ModFonction::on_btValider_clicked()
{
    if(champsVide())
        return;
    fonction = new Core::Fonction;
    fonction->setCode(codeEdit->text());
    fonction->setLibelle(libelleEdit->text());
    fonction->setSuppr(false);
    if(fonction->Equal(modFonct)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        codeEdit->setFocus();
        delete fonction;
        return;
    }
    if(fonction->update(modFonct->getCode())){
        QMessageBox::information(this,tr("SUCCES"),tr("Données de Fonction modifiées"));
        delete fonction;
        delete modFonct;
        model->select();
        this->close();
    }
}
