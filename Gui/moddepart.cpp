#include "moddepart.h"

using namespace Gui;

ModDepart::ModDepart(Core::Depart *dep, QSqlRelationalTableModel *mod, QWidget *parent) :
    QDialog(parent),depart(dep),mode(mod)
{
    setupUi(this);
    initComposant();
}

void ModDepart::initComposant()
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

    agentEdit->setText(depart->getAgent());
    motifdepartEdit->setPlainText(depart->getMotif());
    datedepartEdit->setDate(depart->getDdep());
    typedepartCombo->setCurrentIndex(typedepartCombo->findText(depart->getType()));
    depart->setType(depart->getType().left(3));
}

bool ModDepart::champsVide()
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

void Gui::ModDepart::on_btValider_clicked()
{
    if(champsVide())
        return;
    if(typedepartCombo->currentText().left(3)!="DEC"){
        if(datedepartEdit->date().operator <(depart->getDdep())){
            QMessageBox::critical(this,"ERREUR 11810","Date invalide");
            datedepartEdit->setFocus();
            return;
        }
    }
    modDep = new Core::Depart;
    modDep->setCode(depart->getCode());
    modDep->setAgent(depart->getAgent());
    modDep->setType(typedepartCombo->currentText().left(3));
    modDep->setMotif(motifdepartEdit->toPlainText());
    modDep->setDdep(datedepartEdit->date());
    if(modDep->Equal(depart)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        typedepartCombo->setFocus();
        delete modDep;
        return ;
    }
    if(modDep->update()){
        QMessageBox::information(this, tr("Succès"), tr("<B>Depart modifié</B>") ) ;
        this->close();
        model->select();
        delete modDep;
    }
}
