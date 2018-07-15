#include "ajouttypconge.h"

using namespace Gui;

ajoutTypConge::ajoutTypConge(QSqlTableModel *mode, QWidget *parent) :
    QDialog(parent),model(mode)
{
    setupUi(this);
    initComposant();
}

void Gui::ajoutTypConge::initComposant()
{
    validator = new QIntValidator(0,99999,this);
    jrsEdit->setValidator( validator );
}

bool Gui::ajoutTypConge::champsVide()
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

void Gui::ajoutTypConge::on_btValider_clicked()
{
    if(champsVide())
        return;
    TypCong = new Core::TypeConge;
    TypCong->setLibelle(typeEdit->text());
    TypCong->setNbrjrs(jrsEdit->text().toInt());
    TypCong->setSuppr(false);
    TypCong->setCode(TypCong->generate());
    if(TypCong->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Type existant"));
        delete TypCong;
        return;
    }
    if(TypCong->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Type congé enregistré"));
        model->select();
        typeEdit->clear();
        jrsEdit->clear();
        delete TypCong;
    }
}
