#include "ajoutdepdos.h"

using namespace Gui;

AjoutDepDos::AjoutDepDos(Core::Dossier *dos, QWidget *parent) :
    QDialog(parent),dossier(dos)
{
    setupUi(this);
    initComposant();
    initCombo();
    initDossier();
    initTable();
}

void AjoutDepDos::initComposant()
{
    validator = new QDoubleValidator(0,999999999,3,this);
    montantEdit->setValidator( validator );

    agent = new Core::Agent;
    depense = new Core::Depense;

    btValide->setVisible(false);

    dateEdit->setDate(QDate::currentDate());
    timeEdit->setTime(QTime::currentTime());
    agentEdit->clear();
    bonEdit->clear();
    montantEdit->clear();
}

void AjoutDepDos::initDossier()
{
    clientComboBox->setCurrentIndex(clientComboBox->findText(dossier->getClient()));
    repEdit->setText(dossier->getRep());
    recepdateEdit->setDate(dossier->getDateRec());
    arrdateEdit->setDate(dossier->getDateArr());
}

void AjoutDepDos::initTable()
{
    modelCont = new QSqlRelationalTableModel;
    modelCont->setTable("subir");
    modelCont->setHeaderData(0,Qt::Horizontal,tr("Rep"));
    modelCont->setHeaderData(1,Qt::Horizontal,tr("Agent"));
    modelCont->setHeaderData(2,Qt::Horizontal,tr("Bon pour"));
    modelCont->setHeaderData(3,Qt::Horizontal,tr("Date"));
    modelCont->setHeaderData(4,Qt::Horizontal,tr("Heure"));
    modelCont->setHeaderData(5,Qt::Horizontal,tr("Montant"));
    modelCont->setHeaderData(6,Qt::Horizontal,tr("Suppr"));
    modelCont->setRelation(1, QSqlRelation("agent", "IdAgent", "NomAgent"));
    modelCont->setRelation(2, QSqlRelation("depense", "CodeDepense", "Libelle"));
    modelCont->setFilter("SupprSubir=0 and RepDossier ='"+dossier->getRep()+"' ");
    modelCont->select();

    contTableView->setModel(modelCont);
    contTableView->hideColumn(0);
    contTableView->hideColumn(6);
    contTableView->show();
}

void AjoutDepDos::initCombo()
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

    clientComboBox->setModel( model );
    clientComboBox->setModelColumn(1);
    clientComboBox->showMinimized();
}

bool AjoutDepDos::champsVide()
{
    if(agentEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir l'agent");
                btAgent->setFocus();
                return true;
            }
    if(bonEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir la depense");
                btDep->setFocus();
                return true;
            }
    if(montantEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le montant total");
                montantEdit->setFocus();
                return true;
            }
    return false;
}

void Gui::AjoutDepDos::on_btAgent_clicked()
{
    FenAgent = new Gui::ListeAgent(agent,agentEdit,this);
    FenAgent->showNormal();
}

void Gui::AjoutDepDos::on_btDep_clicked()
{
    FenDepense = new Gui::ListeDepense(bonEdit,depense,this);
    FenDepense->showNormal();
}

void Gui::AjoutDepDos::on_bonEdit_textChanged()
{
    QSqlQuery query;
    if(query.exec("select count(*) from conteneur where RepDossier='"+dossier->getRep()+"'")){
        if(query.first())
            montantEdit->setText(QString::number(depense->getMontant()*query.value(0).toInt()));
    }
}

void Gui::AjoutDepDos::on_btAjouter_clicked()
{
    if(champsVide())
        return;
    subir = new Core::Subir;
    subir->setDossier(dossier->getRep());
    subir->setAgent(agent->getIdAgent());
    subir->setDepense(depense->getCode());
    subir->setDate(dateEdit->date());
    subir->setTime(timeEdit->time());
    subir->setMontant(montantEdit->text().toDouble());
    subir->setSuppr(false);
    if(subir->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("dépense déjà  effectuée pour ce dossier"));
        delete subir;
        return;
    }
    if(subir->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Dépense enregistrée pour ce dossier"));
        delete subir;
        agentEdit->clear();
        bonEdit->clear();
        montantEdit->clear();
        modelCont->select();
    }
}

void Gui::AjoutDepDos::on_btValide_clicked()
{
    if(champsVide())
        return;
    modSub = new Core::Subir;
    modSub->setDossier(dossier->getRep());
    modSub->setAgent(agentEdit->text());
    modSub->setDepense(subir->getDepense());
    modSub->setDate(dateEdit->date());
    modSub->setTime(timeEdit->time());
    modSub->setMontant(montantEdit->text().toDouble());
    modSub->setSuppr(false);
    if(modSub->Equal(subir)){
         QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
         delete modSub;
         btAgent->setFocus();
         return;
    }
    modSub->setAgent(agent->getIdAgent());
    if(modSub->update()){
         QMessageBox::information(this,tr("SUCCES"),tr("Données de depense modifiées"));
         modelCont->select();
         btAjouter->setVisible(true);
         btEffacer->setVisible(true);
         dateEdit->setReadOnly(true);
         timeEdit->setReadOnly(true);
         btDep->setEnabled(true);
         btAgent->setEnabled(true);
         initComposant();
    }
}

void Gui::AjoutDepDos::on_contTableView_clicked()
{
    liste = contTableView->selectionModel()->selection().indexes();
}

void Gui::AjoutDepDos::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer ce client?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            subir = new Core::Subir;
            QSqlQuery query;
            if(query.exec("select CodeDepense from depense where Libelle='"+liste.at(2).data().toString()+"'")){
                query.first();
                subir->setDepense(query.value(0).toString());
            }
            subir->setDossier(dossier->getRep());
           if(subir->Delete()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Dépense supprimée</B>") ) ;
               modelCont->select();
               delete subir;
           }
        }
}

void Gui::AjoutDepDos::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    subir = new Core::Subir;
    QSqlQuery query;
    if(query.exec("select CodeDepense from depense where Libelle='"+liste.at(2).data().toString()+"'")){
        query.first();
        subir->setDepense(query.value(0).toString());
    }
    subir->setDossier(liste.at(0).data().toString());
    subir->setAgent(liste.at(1).data().toString());
    subir->setDate(liste.at(3).data().toDate());
    subir->setTime(liste.at(4).data().toTime());
    subir->setMontant(liste.at(5).data().toDouble());

    agentEdit->setText(liste.at(1).data().toString());
    bonEdit->setText(liste.at(2).data().toString());
    dateEdit->setDate(liste.at(3).data().toDate());
    timeEdit->setTime(liste.at(4).data().toTime());
    montantEdit->setText(liste.at(5).data().toString());

    btAjouter->setVisible(false);
    btEffacer->setVisible(false);
    btValide->setVisible(true);
    dateEdit->setReadOnly(false);
    timeEdit->setReadOnly(false);
    btDep->setEnabled(false);
    btAgent->setEnabled(false);
}

void Gui::AjoutDepDos::on_btVoir_clicked()
{
    QSqlQuery query;
    query.clear();
    query.prepare("select d.Libelle,m.MontantReel from depense d,subir m where d.CodeDepense=m.CodeDepense and m.RepDossier='"+dossier->getRep()+"' and supprSubir=0");
    if(query.exec()){
        modelEtat = new QSqlQueryModel;
        modelEtat->setQuery(query);
        modelEtat->setHeaderData(0,Qt::Horizontal,tr("Libelle"));
        modelEtat->setHeaderData(1,Qt::Horizontal,tr("Montant"));

        prefact = new Reports::ReportDepense(dossier,modelEtat);
    }
}
