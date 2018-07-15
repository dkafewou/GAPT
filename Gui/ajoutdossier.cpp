#include "ajoutdossier.h"

using namespace Gui;

AjoutDossier::AjoutDossier(QSqlRelationalTableModel *mod, QWidget *parent) :
    QDialog(parent),modelDoss(mod)
{
    setupUi(this);
    initCombo();
    initComposant();
}

AjoutDossier::AjoutDossier(Core::Dossier *dos, QSqlRelationalTableModel *mod, QWidget *parent) :
    QDialog(parent),modelDoss(mod),dossier(dos)
{
    setupUi(this);
    this->setWindowTitle("Modifier dossier");
    initCombo();
    initComposantMod();
    initTable();
}

void AjoutDossier::initComposant()
{
    validator = new QDoubleValidator(0,999999999,0,this);
    numeroEdit->setValidator( validator );

    recepdateEdit->setDate(QDate::currentDate());
    arrdateEdit->setDate(QDate::currentDate());

    btModif->setVisible(false);
    btValide->setVisible(false);
}

void AjoutDossier::initCombo()
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

void AjoutDossier::initComposantMod()
{
    btValider->setVisible(false);
    btModif->setVisible(true);
    btAnnuler->setVisible(false);
    btValide->setVisible(false);
    btModifier->setEnabled(true);
    btSupprimer->setEnabled(true);
    btAjouter->setEnabled(true);

    validator = new QDoubleValidator(0,999999999,0,this);
    numeroEdit->setValidator( validator );

    clientComboBox->setCurrentIndex(clientComboBox->findText(dossier->getClient()));
    repEdit->setText(dossier->getRep());
    recepdateEdit->setDate(dossier->getDateRec());
    arrdateEdit->setDate(dossier->getDateArr());
}

void AjoutDossier::initConteneur()
{
    clientComboBox->setEnabled(false);
    repEdit->setEnabled(false);
    arrdateEdit->setEnabled(false);
    recepdateEdit->setEnabled(false);
    btValider->setEnabled(false);
    btAnnuler->setEnabled(false);

    btAjouter->setEnabled(true);
    btModifier->setEnabled(true);
    btSupprimer->setEnabled(true);
}

void AjoutDossier::initTable()
{
    modelCont = new QSqlTableModel;
    modelCont->setTable("conteneur");
    modelCont->setHeaderData(0,Qt::Horizontal,tr("Code"));
    modelCont->setHeaderData(1,Qt::Horizontal,tr("Rep"));
    modelCont->setHeaderData(2,Qt::Horizontal,tr("Numero"));
    modelCont->setHeaderData(3,Qt::Horizontal,tr("Marchandise"));
    modelCont->setHeaderData(4,Qt::Horizontal,tr("Type"));
    modelCont->setHeaderData(5,Qt::Horizontal,tr("Suppr"));
    modelCont->setFilter("SupprConteneur=0 and RepDossier ='"+dossier->getRep()+"' ");
    modelCont->select();

    contTableView->setModel(modelCont);
    contTableView->hideColumn(0);
    contTableView->hideColumn(1);
    contTableView->hideColumn(5);
    contTableView->show();
}

bool AjoutDossier::champsVide()
{
    if(repEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le repertoire");
        repEdit->setFocus();
        return true;
    }
    if(recepdateEdit->date().operator <(QDate::currentDate())){
        QMessageBox::critical(this,"ERREUR 11810","Date invalide");
        recepdateEdit->setFocus();
        return true;
    }
    return false;
}

bool AjoutDossier::champsVideCont()
{
    if(numeroEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le numéro");
        numeroEdit->setFocus();
        return true;
    }
    if(marchandiseEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner la marchandise");
        marchandiseEdit->setFocus();
        return true;
    }
    return false;
}

void Gui::AjoutDossier::on_btValider_clicked()
{
    if(champsVide())
        return;
    QSqlQuery *query = new QSqlQuery;
    if(query->exec("select CodeClient from client where NomClient ='"+clientComboBox->currentText()+"'")){
        if (query->first()){
            dossier = new Core::Dossier;
            dossier->setRep(repEdit->text());
            dossier->setClient(query->value(0).toString());
            dossier->setDateArr(recepdateEdit->date());
            dossier->setDateRec(arrdateEdit->date());
            dossier->setSuppr(false);
            if(dossier->Existe()){
                QMessageBox::critical(this,tr("Doublon"),tr("Ce repertoire existe déjà"));
                repEdit->setFocus();
                delete dossier;
                return;
            }
            if(dossier->save()){
                QMessageBox::information(this,tr("SUCCES"),tr("Dossier enregistré"));
                initConteneur();
                modelDoss->select();
                initTable();
            }
        }
    }
}

