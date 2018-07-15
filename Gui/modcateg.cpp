#include "modcateg.h"

using namespace Gui;

ModCateg::ModCateg(Core::Categorie *categ, QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),categorie(categ),model(mod)
{
    setupUi(this);
    codeEdit->setText(categorie->getCode());
    libelleEdit->setText(categorie->getLibelle());
    salaireEdit->setText(QString::number( categorie->getSalaire()));
}

void ModCateg::initComposant()
{
    validator = new QDoubleValidator(0,999999999,3,this);
    salaireEdit->setValidator( validator );
}

bool ModCateg::champVide()
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
    if(salaireEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le Salaire Brute");
                salaireEdit->setFocus();
                return true;
            }
    return false;
}

void Gui::ModCateg::on_btValider_clicked()
{
    if(champVide())
        return;
    ModCategorie = new Core::Categorie;
    ModCategorie->setCode(codeEdit->text());
    ModCategorie->setLibelle(libelleEdit->text());
    ModCategorie->setSalaire(salaireEdit->text().toDouble());
    if(ModCategorie->Equal(categorie)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        codeEdit->setFocus();
        delete ModCategorie;
        return ;
    }
    if(ModCategorie->update()){
        QMessageBox::information(this, tr("Succès"), tr("<B>Categorie modifiée</B>") ) ;
        delete categorie;
        delete ModCategorie;
        delete validator;
        this->close();
        model->select();
    }
}
