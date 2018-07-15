#include "ajouttypperm.h"

using namespace Gui;

AjoutTypPerm::AjoutTypPerm(QSqlTableModel *mode, QWidget *parent) :
    QDialog(parent),model(mode)
{
    setupUi(this);
}

void Gui::AjoutTypPerm::initComposant()
{
    validator = new QIntValidator(0,99999,this);
    nbrejrsEdit->setValidator( validator );
}

bool Gui::AjoutTypPerm::champsVide()
{
    if(libelleEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le libelle");
                libelleEdit->setFocus();
                return true;
            }
    if(nbrejrsEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner nombre de jour");
                nbrejrsEdit->setFocus();
                return true;
            }
    return false;
}

void Gui::AjoutTypPerm::on_btValider_clicked()
{
    if(champsVide())
        return;
    typePerm = new Core::TypePermission;
    typePerm->setLibelle(libelleEdit->text());
    typePerm->setNbrJours(nbrejrsEdit->text().toInt());
    typePerm->setSuppr(false);
    typePerm->setCode(typePerm->generate());
    if(typePerm->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Type existant"));
        delete typePerm;
        return;
    }
    if(typePerm->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Type permission enregistré"));
        model->select();
        libelleEdit->clear();
        nbrejrsEdit->clear();
        delete typePerm;
    }
}
