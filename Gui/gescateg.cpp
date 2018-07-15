#include "gescateg.h"

using namespace Gui;

GesCateg::GesCateg(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void GesCateg::initComposant()
{
    model = new QSqlTableModel;
    model->setTable("categorie");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Libellé"));
    model->setHeaderData(2,Qt::Horizontal,tr("Salaire Brute"));
    model->setHeaderData(3,Qt::Horizontal,tr("supr"));
    model->setFilter("SupprCategorie=0");
    model->select();

    categorieTableView->setModel(model);
    categorieTableView->hideColumn(3);
    categorieTableView->show();
}

void Gui::GesCateg::on_btNouveau_clicked()
{
    FenAjoutCateg = new Gui::AjoutCateg(model,this);
    FenAjoutCateg->showNormal();
}

void Gui::GesCateg::on_libelleEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprCategorie=0 and LibelleCategorie like '"+arg1+"%' ");
    model->select();
    liste.clear();
}

void Gui::GesCateg::on_categorieTableView_clicked()
{
    liste = categorieTableView->selectionModel()->selection().indexes();
}

void Gui::GesCateg::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    categorie = new Core::Categorie;
    categorie->setCode(liste.at(0).data().toString());
    categorie->setLibelle(liste.at(1).data().toString());
    categorie->setSalaire(liste.at(2).data().toDouble());

    FenModCateg = new Gui::ModCateg(categorie,model,this);
    FenModCateg->showNormal();
}

void Gui::GesCateg::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            categorie = new Core::Categorie;
            categorie->setCode(liste.at(0).data().toString());
           if(categorie->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
           }
        }
}
