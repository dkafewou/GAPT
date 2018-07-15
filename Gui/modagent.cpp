#include "modagent.h"

using namespace Gui;

ModAgent::ModAgent(QSqlRelationalTableModel *mod, Core::Agent *ag, QWidget *parent) :
    QDialog(parent),model(mod),agent(ag)
{
    setupUi(this);
    initComposant();
}

void ModAgent::initComposant()
{
    validator = new QDoubleValidator(0,999999999,0,this);
    telEdit->setValidator( validator );

    categorieEdit->setText(agent->getCodeCateg());
    nomEdit->setText(agent->getNomAgent());
    prenomEdit->setText(agent->getPrenomAgent());
    sexeCombo->setCurrentIndex(sexeCombo->findText(agent->getSexe()));
    datenaissEdit->setDate(agent->getDateNaiss());
    dateembaucheEdit->setDate(agent->getDateAmb());
    nationaliteComboBox->setCurrentIndex(nationaliteComboBox->findText(agent->getNationalite()));
    situationComboBox->setCurrentIndex(situationComboBox->findText(agent->getSituation()));
    diplomeEdit->setText(agent->getDiplome());
    niveauComboBox->setCurrentIndex(niveauComboBox->findText(agent->getNiveau()));
    telEdit->setText(agent->getTelAgent());
    adresseEdit->setPlainText(agent->getAdrAgent());
}

bool ModAgent::champsVides()
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
    if(datenaissEdit->date().operator >(QDate::currentDate().addYears(-18))){
        QMessageBox::critical(this,"ERREUR 10234","Veuillez choisir une date de naissance supperieur à 18ans");
        datenaissEdit->setFocus();
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

    return false;
}

void Gui::ModAgent::on_datenaissEdit_dateChanged(const QDate &date)
{
    if(date.operator >(QDate::currentDate().addYears(-18))){
        QMessageBox::critical(this,"ERREUR 10234","Veuillez choisir une date de naissance supperieur à 18ans");
        datenaissEdit->setFocus();
    }
}

void Gui::ModAgent::on_btCategorie_clicked()
{
    FenCateg = new Gui::ListeCategorie(categorieEdit,agent,this);
    FenCateg->showNormal();
}

void Gui::ModAgent::on_btValider_clicked()
{
    if(champsVides())
        return;
    modAg = new Core::Agent;
    modAg->setNomAgent(nomEdit->text());
    modAg->setPrenomAgent(prenomEdit->text());
    modAg->setSexe(sexeCombo->currentText());
    modAg->setDateNaiss(datenaissEdit->date());
    modAg->setDateAmb(dateembaucheEdit->date());
    modAg->setNationalite(nationaliteComboBox->currentText());
    modAg->setSituation(situationComboBox->currentText());
    modAg->setDiplome(diplomeEdit->text());
    modAg->setNiveau(niveauComboBox->currentText());
    modAg->setTelAgent(telEdit->text());
    modAg->setAdrAgent(adresseEdit->toPlainText());
    modAg->setSuprAgent(false);
    modAg->setIdAgent(agent->getIdAgent());
    modAg->setCodeCateg(agent->getCodeCateg());
    if(modAg->Equal(agent)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        nomEdit->setFocus();
        delete modAg;
        return;
    }
    if(modAg->update()){
        model->select();
        QMessageBox::information(this,tr("SUCCES"),tr("Agent modifié"));
        delete agent;
        delete modAg;
        this->close();
    }
}
