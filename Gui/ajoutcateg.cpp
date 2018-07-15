#include "ajoutcateg.h"

using namespace Gui;

AjoutCateg::AjoutCateg(QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
    initComposant();
}

bool AjoutCateg::champsVides()
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

void AjoutCateg::initComposant()
{
    validator = new QDoubleValidator(0,999999999,3,this);
    salaireEdit->setValidator( validator );
}

void Gui::AjoutCateg::on_btValider_clicked()
{
    if(champsVides())
        return;
    categorie = new Core::Categorie();
    categorie->setCode(codeEdit->text());
    categorie->setLibelle(libelleEdit->text());
    categorie->setSalaire(salaireEdit->text().toDouble());
    categorie->setSuppr(false);
    if(categorie->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Cette categorie existe déjà "));
        delete categorie;
        return;
    }
    if(categorie->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Cette categorie a été bien enregistrée"));
        model->select();
        codeEdit->clear();
        libelleEdit->clear();
        salaireEdit->clear();
        delete categorie;
    }
}
