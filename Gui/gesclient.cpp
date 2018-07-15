#include "gesclient.h"

using namespace Gui;
gesClient::gesClient(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void gesClient::initComposant()
{
    model = new QSqlTableModel;
    model->setTable("client");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Raison Sociale"));
    model->setHeaderData(2,Qt::Horizontal,tr("Telephone"));
    model->setHeaderData(3,Qt::Horizontal,tr("Adresse"));
    model->setHeaderData(4,Qt::Horizontal,tr("Pays"));
    model->setHeaderData(5,Qt::Horizontal,tr("Ville"));
    model->setHeaderData(6,Qt::Horizontal,tr("Suppr"));
    model->setFilter("SupprClient=0");
    model->select();

    clientTableView->setModel(model);
    clientTableView->hideColumn(0);
    clientTableView->hideColumn(6);
    clientTableView->show();
}

void Gui::gesClient::on_btNouveau_clicked()
{
    FenAjoutClient = new Gui::AjoutClient(model,this);
    FenAjoutClient->showNormal();
}

void Gui::gesClient::on_clientTableView_clicked()
{
    liste = clientTableView->selectionModel()->selection().indexes();
}

void Gui::gesClient::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner le client à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer ce client?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            client = new Core::Client;
            client->setCode(liste.at(0).data().toString());
           if(client->remove()){
               QMessageBox::information(this, tr("SuccÃ¨s"), tr("<B>Client supprimé</B>") ) ;
               model->select();
               delete client;
           }
        }
}

void Gui::gesClient::on_nomEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprClient=0 and NomClient like '"+arg1+"%' ");
    liste.clear();
}

void Gui::gesClient::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner le client à modifier</B>"));
        return;
    }
    client = new Core::Client;
    client->setCode(liste.at(0).data().toString());
    client->setNom(liste.at(1).data().toString());
    client->setTel(liste.at(2).data().toString());
    client->setAdr(liste.at(3).data().toString());
    client->setPays(liste.at(4).data().toString());
    client->setVille(liste.at(5).data().toString());

    FenModclient = new Gui::ModClien(model,client,this);
    FenModclient->showNormal();
}

void Gui::gesClient::on_btApercu_clicked()
{
    QSqlQuery query;
        query.clear();
        query.prepare("select c.NomClient,c.TelClient,c.AdresseClient,c.Pays,c.Ville from Client c where c.NomClient like'"+nomEdit->text()+"%' and SupprClient=0");
        if(query.exec()){
            modelEtat = new QSqlQueryModel;
            modelEtat->setQuery(query);
            modelEtat->setHeaderData(0,Qt::Horizontal,tr("Raison sociale"));
            modelEtat->setHeaderData(1,Qt::Horizontal,tr("Téléphone"));
            modelEtat->setHeaderData(2,Qt::Horizontal,tr("Adresse"));
            modelEtat->setHeaderData(3,Qt::Horizontal,tr("Pays"));
            modelEtat->setHeaderData(4,Qt::Horizontal,tr("Ville"));

            etat = new Reports::EtatNomination("Liste des clients",modelEtat);
}
}
