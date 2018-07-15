#include "corbeille.h"

using namespace Gui;

Corbeille::Corbeille(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposantDossier();
    initComposantAgent();
    initComposantFormation();
    initComposantSanction();
    initComposantTransporteur();
}

void Corbeille::initComposantDossier()
{
    modelDos = new QSqlRelationalTableModel(this);
    modelDos->setTable("dossier");
    modelDos->setHeaderData(0,Qt::Horizontal,tr("Repertoire"));
    modelDos->setHeaderData(1,Qt::Horizontal,tr("Client"));
    modelDos->setHeaderData(2,Qt::Horizontal,tr("Date Reception"));
    modelDos->setHeaderData(3,Qt::Horizontal,tr("Arrivé du Bateau"));
    modelDos->setHeaderData(4,Qt::Horizontal,tr("Suppr"));
    modelDos->setRelation(1, QSqlRelation("client", "CodeClient", "NomClient"));
    modelDos->setFilter("SupprDossier=1");
    modelDos->select();

    dossierTableView->setModel(modelDos);
    dossierTableView->hideColumn(4);
    dossierTableView->show();
}
void Corbeille::initComposantAgent()
{

    model = new QSqlRelationalTableModel(this);
    model->setTable("agent");
    model->setHeaderData(0,Qt::Horizontal,tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,tr("Categorie"));
    model->setHeaderData(2,Qt::Horizontal,tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,tr("Prénom"));
    model->setHeaderData(4,Qt::Horizontal,tr("Sexe"));
    model->setHeaderData(5,Qt::Horizontal,tr("Date Naissance"));
    model->setHeaderData(6,Qt::Horizontal,tr("Nationalité"));
    model->setHeaderData(7,Qt::Horizontal,tr("Situation"));
    model->setHeaderData(8,Qt::Horizontal,tr("Diplôme"));
    model->setHeaderData(9,Qt::Horizontal,tr("Niveau"));
    model->setHeaderData(10,Qt::Horizontal,tr("Telephone"));
    model->setHeaderData(11,Qt::Horizontal,tr("Adresse"));
    model->setHeaderData(12,Qt::Horizontal,tr("Ambauché le"));
    model->setHeaderData(13,Qt::Horizontal,tr("Suppr"));
    model->setRelation(1, QSqlRelation("Categorie", "CodeCategorie", "LibelleCategorie"));
    model->setFilter("SupprAgent=1");
    model->select();

    agentTableView->setModel(model);
    agentTableView->hideColumn(13);
    agentTableView->hideColumn(8);
    agentTableView->hideColumn(9);
    agentTableView->show();

}

void Corbeille::initComposantFormation()
{

    modelFormation = new QSqlRelationalTableModel(this);
    modelFormation->setTable("formation");
    modelFormation->setHeaderData(0,Qt::Horizontal,tr("Code"));
    modelFormation->setHeaderData(1,Qt::Horizontal,tr("Libelle"));
    modelFormation->setHeaderData(2,Qt::Horizontal,tr("Ville"));
    modelFormation->setHeaderData(3,Qt::Horizontal,tr("Pays"));
    modelFormation->setHeaderData(4,Qt::Horizontal,tr("Date Debut"));
    modelFormation->setHeaderData(5,Qt::Horizontal,tr("Date Fin"));
    modelFormation->setHeaderData(6,Qt::Horizontal,tr("Fin Effective"));
    modelFormation->setHeaderData(7,Qt::Horizontal,tr("Suppr"));
    modelFormation->setFilter("SupprFormation=1");
    modelFormation->select();

    formationTableView->setModel(modelFormation);
    formationTableView->hideColumn(7);
    formationTableView->hideColumn(0);
    formationTableView->show();

}


void Corbeille::initComposantSanction()
{
    modelSanction = new QSqlRelationalTableModel(this);
    modelSanction->setTable("sanction");
    modelSanction->setHeaderData(0,Qt::Horizontal,tr("Code"));
    modelSanction->setHeaderData(1,Qt::Horizontal,tr("Agent"));
    modelSanction->setHeaderData(2,Qt::Horizontal,tr("Motif"));
    modelSanction->setHeaderData(3,Qt::Horizontal,tr("Date"));
    modelSanction->setHeaderData(4,Qt::Horizontal,tr("Suppr"));
    modelSanction->setRelation(1, QSqlRelation("Agent", "IdAgent", "NomAgent"));
    modelSanction->setFilter("SupprSanction=1");
    modelSanction->select();

    sanctionTableView->setModel(modelSanction);
    sanctionTableView->hideColumn(4);
    sanctionTableView->show();
}

void Corbeille::initComposantTransporteur()
{
    modelTransporteur = new QSqlRelationalTableModel(this);
    modelTransporteur->setTable("transporteur");
    modelTransporteur->setHeaderData(0,Qt::Horizontal,tr("Code"));
    modelTransporteur->setHeaderData(1,Qt::Horizontal,tr("Nom"));
    modelTransporteur->setHeaderData(2,Qt::Horizontal,tr("Prenom"));
    modelTransporteur->setHeaderData(3,Qt::Horizontal,tr("Telephone"));
    modelTransporteur->setHeaderData(4,Qt::Horizontal,tr("Adresse"));
    modelTransporteur->setHeaderData(5,Qt::Horizontal,tr("Suppr"));
    modelTransporteur->setFilter("SupprTransporteur=1");
    modelTransporteur->select();

    transporteurTableView->setModel(modelTransporteur);
    transporteurTableView->hideColumn(0);
    transporteurTableView->hideColumn(5);
    transporteurTableView->show();
}

