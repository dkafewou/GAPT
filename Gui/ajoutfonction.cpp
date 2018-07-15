#include "ajoutfonction.h"

using namespace Gui;

AjoutFonction::AjoutFonction(QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
}

bool AjoutFonction::champsVides()
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

void Gui::AjoutFonction::on_btValider_clicked()
{
    if(champsVides())
        return;
    fonction =new Core::Fonction;
    fonction->setCode(codeEdit->text());
    fonction->setLibelle(libelleEdit->text());
    fonction->setSuppr(false);
    if(fonction->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Cette Fonction existe déjà "));
        return;
    }
    if(fonction->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Fonction enregistrée"));
        model->select();
        codeEdit->clear();
        libelleEdit->clear();
    }
}
