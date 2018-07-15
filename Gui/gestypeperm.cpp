#include "gestypeperm.h"

using namespace Gui;

GesTypePerm::GesTypePerm(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void Gui::GesTypePerm::initComposant()
{
    model = new QSqlTableModel;
    model->setTable("TypePermission");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Libellé"));
    model->setHeaderData(2,Qt::Horizontal,tr("Nbres de jours"));
    model->setHeaderData(3,Qt::Horizontal,tr("supr"));
    model->setFilter("SupprTypePermission=0");
    model->select();

    typepermissionTableView->setModel(model);
    typepermissionTableView->hideColumn(0);
    typepermissionTableView->hideColumn(3);
    typepermissionTableView->show();
}

void Gui::GesTypePerm::on_btNouveau_clicked()
{
    FenAjout = new Gui::AjoutTypPerm(model,this);
    FenAjout->showNormal();
}

void Gui::GesTypePerm::on_typepermissionTableView_clicked()
{
    liste = typepermissionTableView->selectionModel()->selection().indexes();
}

void Gui::GesTypePerm::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    perm = new Core::TypePermission;
    perm->setCode(liste.at(0).data().toString());
    perm->setLibelle(liste.at(1).data().toString());
    perm->setNbrJours(liste.at(2).data().toInt());

    FenMod = new Gui::ModTypPerm(model,perm,this);
    FenMod->showNormal();
}

void Gui::GesTypePerm::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            perm = new Core::TypePermission;
            perm->setCode(liste.at(0).data().toString());
           if(perm->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
               delete perm;
           }
        }
}

void Gui::GesTypePerm::on_libelleEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprTypePermission=0 and LibellePermission like '"+arg1+"%'");
    liste.clear();
}
