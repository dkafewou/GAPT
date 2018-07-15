#include "ajoutagent.h"

using namespace Gui;

AjoutAgent::AjoutAgent(QSqlRelationalTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
    initComposant();
}

void AjoutAgent::initComposant()
{
    agent = new Core::Agent();
    travai =new Core::travail;
    validator = new QDoubleValidator(0,99999999,0,this);
    telEdit->setValidator( validator );
    dateembaucheEdit->setDate(QDate::currentDate());
    debutDateEdit->setDate(QDate::currentDate());
    datenaissEdit->setDate(QDate::currentDate().addYears(-18));
}

bool AjoutAgent::champsVides()
{
    if(categorieEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir la categorie de l'employé");
        btCategorie->setFocus();
        return true;
    }
    if(nomEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le nom");
        nomEdit->setFocus();
        return true;
    }
    if(prenomEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le prenom");
        prenomEdit->setFocus();
        return true;
    }
    if(diplomeEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le diplôme");
        diplomeEdit->setFocus();
        return true;
    }
    if(telEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le telephone");
        telEdit->setFocus();
        return true;
    }
    if(adresseEdit->toPlainText().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner l'adresse");
        adresseEdit->setFocus();
        return true;
    }
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
    return false;
}

void Gui::AjoutAgent::on_btPoste_clicked()
{
    FenListePoste = new Gui::ListePoste(posteEdit,travai,this);
    FenListePoste->showNormal();
}

void Gui::AjoutAgent::on_btService_clicked()
{
    FenListeService = new Gui::ListeService(serviceEdit,travai,this);
    FenListeService->showNormal();
}

void Gui::AjoutAgent::on_btCategorie_clicked()
{
    FenListeCategorie = new Gui::ListeCategorie(categorieEdit,agent,this);
    FenListeCategorie->showNormal();
}

void Gui::AjoutAgent::on_datenaissEdit_dateChanged(const QDate &date)
{
    if(date.operator >(QDate::currentDate().addYears(-18))){
        QMessageBox::critical(this,"ERREUR 10234","Veuillez choisir une date de naissance supperieur à 18ans");
        datenaissEdit->setFocus();
    }
}

void Gui::AjoutAgent::on_btValider_clicked()
{
    if(champsVides())
        return;
    if(datenaissEdit->date().operator >(QDate::currentDate().addYears(-18))){
        QMessageBox::critical(this,"ERREUR 10234","Veuillez choisir une date de naissance supperieur à 18ans");
        datenaissEdit->setFocus();
        return;
    }
    if(dateembaucheEdit->date() < QDate::currentDate()){
        QMessageBox::critical(this,"ERREUR 102340","Date ambauche incorrecte\n Ne doit pas être anterieure à celle d'aujourd'hui");
        dateembaucheEdit->setFocus();
        return;
    }
    if(debutDateEdit->date() < dateembaucheEdit->date()){
        QMessageBox::critical(this,"ERREUR 102340","Date debut de service incorrecte\n Ne doit pas être anterieure à celle d'ambauche");
        debutDateEdit->setFocus();
        return;
    }
    agent->setNomAgent(nomEdit->text());
    agent->setPrenomAgent(prenomEdit->text());
    agent->setSexe(sexeCombo->currentText());
    agent->setDateNaiss(datenaissEdit->date());
    agent->setNationalite(nationaliteComboBox->currentText());
    agent->setSituation(situationComboBox->currentText());
    agent->setDiplome(diplomeEdit->text());
    agent->setNiveau(niveauComboBox->currentText());
    agent->setTelAgent(telEdit->text());
    agent->setAdrAgent(adresseEdit->toPlainText());
    agent->setDateAmb(dateembaucheEdit->date());
    agent->setSuprAgent(false);
    agent->setIdAgent(agent->generate());
    if(agent->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Cet agent existe déjà "));
        return;
    }
    if(agent->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Cet agent a été bien enregistré"));
        model->select();
        travai->setAgent(agent->getIdAgent());
        travai->setDatedebut(debutDateEdit->date());
        travai->save();
        if(travai->getFonction()=="CHS"){
            QSqlQuery query;
            query.clear();
            query.clear();
            query.prepare("SELECT * FROM travail  where CodeFonction='"+travai->getFonction()+"' and CodeService='"+travai->getService()+"' and Date_Fin is null");
            if(query.exec()){
                if(query.first()){
                    travai->setAgent(query.value(0).toString());
                    travai->setFonction(query.value(1).toString());
                    travai->setService(query.value(2).toString());
                    travai->setDatefin(debutDateEdit->date());
                    travai->setDatedebut(query.value(3).toDate());
                    travai->update();
                 }
             }
         }
        delete agent;
        delete travai;
        categorieEdit->clear();
        nomEdit->clear();
        prenomEdit->clear();
        dateembaucheEdit->setDate(QDate::currentDate());
        debutDateEdit->setDate(QDate::currentDate());
        datenaissEdit->setDate(QDate::currentDate().addYears(-18));
        telEdit->clear();
        adresseEdit->clear();
        diplomeEdit->clear();
    }
}
