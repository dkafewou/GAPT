#include "gesdepartement.h"

using namespace Gui;

GesDepartement::GesDepartement(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void GesDepartement::initComposant()
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

    modelDirection = new QSqlTableModel;
    modelDirection->setTable("direction");
    modelDirection->setHeaderData(0,Qt::Horizontal,tr("Code"));
    modelDirection->setHeaderData(1,Qt::Horizontal,tr("Libellé"));
    modelDirection->setHeaderData(2,Qt::Horizontal,tr("Prime Directeur"));
    modelDirection->setHeaderData(3,Qt::Horizontal,tr("supr"));
    modelDirection->setFilter("SupprDirection=0");
    modelDirection->select();
    directionTableView->setModel(modelDirection);
    directionTableView->hideColumn(3);
    directionTableView->show();

    modelFonction = new QSqlTableModel;
    modelFonction->setTable("fonction");
    modelFonction->setHeaderData(0,Qt::Horizontal,tr("Code"));
    modelFonction->setHeaderData(1,Qt::Horizontal,tr("Libellé"));
    modelFonction->setHeaderData(2,Qt::Horizontal,tr("supr"));
    modelFonction->setFilter("SupprFonction=0");
    modelFonction->select();

    fonctionTableView->setModel(modelFonction);
    fonctionTableView->hideColumn(2);
    fonctionTableView->show();
}

void Gui::GesDepartement::on_btSNouveau_clicked()
{
    FenAjoutService = new Gui::AjoutService(modelService,this);
    FenAjoutService->showNormal();
}

void Gui::GesDepartement::on_serviceEdit_textChanged(const QString &arg1)
{
    modelService->setFilter("SupprService=0 and LibelleService like '"+arg1+"%' ");
    listeService.clear();
}

void Gui::GesDepartement::on_btDNouveau_clicked()
{
    FenAjoutDirection = new Gui::AjoutDirection(modelDirection,this);
    FenAjoutDirection->showNormal();
}

void Gui::GesDepartement::on_directionEdit_textChanged(const QString &arg1)
{
    modelDirection->setFilter("SupprDirection=0 and LibelleDirection like '"+arg1+"%' ");
    listeDirection.clear();
}

void Gui::GesDepartement::on_btFNouveau_clicked()
{
    FenAjoutFonction = new Gui::AjoutFonction(modelFonction,this);
    FenAjoutFonction->showNormal();
}

void Gui::GesDepartement::on_fonctionEdit_textChanged(const QString &arg1)
{
    modelFonction->setFilter("SupprFonction=0 and LibelleFonction like '"+arg1+"%' ");
    listeFonction.clear();
}

void Gui::GesDepartement::on_btSModifier_clicked()
{
    if(listeService.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    service = new Core::service;
    service->setCode(listeService.at(0).data().toString());
    service->setLibelle(listeService.at(1).data().toString());
    service->setPrime(listeService.at(2).data().toDouble());

    FenModServ = new Gui::ModService(modelService,service,this);
    FenModServ->showNormal();
}
//Service
void Gui::GesDepartement::on_btSupprimer_clicked()
{
    if(listeService.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            service = new Core::service;
            service->setCode(listeService.at(0).data().toString());
           if(service->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               delete service;
               modelService->select();
           }
        }
}

void Gui::GesDepartement::on_serviceTableView_clicked()
{
    listeService = serviceTableView->selectionModel()->selection().indexes();
}
//Direction
void Gui::GesDepartement::on_btDModifier_clicked()
{
    if(listeDirection.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    direction = new Core::Direction;
    direction->setCode(listeDirection.at(0).data().toString());
    direction->setLibelle(listeDirection.at(1).data().toString());
    direction->setPrime(listeDirection.at(2).data().toDouble());

    FenModDirection = new Gui::ModDirection(modelDirection,direction,this);
    FenModDirection->showNormal();
}

void Gui::GesDepartement::on_btDSupprimer_clicked()
{
    if(listeDirection.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            direction = new Core::Direction;
            direction->setCode(listeDirection.at(0).data().toString());
           if(direction->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               delete direction;
               modelDirection->select();
           }
        }
}

void Gui::GesDepartement::on_directionTableView_clicked()
{
    listeDirection = directionTableView->selectionModel()->selection().indexes();
}
//Fonction

void Gui::GesDepartement::on_btFModifier_clicked()
{
    if(listeFonction.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    fonction = new Core::Fonction;
    fonction->setCode(listeFonction.at(0).data().toString());
    fonction->setLibelle(listeFonction.at(1).data().toString());

    FenModFonct = new Gui::ModFonction(modelFonction,fonction,this);
    FenModFonct->showNormal();
}

void Gui::GesDepartement::on_btFSupprimer_clicked()
{
    if(listeFonction.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            fonction = new Core::Fonction;
            fonction->setCode(listeFonction.at(0).data().toString());
           if(fonction->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               delete fonction;
               modelFonction->select();
               listeFonction.clear();
           }
        }
}

void Gui::GesDepartement::on_fonctionTableView_clicked()
{
    listeFonction = fonctionTableView->selectionModel()->selection().indexes();
}
