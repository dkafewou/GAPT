#include "moddepense.h"

using namespace Gui;

ModDepense::ModDepense(QSqlTableModel *mod, Core::Depense *dep, QWidget *parent) :
    QDialog(parent),model(mod),modDep(dep)
{
    setupUi(this);
    initComposant();
}

void ModDepense::initComposant()
{
    validator = new QDoubleValidator(0,999999999,3,this);
    montantEdit->setValidator( validator );

    libelleEdit->setText(modDep->getLibelle());
    montantEdit->setText(QString::number(modDep->getMontant()));
}

bool ModDepense::champsVide()
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

void Gui::ModDepense::on_btValider_clicked()
{
    if(champsVide())
        return;
    depense = new Core::Depense;
    depense->setCode(modDep->getCode());
    depense->setLibelle(libelleEdit->text());
    depense->setMontant(montantEdit->text().toDouble());
    depense->setSuppr(false);
    if(depense->Equal(modDep)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        libelleEdit->setFocus();
        delete depense;
        return;
    }
    if(depense->update()){
        QMessageBox::information(this,tr("SUCCES"),tr("Données de depense modifiées"));
        model->select();
        delete depense;
        delete modDep;
        this->close();
    }
}
