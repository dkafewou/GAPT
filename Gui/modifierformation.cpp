#include "modifierformation.h"

using namespace Gui;

ModifierFormation::ModifierFormation(Core::Formation *form, QSqlTableModel *mod, QWidget *parent) :
    QDialog(parent),formation(form),mode(mod)
{
    setupUi(this);
    initComposant();
    initTable();
}

void ModifierFormation::initComposant()
{
    libelleEdit->setText(formation->getLibelle());
    villeEdit->setText(formation->getVille());
    paysComboBox->setCurrentIndex(paysComboBox->findText(formation->getPays()));
    debutDateEdit->setDate(formation->getDebut());
    finDateEdit->setDate(formation->getFin());
    effectiveDateEdit->setDate(formation->getReel());

    agent = new Core::Agent;
    model = new QSqlQueryModel(this);
}

bool ModifierFormation::champVideFormation()
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
    if(debutDateEdit->date().operator <(formation->getDebut())){
        QMessageBox::critical(this,"ERREUR 11810","Date debut invalide");
        debutDateEdit->setFocus();
        return true;
    }
    if(finDateEdit->date().operator <(debutDateEdit->date())){
        QMessageBox::critical(this,"ERREUR 11810","Date Fin invalide");
        finDateEdit->setFocus();
        return true;
    }
    if(effectiveDateEdit->date().operator <(debutDateEdit->date())){
        QMessageBox::critical(this,"ERREUR 11810","Date invalide");
        effectiveDateEdit->setFocus();
        return true;
    }
    return false;
}

void ModifierFormation::initTable()
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

void Gui::ModifierFormation::on_btOk_clicked()
{
    if(champVideFormation())
        return;
    modForm = new Core::Formation;
    modForm->setCode(formation->getCode());
    modForm->setLibelle(libelleEdit->text());
    modForm->setVille(villeEdit->text());
    modForm->setPays(paysComboBox->currentText());
    modForm->setDebut(debutDateEdit->date());
    modForm->setFin(finDateEdit->date());
    modForm->setReel(effectiveDateEdit->date());
    if(modForm->Equal(formation)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        libelleEdit->setFocus();
        delete modForm;
        return ;
    }
    if(modForm->update()){
        QMessageBox::information(this, tr("Succès"), tr("<B>Formation modifiée</B>") ) ;
        formation->Clone(modForm);
        mode->select();
        delete modForm;
    }
}

void Gui::ModifierFormation::on_agentTableView_clicked()
{
    liste = agentTableView->selectionModel()->selection().indexes();
}

void Gui::ModifierFormation::on_btSupprimer_clicked()
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
               QMessageBox::information(this, tr("Succés"), tr("<B>Ligne Supprimée </B>") ) ;
               initTable();
           }
        }
}

void Gui::ModifierFormation::on_btAgent_clicked()
{
    FenListeAgent = new Gui::ListeAgent(agent,agentEdit,this);
    FenListeAgent->showNormal();
}

void Gui::ModifierFormation::on_btAjouter_clicked()
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
        QMessageBox::critical(this,tr("Erreur 20320"),tr("Agent déjà  dans la liste"));
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

void Gui::ModifierFormation::on_matrEdit_textChanged(const QString &arg1)
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
    liste.clear();
}

void Gui::ModifierFormation::on_nomEdit_textChanged(const QString &arg1)
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
    liste.clear();
}
