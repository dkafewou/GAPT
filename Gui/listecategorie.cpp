#include "listecategorie.h"

using namespace Gui;

ListeCategorie::ListeCategorie(QLineEdit *edi, Core::Agent *agen, QWidget *parent) :
    QDialog(parent),edit(edi),agent(agen)
{
    setupUi(this);
    initComposant();
}

void ListeCategorie::initComposant()
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

void Gui::ListeCategorie::on_categorieEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprCategorie=0 and LibelleCategorie like '"+arg1+"%' ");
    liste.clear();
}

void Gui::ListeCategorie::on_categorieTableView_clicked()
{
    liste = categorieTableView->selectionModel()->selection().indexes();
}

void Gui::ListeCategorie::on_btOk_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir la Categorie");
        return;
    }
    edit->setText(liste.at(1).data().toString());
    agent->setCodeCateg(liste.at(0).data().toString());
    this->close();
}
