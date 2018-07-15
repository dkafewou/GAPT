#include "modtypedepart.h"

using namespace Gui;

ModTypeDepart::ModTypeDepart(Core::TypeDepart *type, QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),modtype(type),model(mod)
{
    setupUi(this);
    libelleEdit->setText(modtype->getLibelle());
}

bool ModTypeDepart::champsVide()
{
    if(libelleEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le libell�");
        libelleEdit->setFocus();
        return true;
    }
    return false;
}

void Gui::ModTypeDepart::on_btValider_clicked()
{
    if(champsVide())
        return;
    typedep = new Core::TypeDepart;
    typedep->setLibelle(libelleEdit->text());
    typedep->setSuppr(false);
    typedep->setCode(modtype->getCode());
    if(typedep->Equal(modtype)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a �t� effectuer</b>")) ;
        libelleEdit->setFocus();
        delete typedep;
        return ;
    }
    if(typedep->update()){
        QMessageBox::information(this,tr("SUCCES"),tr("Type modifi�"));
        delete typedep;
        delete modtype;
        model->select();
        this->close();
    }
}
