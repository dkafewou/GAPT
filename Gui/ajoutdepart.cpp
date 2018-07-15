#include "ajoutdepart.h"

using namespace Gui;

AjoutDepart::AjoutDepart(QSqlRelationalTableModel *mod, QWidget *parent) :
    QDialog(parent),mode(mod)
{
    setupUi(this);
    initComposant();
}

void AjoutDepart::initComposant()
{
    model = new QSqlTableModel(this);
    model->setTable("typedepart");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Libelle"));
    model->setHeaderData(2,Qt::Horizontal,tr("Suppr"));
    model->setFilter("SupprTypeDepart=0");
    model->select();

    typedepartCombo->setModel(model);
    typedepartCombo->setModelColumn(1);
    typedepartCombo->setAutoCompletion(true);
    typedepartCombo->show();

    datedepartEdit->setDate(QDate::currentDate());
    agent = new Core::Agent;
}

bool AjoutDepart::champsVide()
{
    if(agentEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir l'agent");
        btAgent->setFocus();
        return true;
    }
    if(motifdepartEdit->toPlainText().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner la cause");
        motifdepartEdit->setFocus();
        return true;
    }
    return false;
}

void Gui::AjoutDepart::on_btAgent_clicked()
{
    FenListe = new Gui::ListeAgent(agent,agentEdit,this);
    FenListe->showNormal();
}

void Gui::AjoutDepart::on_btValider_clicked()
{
    if(champsVide())
        return;
    if(typedepartCombo->currentText().left(3)!="DEC"){
        if(datedepartEdit->date().operator <(QDate::currentDate())){
            QMessageBox::critical(this,"ERREUR 11810","Date invalide");
            datedepartEdit->setFocus();
            return;
        }
    }
    depart = new Core::Depart;
    depart->setAgent(agent->getIdAgent());
    depart->setMotif(motifdepartEdit->toPlainText());
    depart->setType(typedepartCombo->currentText().left(3));
    depart->setDdep(datedepartEdit->date());
    depart->setSuppr(false);
    depart->setCode(depart->generate());
    if(depart->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Ce Départ existe déjà  pour cet agent"));
        delete depart;
        return;
    }
    if(depart->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Départ enregistré"));
        agentEdit->clear();
        motifdepartEdit->clear();
        agent->remove();
        mode->select();
        QSqlQuery query;
        if(query.exec("select IdUtilisateur from utilisateur where IdAgent='"+depart->getAgent()+"'")){
            while (query.next()){
                users = new Core::Utilisateur;
                users->setCode(query.value(0).toString());
                users->remove();
                delete users;
            }
        }
        delete depart;
    }
}
