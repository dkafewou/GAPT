#include "gestransport.h"

using namespace Gui;

GesTransport::GesTransport(Core::Utilisateur *use, QWidget *parent) :
    QDialog(parent),util(use)
{
    setupUi(this);
    initComposant();
}

void GesTransport::initComposant()
{
    if(util->getProfil()=="Secrétaire"){
        btPaye->setEnabled(false);
    }
    if(util->getProfil()=="Caisse"){
        btModifier->setEnabled(false);
        btSupprimer->setEnabled(false);
    }

    model = new QSqlRelationalTableModel(this);
    model->setTable("transport");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Conteneur N°"));
    model->setHeaderData(2,Qt::Horizontal,tr("Transporteur"));
    model->setHeaderData(3,Qt::Horizontal,tr("Date Sortie"));
    model->setHeaderData(4,Qt::Horizontal,tr("Date Retour"));
    model->setHeaderData(5,Qt::Horizontal,tr("Suppr"));
    model->setRelation(1, QSqlRelation("conteneur", "CodeConteneur", "NumeroCont"));
    model->setRelation(2, QSqlRelation("transporteur", "CodeTransporteur", "NomTransporteur"));
    model->setFilter("SupprTransp=0");
    model->select();

    transportTableView->setModel(model);
    transportTableView->hideColumn(0);
    transportTableView->hideColumn(5);
    transportTableView->show();
}

void Gui::GesTransport::on_transportTableView_clicked()
{
    liste = transportTableView->selectionModel()->selection().indexes();

    QSqlQuery query;
    query.clear();
    query.prepare("select * from reglement where CodeTransp='"+liste.at(0).data().toString()+"'");
    if(query.exec()){
        if(query.first())
            btPaye->setEnabled(false);
        else
            btPaye->setEnabled(true);
    }
}

void Gui::GesTransport::on_btPaye_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner le transport à payer</B>"));
        return;
    }
    reglement = new Core::Reglement;
    reglement->setTransport(liste.at(0).data().toString());

    FenReglement = new Gui::AjoutReglement(liste.at(1).data().toString(),liste.at(2).data().toString(),reglement,this);
    FenReglement->showNormal();
}

void Gui::GesTransport::on_TransporteurEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprTransp=0 and NomTransporteur like '"+arg1+"%'");
    liste.clear();
}

void Gui::GesTransport::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    transport = new Core::transport;
    transport->setCode(liste.at(0).data().toString());
    transport->setConteneur(liste.at(1).data().toString());
    transport->setTransporteur(liste.at(2).data().toString());
    transport->setDatetransp(liste.at(3).data().toDate());
    transport->setDateretour(liste.at(4).data().toDate());

    FenModTr = new Gui::ModTransp(model,transport,this);
    FenModTr->showNormal();
}

void Gui::GesTransport::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            transport = new Core::transport;
            transport->setCode(liste.at(0).data().toString());
           if(transport->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
           }
        }
}
