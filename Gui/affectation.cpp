#include "affectation.h"

using namespace Gui;

Affectation::Affectation(Core::Agent *ag, QWidget *parent) :
    QDialog(parent),agent(ag)
{
    setupUi(this);
    initComposant();
}

void Affectation::initComposant()
{
    travail = new Core::travail;
    debutDateEdit->setDate(QDate::currentDate());
    agentEdit->setText(agent->getNomAgent()+" "+agent->getPrenomAgent());
}

bool Affectation::champsVide()
{
    if(posteEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir la fonction à occuper");
        posteEdit->setFocus();
        return true;
    }
    if(serviceEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir le service");
        serviceEdit->setFocus();
        return true;
    }
    if(debutDateEdit->date() < QDate::currentDate()){
        QMessageBox::critical(this,"ERREUR 102340","Date debut de service incorrecte\n Ne doit pas être anterieure à celle d'aujourd'huit");
        debutDateEdit->setFocus();
        return true;
    }
    return false;
}

void Gui::Affectation::on_btPoste_clicked()
{
    FenPoste = new Gui::ListePoste(posteEdit,travail,this);
    FenPoste->showNormal();
}

void Gui::Affectation::on_btService_clicked()
{
    FenService = new Gui::ListeService(serviceEdit,travail,this);
    FenService->showNormal();
}

void Gui::Affectation::on_btValider_clicked()
{
    if(champsVide())
        return;
    QSqlQuery query;
    query.clear();
    query.prepare("SELECT * FROM travail  where IdAgent='"+agent->getIdAgent()+"' and Date_Fin is null");
    if(query.exec()){
        if(query.first()){
            FinTtravail = new Core::travail;
            FinTtravail->setAgent(agent->getIdAgent());
            FinTtravail->setFonction(query.value(1).toString());
            FinTtravail->setService(query.value(2).toString());
            FinTtravail->setDatefin(debutDateEdit->date());
            FinTtravail->setDatedebut(query.value(3).toDate());
            FinTtravail->update();
        }
    }
    travail->setAgent(agent->getIdAgent());
    travail->setDatedebut(debutDateEdit->date());
    if(travail->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Affectation existante"));
        return;
    }
    if(travail->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Agent affecté"));
        if(travail->getFonction()=="CHS"){
            query.clear();
            query.prepare("SELECT * FROM travail  where CodeFonction='"+travail->getFonction()+"' and CodeService='"+travail->getService()+"' and Date_Fin is null");
            if(query.exec()){
                if(query.first()){
                    FinTtravail = new Core::travail;
                    FinTtravail->setAgent(query.value(0).toString());
                    FinTtravail->setFonction(query.value(1).toString());
                    FinTtravail->setService(query.value(2).toString());
                    FinTtravail->setDatefin(debutDateEdit->date());
                    FinTtravail->setDatedebut(query.value(3).toDate());
                    FinTtravail->update();
                 }
             }
         }
         this->close();
         delete travail;
         delete agent;
         delete FinTtravail;
    }
}
