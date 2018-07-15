#include "listedepense.h"

using namespace Gui;

ListeDepense::ListeDepense(QLineEdit *edi, Core::Depense *dep, QWidget *parent) :
    QDialog(parent),edit(edi),depense(dep)
{
    setupUi(this);
    initComposant();
}

void ListeDepense::initComposant()
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

void Gui::ListeDepense::on_depenseEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprDep=0 and Libelle like '"+arg1+"%'");
    liste.clear();
}

void Gui::ListeDepense::on_depenseTableView_clicked()
{
     liste = depenseTableView->selectionModel()->selection().indexes();
}

void Gui::ListeDepense::on_btOk_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir la dépense");
        return;
    }
    depense->setCode(liste.at(0).data().toString());
    depense->setLibelle(liste.at(1).data().toString());
    depense->setMontant(liste.at(2).data().toDouble());
    edit->setText(liste.at(1).data().toString());
    this->close();
}
