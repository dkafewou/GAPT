#include "gesagent.h"

using namespace Gui;

GesAgent::GesAgent(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    model = new QSqlRelationalTableModel(this);
    initCombo();
    initComposant();
}

void GesAgent::initComposant()
{
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
    model->setFilter("SupprAgent=0");
    model->select();

    agentTableView->setModel(model);
    agentTableView->hideColumn(13);
    agentTableView->show();

}

void GesAgent::initCombo()
{
    comboModel = new QSqlTableModel(this);
    comboModel->setTable("categorie");
    comboModel->setHeaderData(0,Qt::Horizontal,tr("Code"));
    comboModel->setHeaderData(1,Qt::Horizontal,tr("Libelle"));
    comboModel->setFilter("SupprCategorie=0");
    comboModel->select();

    categorieComboBox->setModel(comboModel);
    categorieComboBox->setModelColumn(1);
    categorieComboBox->show();
}

void Gui::GesAgent::on_btNouveau_clicked()
{
    FenAjoutAgent = new Gui::AjoutAgent(model,this);
    FenAjoutAgent->showNormal();
}

void Gui::GesAgent::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            agent = new Core::Agent;
            agent->setIdAgent(liste.at(0).data().toString());
           if(agent->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
               delete agent;
           }
        }
}

void Gui::GesAgent::on_btModifer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    agent = new Core::Agent;
    agent->setIdAgent(liste.at(0).data().toString());
    agent->setNomAgent(liste.at(2).data().toString());
    agent->setPrenomAgent(liste.at(3).data().toString());
    agent->setSexe(liste.at(4).data().toString());
    agent->setDateNaiss(liste.at(5).data().toDate());
    agent->setNationalite(liste.at(6).data().toString());
    agent->setSituation(liste.at(7).data().toString());
    agent->setDiplome(liste.at(8).data().toString());
    agent->setNiveau(liste.at(9).data().toString());
    agent->setTelAgent(liste.at(10).data().toString());
    agent->setAdrAgent(liste.at(11).data().toString());
    agent->setDateAmb(liste.at(12).data().toDate());
    QSqlQuery query;
    query.clear();
    query.prepare("select CodeCategorie from agent where IdAgent='"+liste.at(0).data().toString()+"'");
    if(query.exec()){
        if(query.first())
            agent->setCodeCateg(query.value(0).toString());
    }

    FenMod = new Gui::ModAgent(model,agent,this);
    FenMod->showNormal();
}

void Gui::GesAgent::on_agentTableView_clicked()
{
    liste = agentTableView->selectionModel()->selection().indexes();
}

void Gui::GesAgent::on_btActualiser_clicked()
{
    initComposant();
}

void Gui::GesAgent::on_nomEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprAgent=0 and NomAgent like '"+arg1+"%' and prenomAgent like '"+prenomEdit->text()+"%'");
    liste.clear();
}

void Gui::GesAgent::on_prenomEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprAgent=0 and NomAgent like '"+nomEdit->text()+"%' and prenomAgent like '"+arg1+"%'");
    liste.clear();
}

void Gui::GesAgent::on_btAffecter_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner l'agent à affecter</B>"));
        return;
    }
    agent = new Core::Agent;
    agent->setIdAgent(liste.at(0).data().toString());
    agent->setNomAgent(liste.at(2).data().toString());
    agent->setPrenomAgent(liste.at(3).data().toString());

    FenAffectation = new Gui::Affectation(agent,this);
    FenAffectation->showNormal();
}

void Gui::GesAgent::on_btNommer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner l'agent à nommer</B>"));
        return;
    }
    agent = new Core::Agent;
    agent->setIdAgent(liste.at(0).data().toString());
    agent->setNomAgent(liste.at(2).data().toString());
    agent->setPrenomAgent(liste.at(3).data().toString());

    FenNomination = new Gui::NommerAgent(agent,this);
    FenNomination->showNormal();
}

void Gui::GesAgent::on_btMouvement_clicked()
{
    FenMouvement = new Gui::Mouvement(this);
    FenMouvement->showNormal();
}

void Gui::GesAgent::on_categorieComboBox_currentIndexChanged(const QString &arg1)
{
    if(sexeComboBox->currentText()=="Tout")
        model->setFilter("SupprAgent=0 and LibelleCategorie like '"+arg1+"%'");
    else
        model->setFilter("SupprAgent=0 and LibelleCategorie like '"+arg1+"%' and SexeAgent like '"+sexeComboBox->currentText()+"%'");
    liste.clear();
}

void Gui::GesAgent::on_sexeComboBox_currentIndexChanged(const QString &arg1)
{
    if(sexeComboBox->currentText()=="Tout")
        model->setFilter("SupprAgent=0");
    else
        model->setFilter("SupprAgent=0 and SexeAgent like '"+arg1+"%'");
    liste.clear();
}

void Gui::GesAgent::on_btBulletin_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner l'agent</B>"));
        return;
    }
    agent = new Core::Agent;
    agent->setIdAgent(liste.at(0).data().toString());
    agent->setNomAgent(liste.at(2).data().toString());
    agent->setPrenomAgent(liste.at(3).data().toString());
    agent->setSexe(liste.at(4).data().toString());
    agent->setDateNaiss(liste.at(5).data().toDate());
    agent->setNationalite(liste.at(6).data().toString());
    agent->setSituation(liste.at(7).data().toString());
    agent->setDiplome(liste.at(8).data().toString());
    agent->setNiveau(liste.at(9).data().toString());
    agent->setTelAgent(liste.at(10).data().toString());
    agent->setAdrAgent(liste.at(11).data().toString());
    agent->setDateAmb(liste.at(12).data().toDate());

    bulletin = new Reports::ReportModel(agent);
}

void Gui::GesAgent::on_btApercu_clicked()
{
    QSqlQuery query;
        query.clear();
        query.prepare("select NomAgent,PrenomAgent,SexeAgent,DateNaiss,Nationalite,Situation,Diplome,Niveau,TelAgent,AdrAgent from agent where SupprAgent =0");
        if(query.exec()){
            modelEtat = new QSqlQueryModel;
            modelEtat->setQuery(query);
            modelEtat->setHeaderData(0,Qt::Horizontal,tr("Nom"));
            modelEtat->setHeaderData(1,Qt::Horizontal,tr("Prénom"));
            modelEtat->setHeaderData(2,Qt::Horizontal,tr("Sexe"));
            modelEtat->setHeaderData(3,Qt::Horizontal,tr("Date de naissance"));
            modelEtat->setHeaderData(4,Qt::Horizontal,tr("Nationalité"));
            modelEtat->setHeaderData(5,Qt::Horizontal,tr("Situation"));
            modelEtat->setHeaderData(6,Qt::Horizontal,tr("Diplome"));
            modelEtat->setHeaderData(7,Qt::Horizontal,tr("Niveau"));
            modelEtat->setHeaderData(8,Qt::Horizontal,tr("Telephone"));
            modelEtat->setHeaderData(9,Qt::Horizontal,tr("Adresse"));

            etat = new Reports::EtatNomination("Liste des agents",modelEtat);
}
}
