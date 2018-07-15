#include "ajoutdepense.h"

using namespace Gui;

AjoutDepense::AjoutDepense(QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
    initComposant();
}


void AjoutDepense::initComposant()
{
    validator = new QDoubleValidator(0,999999999999,3,this);
    montantEdit->setValidator( validator );
}

bool AjoutDepense::champsVide()
{
    if(libelleEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le libelle");
                libelleEdit->setFocus();
                return true;
            }
    if(montantEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le montant");
                montantEdit->setFocus();
                return true;
            }
    return false;
}

void Gui::AjoutDepense::on_btValider_clicked()
{
    if(champsVide())
        return;
    depense = new Core::Depense;
    depense->setLibelle(libelleEdit->text());
    depense->setMontant(montantEdit->text().toDouble());
    depense->setSuppr(false);
    depense->setCode(depense->generate());
    if(depense->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Libellé de la depense existe déjà "));
        delete depense;
        return;
    }
    if(depense->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Dépense enregistrée"));
        model->select();
        libelleEdit->clear();
        montantEdit->clear();
    }
}