void Gui::Corbeille::on_dossierTableView_clicked()
{
    listeDossier = dossierTableView->selectionModel()->selection().indexes();
}

void Gui::Corbeille::on_btdossierRestaurer_clicked()
{
    if(listeDossier.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à restaurer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment restaurer ce dossier?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            dossier = new Core::Dossier;
            dossier->setRep(listeDossier.at(0).data().toString());
           if(dossier->restore()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Dossier restauré</B>") ) ;
               delete dossier;
               modelDos->select();
           }
        }

}

void Gui::Corbeille::on_btdossierSupprimer_clicked()
{
    if(listeDossier.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer ce dossier?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            dossier = new Core::Dossier;
            dossier->setRep(listeDossier.at(0).data().toString());
           if(dossier->Delete()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Dossier supprimé</B>") ) ;
               delete dossier;
               modelDos->select();
           }
        }
}

void Gui::Corbeille::on_agentTableView_clicked()
{
    listeAgent = agentTableView->selectionModel()->selection().indexes();
}

void Gui::Corbeille::on_btagentRestaurer_clicked()
{
    if(listeAgent.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à restaurer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment restaurer cet agent?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            agent = new Core::Agent;
            agent->setIdAgent(listeAgent.at(0).data().toString());
            }
        if(agent->restore()){
            QMessageBox::information(this, tr("Succès"), tr("<B>Agent restauré</B>") ) ;
            delete agent;
            model->select();
        }
}

void Gui::Corbeille::on_btagentSupprimer_clicked()
{
    if(listeAgent.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cet agent?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            agent = new Core::Agent;
            agent->setIdAgent(listeAgent.at(0).data().toString());
           if(agent->Delete()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Agent supprimé</B>") ) ;
               delete agent;
               model->select();
           }
        }
}



void Gui::Corbeille::on_formationTableView_clicked()
{
    listeFormation = formationTableView->selectionModel()->selection().indexes();
}


void Gui::Corbeille::on_btformationRestaurer_clicked()
{
    if(listeFormation.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à restaurer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment restaurer cette formation?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            formation = new Core::Formation;
            formation->setCode(listeFormation.at(0).data().toString());
            }
        if(formation->restore()){
            QMessageBox::information(this, tr("Succès"), tr("<B>Formation restaurée</B>") ) ;
            delete formation;
            modelFormation->select();
        }

}

void Gui::Corbeille::on_btformationSupprimer_clicked()
{
    if(listeFormation.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette formation?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            formation = new Core::Formation;
            formation->setCode(listeFormation.at(0).data().toString());
           if(formation->Delete()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Formation supprimée</B>") ) ;
               delete formation;
               modelFormation->select();
           }
        }
}


void Gui::Corbeille::on_sanctionTableView_clicked()
{
    listeSanction = sanctionTableView->selectionModel()->selection().indexes();
}

void Gui::Corbeille::on_btsanctionRestaurer_clicked()
{
    if(listeSanction.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à restaurer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment restaurer cette sanction?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            sanction1 = new Core::sanction;
            sanction1->setCode(listeSanction.at(0).data().toString());
            }
        if(sanction1->restore()){
            QMessageBox::information(this, tr("Succès"), tr("<B>Sanction restaurée</B>") ) ;
            delete sanction1;
            modelSanction->select();
        }

}

void Gui::Corbeille::on_btsanctionSupprimer_clicked()
{
    if(listeSanction.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette sanction?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            sanction1 = new Core::sanction;
            sanction1->setCode(listeSanction.at(0).data().toString());
           if(sanction1->Delete()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Sanction supprimée</B>") ) ;
               delete sanction1;
               modelSanction->select();
           }
        }
}


void Gui::Corbeille::on_transporteurTableView_clicked()
{
    listeTransporteur = transporteurTableView->selectionModel()->selection().indexes();
}

void Gui::Corbeille::on_bttransporteurRestaurer_clicked()
{
    if(listeTransporteur.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à restaurer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment restaurer cet transporteur?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            transporteur1 = new Core::transporteur;
            transporteur1->setCode(listeTransporteur.at(0).data().toString());
            }
        if(transporteur1->restore()){
            QMessageBox::information(this, tr("Succès"), tr("<B>transporteur restauré</B>") ) ;
            delete transporteur1;
            modelTransporteur->select();
        }
}

void Gui::Corbeille::on_bttransporteurSupprimer_clicked()
{
    if(listeTransporteur.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cet transporteur?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            transporteur1 = new Core::transporteur;
            transporteur1->setCode(listeTransporteur.at(0).data().toString());
           if(transporteur1->Delete()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Transporteur supprimé</B>") ) ;
               delete transporteur1;
               modelTransporteur->select();
           }
        }
}