void Gui::AjoutDossier::on_btAjouter_clicked()
{
    if(champsVideCont())
        return;
    conteneur = new Core::Conteneur;
    conteneur->setNumero(numeroEdit->text());
    conteneur->setMarchandise(marchandiseEdit->text());
    conteneur->setRep(dossier->getRep());
    conteneur->setType(typeComboBox->currentText());
    conteneur->setSuppr(false);
    conteneur->setCode(conteneur->generate());
    if(conteneur->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Ce conteneur est déjà ajouté au dossier"));
        numeroEdit->setFocus();
        delete conteneur;
        return;
    }
    if(conteneur->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Conteneur ajouté au dossier"));
        modelCont->select();
        numeroEdit->clear();
        marchandiseEdit->clear();
        delete conteneur;
    }
}

void Gui::AjoutDossier::on_contTableView_clicked()
{
    liste = contTableView->selectionModel()->selection().indexes();
}

void Gui::AjoutDossier::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            conteneur = new Core::Conteneur;
            conteneur->setCode(liste.at(0).data().toString());
           if(conteneur->Delete()){
               QMessageBox::information(this, tr("SuccÃ¨s"), tr("<B>Ligne Supprimée </B>") ) ;
               modelCont->select();
               delete conteneur;
           }
        }
}

void Gui::AjoutDossier::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    conteneur = new Core::Conteneur;
    conteneur->setCode(liste.at(0).data().toString());
    conteneur->setRep(liste.at(1).data().toString());
    conteneur->setNumero(liste.at(2).data().toString());
    conteneur->setMarchandise(liste.at(3).data().toString());
    conteneur->setType(liste.at(4).data().toString());

    numeroEdit->setText(liste.at(2).data().toString());
    marchandiseEdit->setText(liste.at(3).data().toString());
    typeComboBox->setCurrentIndex(typeComboBox->findText(liste.at(4).data().toString()));

    btAjouter->setVisible(false);
    btEffacer->setVisible(false);
    btValide->setVisible(true);
}

void Gui::AjoutDossier::on_btValide_clicked()
{
    if(champsVideCont())
        return;
    modCont = new Core::Conteneur;
    modCont->setNumero(numeroEdit->text());
    modCont->setMarchandise(marchandiseEdit->text());
    modCont->setRep(conteneur->getRep());
    modCont->setType(typeComboBox->currentText());
    modCont->setSuppr(false);
    modCont->setCode(conteneur->getCode());
    if(modCont->Equal(conteneur)){
        QMessageBox::critical(this,tr("Doublon"),tr("Aucune modifictation n'a été effectuée"));
        numeroEdit->setFocus();
        delete modCont;
        return;
    }
    if(modCont->update()){
        QMessageBox::information(this,tr("SUCCES"),tr("Donnés modifiées avec succès"));
        modelCont->select();
        numeroEdit->clear();
        marchandiseEdit->clear();
        btAjouter->setVisible(true);
        btEffacer->setVisible(true);
        btValide->setVisible(false);
        delete conteneur;
        delete modCont;
    }
}

void Gui::AjoutDossier::on_btModif_clicked()
{
    if(champsVide())
        return;
    ModDoss = new Core::Dossier;
    ModDoss->setRep(repEdit->text());
    ModDoss->setClient(clientComboBox->currentText());
    ModDoss->setDateArr(recepdateEdit->date());
    ModDoss->setDateRec(arrdateEdit->date());
    ModDoss->setSuppr(false);
    if(ModDoss->Equal(dossier)){
        QMessageBox::critical(this,tr("Doublon"),tr("Aucune modifictation n'a été effectuée"));
        clientComboBox->setFocus();
        delete ModDoss;
        return;
    }
    QSqlQuery *query = new QSqlQuery;
    if(query->exec("select CodeClient from client where NomClient ='"+clientComboBox->currentText()+"'")){
        if (query->first()){
            ModDoss->setClient(query->value(0).toString());
            if(ModDoss->update(dossier->getRep())){
                QMessageBox::information(this,tr("SUCCES"),tr("Données modifiées avec succès"));
                modelDoss->select();
                dossier->setRep(ModDoss->getRep());
                delete ModDoss;
            }
        }
    }
}
