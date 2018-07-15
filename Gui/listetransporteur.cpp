#include "listetransporteur.h"

using namespace Gui;

ListeTransporteur::ListeTransporteur(QLineEdit *edi, Core::transporteur *tr, QWidget *parent) :
    QDialog(parent),edit(edi),transporteur(tr)
{
    setupUi(this);
    initComposant();
}

void ListeTransporteur::initComposant()
{
    model = new QSqlTableModel;
    model->setTable("transporteur");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,tr("Telephone"));
    model->setHeaderData(4,Qt::Horizontal,tr("Adresse"));
    model->setHeaderData(5,Qt::Horizontal,tr("Suppr"));
    model->setFilter("SupprTransporteur=0");
    model->select();

    transporteurTableView->setModel(model);
    transporteurTableView->hideColumn(0);
    transporteurTableView->hideColumn(5);
    transporteurTableView->show();
}

void Gui::ListeTransporteur::on_nomEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprTransporteur=0 and NomTransporteur like'"+arg1+"%'");
    liste.clear();
}

void Gui::ListeTransporteur::on_transporteurTableView_clicked()
{
    liste = transporteurTableView->selectionModel()->selection().indexes();
}

void Gui::ListeTransporteur::on_btOk_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir le Service");
        return;
    }
    edit->setText(liste.at(1).data().toString()+" "+liste.at(2).data().toString());
    transporteur->setCode(liste.at(0).data().toString());
    this->close();
}
