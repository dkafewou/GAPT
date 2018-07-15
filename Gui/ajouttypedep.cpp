#include "ajouttypedep.h"

using namespace Gui;

AjoutTypeDep::AjoutTypeDep(QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
}

bool AjoutTypeDep::champsVide()
{
    if(libelleEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le libell�");
        libelleEdit->setFocus();
        return true;
    }
    return false;
}

void Gui::AjoutTypeDep::on_btValider_clicked()
{
    if(champsVide())
        return;
    typedep = new Core::TypeDepart;
    typedep->setLibelle(libelleEdit->text());
    typedep->setSuppr(false);
    typedep->setCode(typedep->generate());
    if(typedep->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Ce type de d�part existe d�j� "));
        delete typedep;
        return;
    }
    if(typedep->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Type d�part enregistr�"));
        delete typedep;
        libelleEdit->clear();
        model->select();
    }
}
