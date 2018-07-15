#include "listeservice.h"

using namespace Gui;

ListeService::ListeService(QLineEdit *edi, Core::travail *taf, QWidget *parent) :
    QDialog(parent),edit(edi),travail(taf)
{
    setupUi(this);
    initComposant();
}

void ListeService::initComposant()
{
    modelService = new QSqlTableModel;
    modelService->setTable("service");
    modelService->setHeaderData(0,Qt::Horizontal,tr("Code"));
    modelService->setHeaderData(1,Qt::Horizontal,tr("Libellé"));
    modelService->setHeaderData(2,Qt::Horizontal,tr("Prime Chef"));
    modelService->setHeaderData(3,Qt::Horizontal,tr("supr"));
    modelService->setFilter("SupprService=0");
    modelService->select();
    serviceTableView->setModel(modelService);
    serviceTableView->hideColumn(3);
    serviceTableView->show();
}

void Gui::ListeService::on_ServiceEdit_textChanged(const QString &arg1)
{
    modelService->setFilter("SupprService=0 and LibelleService like '"+arg1+"%' ");
    liste.clear();
}

void Gui::ListeService::on_serviceTableView_clicked()
{
    liste = serviceTableView->selectionModel()->selection().indexes();
}

void Gui::ListeService::on_btOk_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir le Service");
        return;
    }
    edit->setText(liste.at(1).data().toString());
    travail->setService(liste.at(0).data().toString());
    this->close();
}
