#include "gesdossier.h"

using namespace Gui;

GesDossier::GesDossier(Core::Utilisateur *use, QWidget *parent):
    QDialog(parent),util(use)
{
    setupUi(this);
    initComposant();
}

void GesDossier::initComposant()
{
    if(util->getProfil()=="Secrétaire"){
        btDepense->setEnabled(false);
    }
    if(util->getProfil()=="Caisse"){
        btNouveau->setEnabled(false);
        btModifier->setEnabled(false);
        btTransport->setEnabled(false);
        btSupprimer->setEnabled(false);
    }

    modelDos = new QSqlRelationalTableModel(this);
    modelDos->setTable("dossier");
    modelDos->setHeaderData(0,Qt::Horizontal,tr("Repertoire"));
    modelDos->setHeaderData(1,Qt::Horizontal,tr("Client"));
    modelDos->setHeaderData(2,Qt::Horizontal,tr("Date Reception"));
    modelDos->setHeaderData(3,Qt::Horizontal,tr("Arrivé du Bateau"));
    modelDos->setHeaderData(4,Qt::Horizontal,tr("Suppr"));
    modelDos->setRelation(1, QSqlRelation("client", "CodeClient", "NomClient"));
    modelDos->setFilter("SupprDossier=0");
    modelDos->select();

    dossierTableView->setModel(modelDos);
    dossierTableView->hideColumn(4);
    dossierTableView->show();

    modelCont = new QSqlTableModel;
    modelCont->setTable("conteneur");
    modelCont->setHeaderData(0,Qt::Horizontal,tr("Code"));
    modelCont->setHeaderData(1,Qt::Horizontal,tr("Rep"));
    modelCont->setHeaderData(2,Qt::Horizontal,tr("Numero"));
    modelCont->setHeaderData(3,Qt::Horizontal,tr("Marchandise"));
    modelCont->setHeaderData(4,Qt::Horizontal,tr("Type"));
    modelCont->setHeaderData(5,Qt::Horizontal,tr("Suppr"));
    modelCont->setFilter("SupprConteneur=0 and RepDossier =' ' ");
    modelCont->select();

    contTableView->setModel(modelCont);
    contTableView->hideColumn(0);
    contTableView->hideColumn(1);
    contTableView->hideColumn(5);
    contTableView->show();
}

void Gui::GesDossier::on_dossierTableView_clicked()
{
    listeDos = dossierTableView->selectionModel()->selection().indexes();
    modelCont->setFilter("SupprConteneur=0 and RepDossier ='"+listeDos.at(0).data().toString()+"' ");
    modelCont->select();
}

void Gui::GesDossier::on_repEdit_textChanged(const QString &arg1)
{
    modelDos->setFilter("SupprDossier=0 and RepDossier like '"+arg1+"%' and NomClient like '"+clientEdit->text()+"%'");
    listeDos.clear();
    modelCont->select();
}

void Gui::GesDossier::on_clientEdit_textChanged(const QString &arg1)
{
    modelDos->setFilter("SupprDossier=0 and RepDossier like '"+repEdit->text()+"%' and NomClient like '"+arg1+"%'");
    listeDos.clear();
    modelCont->select();
}

void Gui::GesDossier::on_btNouveau_clicked()
{
    FenAjoutDoss = new Gui::AjoutDossier(modelDos, this);
    FenAjoutDoss->showMaximized();
}
void Gui::GesDossier::on_btModifier_clicked()
{
    if(listeDos.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    dossier = new Core::Dossier;
    dossier->setRep(listeDos.at(0).data().toString());
    dossier->setClient(listeDos.at(1).data().toString());
    dossier->setDateRec(listeDos.at(2).data().toDate());
    dossier->setDateArr(listeDos.at(3).data().toDate());

    FenModDoss = new Gui::AjoutDossier(dossier,modelDos,this);
    FenModDoss->showMaximized();
}

void Gui::GesDossier::on_btSupprimer_clicked()
{
    if(listeDos.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            dossier = new Core::Dossier;
            dossier->setRep(listeDos.at(0).data().toString());
           if(dossier->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               modelDos->select();
               delete dossier;
           }
        }
}

void Gui::GesDossier::on_btDepense_clicked()
{
    if(listeDos.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner le dossier</B>"));
        return;
    }
    dossier = new Core::Dossier;
    dossier->setRep(listeDos.at(0).data().toString());
    dossier->setClient(listeDos.at(1).data().toString());
    dossier->setDateRec(listeDos.at(2).data().toDate());
    dossier->setDateArr(listeDos.at(3).data().toDate());

    FenAjoutDepDos = new Gui::AjoutDepDos(dossier,this);
    FenAjoutDepDos->showMaximized();
}

void Gui::GesDossier::on_btTransport_clicked()
{
    if(listeCont.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner le conteneur à transporter</B>"));
        return;
    }
    conteneur = new Core::Conteneur;
    conteneur->setCode(listeCont.at(0).data().toString());
    conteneur->setRep(listeCont.at(1).data().toString());
    conteneur->setNumero(listeCont.at(2).data().toString());

    FenTransport = new Gui::AjoutTransport(conteneur,this);
    FenTransport->showNormal();
}

void Gui::GesDossier::on_contTableView_clicked()
{
    listeCont = contTableView->selectionModel()->selection().indexes();

    QSqlQuery query;
    query.clear();
    query.prepare("select * from transport where CodeConteneur='"+listeCont.at(0).data().toString()+"'");
    if(query.exec()){
        if(query.first())
            btTransport->setEnabled(false);
        else
            btTransport->setEnabled(true);
    }
}
