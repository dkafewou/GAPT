#include "modtypperm.h"

using namespace Gui;

ModTypPerm::ModTypPerm(QSqlTableModel *mode, Core::TypePermission *perm, QWidget *parent) :
    QDialog(parent),model(mode),TypeP(perm)
{
    setupUi(this);
    initComposant();
}

void Gui::ModTypPerm::initComposant()
{
    validator = new QIntValidator(0,99999,this);
    nbrejrsEdit->setValidator( validator );

    libelleEdit->setText(TypeP->getLibelle());
    nbrejrsEdit->setText(QString::number(TypeP->getNbrJours()));
}

bool Gui::ModTypPerm::champsVide()
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

void Gui::ModTypPerm::on_btValider_clicked()
{
    if(champsVide())
        return;
    typePerm = new Core::TypePermission;
    typePerm->setLibelle(libelleEdit->text());
    typePerm->setNbrJours(nbrejrsEdit->text().toInt());
    typePerm->setSuppr(false);
    typePerm->setCode(TypeP->getCode());
    if(typePerm->Equal(TypeP)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        delete typePerm;
        libelleEdit->setFocus();
        return;
    }
    if(typePerm->update()){
        QMessageBox::information(this,tr("SUCCES"),tr("Type permission modifié"));
        model->select();
        this->close();
    }
}
