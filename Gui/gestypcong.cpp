#include "gestypcong.h"

using namespace Gui;

GesTypCong::GesTypCong(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void Gui::GesTypCong::initComposant()
{
    model = new QSqlTableModel;
    model->setTable("TypeConge");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Libellé"));
    model->setHeaderData(2,Qt::Horizontal,tr("Nbres de jours"));
    model->setHeaderData(3,Qt::Horizontal,tr("supr"));
    model->setFilter("SupprTypeConge=0");
    model->select();

    typecongeTableView->setModel(model);
    typecongeTableView->hideColumn(0);
    typecongeTableView->hideColumn(3);
    typecongeTableView->show();
}

void Gui::GesTypCong::on_btNouveau_clicked()
{
    FenAjouT = new Gui::ajoutTypConge(model,this);
    FenAjouT->showNormal();
}

void Gui::GesTypCong::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    TypCong = new Core::TypeConge;
    TypCong->setCode(liste.at(0).data().toString());
    TypCong->setLibelle(liste.at(1).data().toString());
    TypCong->setNbrjrs(liste.at(2).data().toInt());

    FenModCong = new Gui::ModTypeConge(TypCong,model,this);
    FenModCong->showNormal();
}

void Gui::GesTypCong::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            TypCong = new Core::TypeConge;
            TypCong->setCode(liste.at(0).data().toString());
           if(TypCong->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
               delete TypCong;
           }
        }
}

void Gui::GesTypCong::on_typecongeTableView_clicked()
{
    liste = typecongeTableView->selectionModel()->selection().indexes();
}

void Gui::GesTypCong::on_libelleEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprTypeConge=0 and LibelleConge like '"+arg1+"%'");
    liste.clear();
}
