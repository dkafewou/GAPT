#include "ajoutformation.h"

using namespace Gui;

AjoutFormation::AjoutFormation(QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),mode(mod)
{
    setupUi(this);
    initComposant();
}

void AjoutFormation::initComposant()
{
    debutDateEdit->setDate(QDate::currentDate());
    finDateEdit->setDate(QDate::currentDate());
    effectiveDateEdit->setDate(QDate::currentDate());
}

bool AjoutFormation::champVideFormation()
{
    if(libelleEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le libellé");
        libelleEdit->setFocus();
        return true;
    }
    if(villeEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner la Ville");
        villeEdit->setFocus();
        return true;
    }
    if(debutDateEdit->date().operator <(QDate::currentDate())){
        QMessageBox::critical(this,"ERREUR 11810","Date debut invalide");
        debutDateEdit->setFocus();
        return true;
    }
    if(finDateEdit->date().operator <(debutDateEdit->date())){
        QMessageBox::critical(this,"ERREUR 11810","Date Fin invalide");
        finDateEdit->setFocus();
        return true;
    }
    return false;
}

void AjoutFormation::initParticipant()
{
    libelleEdit->setEnabled(false);
    villeEdit->setEnabled(false);
    paysComboBox->setEnabled(false);
    debutDateEdit->setEnabled(false);
    finDateEdit->setEnabled(false);

    btOk->setEnabled(false);
    btAnnuler->setEnabled(false);

    btSupprimer->setEnabled(true);
    btAjouter->setEnabled(true);
    btAnnule->setEnabled(true);
    btAgent->setEnabled(true);

    agent = new Core::Agent;
}

void AjoutFormation::initTable()
{
    query.prepare("select p.CodeFormation,p.IdAgent,a.NomAgent,p.SupprPart from participant p,agent a where p.IdAgent=a.IdAgent and SupprPart=0 and CodeFormation=?");
    query.bindValue(0,formation->getCode());
    if(!query.exec())
        return;
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Matricule"));
    model->setHeaderData(2,Qt::Horizontal,tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,tr("Suppr"));

    agentTableView->setModel(model);
    agentTableView->hideColumn(0);
    agentTableView->hideColumn(3);
    agentTableView->show();
}

void Gui::AjoutFormation::on_finDateEdit_dateChanged(const QDate &date)
{
    effectiveDateEdit->setDate(date);
}

void Gui::AjoutFormation::on_btOk_clicked()
{
    if (champVideFormation())
        return;
    formation = new Core::Formation;
    formation->setLibelle(libelleEdit->text());
    formation->setVille(villeEdit->text());
    formation->setPays(paysComboBox->currentText());
    formation->setDebut(debutDateEdit->date());
    formation->setFin(finDateEdit->date());
    formation->setReel(effectiveDateEdit->date());
    formation->setSuppr(false);
    formation->setCode(formation->generate());
    if(formation->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Cette formation existe déjà "));
        return;
    }
    if(formation->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Formation  enregistrée"));
        initParticipant();
        mode->select();
        model = new QSqlQueryModel(this);
        initTable();
    }
}

void Gui::AjoutFormation::on_btAgent_clicked()
{
    FenListeAgent = new Gui::ListeAgent(agent,agentEdit,this);
    FenListeAgent->showNormal();
}

void Gui::AjoutFormation::on_btAjouter_clicked()
{
    if(agentEdit->text().isEmpty()){
        QMessageBox::critical(this,tr("Erreur 20320"),tr("Veuillez choisir l'agent"));
        btAgent->setFocus();
        return;
    }
    participant = new Core::Participant;
    participant->setCode(formation->getCode());
    participant->setAgent(agent->getIdAgent());
    participant->setSuppr(false);
    if(participant->Existe()){
        QMessageBox::critical(this,tr("Erreur 20320"),tr("Agent déjà dans la liste"));
        btAgent->setFocus();
        delete participant;
        return;
    }
    if(participant->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Participant ajouté"));
        initTable();
        agentEdit->clear();
        delete participant;
    }
}

void Gui::AjoutFormation::on_agentTableView_clicked()
{
    liste = agentTableView->selectionModel()->selection().indexes();
}

void Gui::AjoutFormation::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            participant = new Core::Participant;
            participant->setCode(formation->getCode());
            participant->setAgent(liste.at(1).data().toString());
           if(participant->Delete()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               initTable();
           }
        }
}

void Gui::AjoutFormation::on_matrEdit_textChanged(const QString &arg1)
{
    query.prepare("select p.CodeFormation,p.IdAgent,a.NomAgent,p.SupprPart from participant p,agent a where p.IdAgent=a.IdAgent and SupprPart=0 and p.IdAgent like '"+arg1+"%' and a.NomAgent like '"+nomEdit->text()+"%' and CodeFormation=?");
    query.bindValue(0,formation->getCode());
    if(!query.exec())
        return;
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Matricule"));
    model->setHeaderData(2,Qt::Horizontal,tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,tr("Suppr"));

    agentTableView->setModel(model);
    agentTableView->hideColumn(0);
    agentTableView->hideColumn(3);
    agentTableView->show();
}

void Gui::AjoutFormation::on_nomEdit_textChanged(const QString &arg1)
{
    query.prepare("select p.CodeFormation,p.IdAgent,a.NomAgent,p.SupprPart from participant p,agent a where p.IdAgent=a.IdAgent and SupprPart=0 and p.IdAgent like '"+matrEdit->text()+"%' and a.NomAgent like '"+arg1+"%' and CodeFormation=?");
    query.bindValue(0,formation->getCode());
    if(!query.exec())
        return;
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Matricule"));
    model->setHeaderData(2,Qt::Horizontal,tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,tr("Suppr"));

    agentTableView->setModel(model);
    agentTableView->hideColumn(0);
    agentTableView->hideColumn(3);
    agentTableView->show();
}
