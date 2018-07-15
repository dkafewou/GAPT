#include "gesdepense.h"

using namespace Gui;
gesDepense::gesDepense(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void gesDepense::initComposant()
{
    model = new QSqlTableModel;
    model->setTable("depense");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Libelle Dépense"));
    model->setHeaderData(2,Qt::Horizontal,tr("Montant Fixe"));
    model->setHeaderData(3,Qt::Horizontal,tr("Suppr"));
    model->setFilter("SupprDep=0");
    model->select();

    depenseTableView->setModel(model);
    depenseTableView->hideColumn(0);
    depenseTableView->hideColumn(3);
    depenseTableView->show();
}

void Gui::gesDepense::on_btNouveau_clicked()
{
    FenDepense = new Gui::AjoutDepense(model,this);
    FenDepense->showNormal();
}

void Gui::gesDepense::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            depense = new Core::Depense;
            depense->setCode(liste.at(0).data().toString());
           if(depense->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
           }
        }
}

void Gui::gesDepense::on_depenseTableView_clicked()
{
    liste = depenseTableView->selectionModel()->selection().indexes();
}

void Gui::gesDepense::on_depenseEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprDep=0 and Libelle like '"+arg1+"%'");
    liste.clear();
}

void Gui::gesDepense::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    depense = new Core::Depense;
    depense->setCode(liste.at(0).data().toString());
    depense->setLibelle(liste.at(1).data().toString());
    depense->setMontant(liste.at(2).data().toDouble());

    FenModDep = new Gui::ModDepense(model,depense,this);
    FenModDep->showNormal();
}
