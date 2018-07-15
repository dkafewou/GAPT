#include "modtypeconge.h"

using namespace Gui;

ModTypeConge::ModTypeConge(Core::TypeConge *typ, QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),modTyp(typ),model(mod)
{
    setupUi(this);
    initComposant();
}

void Gui::ModTypeConge::initComposant()
{
    validator = new QIntValidator(0,99999,this);
    jrsEdit->setValidator( validator );

    typeEdit->setText(modTyp->getLibelle());
    jrsEdit->setText(QString::number(modTyp->getNbrjrs()));
}

bool Gui::ModTypeConge::champsVide()
{
    if(typeEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le libelle");
                typeEdit->setFocus();
                return true;
            }
    if(jrsEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le nombre de jour");
                jrsEdit->setFocus();
                return true;
            }
    return false;
}

void Gui::ModTypeConge::on_btValider_clicked()
{
    if(champsVide())
        return;
    TypCong = new Core::TypeConge;
    TypCong->setLibelle(typeEdit->text());
    TypCong->setNbrjrs(jrsEdit->text().toInt());
    TypCong->setSuppr(false);
    TypCong->setCode(modTyp->getCode());
    if(TypCong->Equal(modTyp)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        typeEdit->setFocus();
        delete TypCong;
        return;
    }
    if(TypCong->update()){
        QMessageBox::information(this,tr("SUCCES"),tr("Type congé modifié"));
        model->select();
        delete TypCong;
        this->close();
    }
}
