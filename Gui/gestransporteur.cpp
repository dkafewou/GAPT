#include "gestransporteur.h"

using namespace Gui;

GesTransporteur::GesTransporteur(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void GesTransporteur::initComposant()
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

void Gui::GesTransporteur::on_btNouveau_clicked()
{
    FenAjoutTransp = new Gui::AjoutTransporteur(model,this);
    FenAjoutTransp->show();
}

void Gui::GesTransporteur::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    transp = new Core::transporteur;
    transp->setCode(liste.at(0).data().toString());
    transp->setNom(liste.at(1).data().toString());
    transp->setPrenom(liste.at(2).data().toString());
    transp->setTel(liste.at(3).data().toString());
    transp->setAdresse(liste.at(4).data().toString());

    FenModTr = new Gui::ModTranqporteur(model,transp,this);
    FenModTr->show();
}

void Gui::GesTransporteur::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            transp = new Core::transporteur;
            transp->setCode(liste.at(0).data().toString());
           if(transp->remove()){
               QMessageBox::information(this, tr("Succés"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
           }
        }
}

void Gui::GesTransporteur::on_transporteurTableView_clicked()
{
    liste = transporteurTableView->selectionModel()->selection().indexes();
}

void Gui::GesTransporteur::on_nomEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprTransporteur=0 and NomTransporteur like'"+arg1+"%' and PrenomTransporteur like '"+prenomEdit->text()+"%'");
    liste.clear();
}

void Gui::GesTransporteur::on_prenomEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprTransporteur=0 and NomTransporteur like'"+nomEdit->text()+"%' and PrenomTransporteur like '"+arg1+"%'");
    liste.clear();
}

void Gui::GesTransporteur::on_btApercu_clicked()
{
    QSqlQuery query;
        query.clear();
        query.prepare("select t.NomTransporteur,t.PrenomTransporteur,t.TelTransporteur,t.AdresseTransporteur from transporteur t where t.NomTransporteur like'"+nomEdit->text()+"%' and t.PrenomTransporteur like'"+prenomEdit->text()+"%' and SupprTransporteur=0");
        if(query.exec()){
            modelEtat = new QSqlQueryModel;
            modelEtat->setQuery(query);
            modelEtat->setHeaderData(0,Qt::Horizontal,tr("Nom"));
            modelEtat->setHeaderData(1,Qt::Horizontal,tr("Prénom"));
            modelEtat->setHeaderData(2,Qt::Horizontal,tr("Téléphone"));
            modelEtat->setHeaderData(3,Qt::Horizontal,tr("Adresse"));

            etat = new Reports::EtatNomination("Liste des transporteurs",modelEtat);
        }
}
