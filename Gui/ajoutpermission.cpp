#include "ajoutpermission.h"

using namespace Gui;

ajoutPermission::ajoutPermission(QSqlRelationalTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
    initComposant();
    initCombo();
}

void Gui::ajoutPermission::initCombo()
{
    mode = new QSqlTableModel;
    mode->setTable("typepermission");
    mode->setHeaderData(0,Qt::Horizontal,tr("Code"));
    mode->setHeaderData(1,Qt::Horizontal,tr("Libellé"));
    mode->setHeaderData(2,Qt::Horizontal,tr("nbrejour"));
    mode->setHeaderData(3,Qt::Horizontal,tr("supr"));
    mode->setFilter("SupprTypePermission=0");
    mode->select();

    typepermissionCombo->setModel(mode);
    typepermissionCombo->setModelColumn(1);
    typepermissionCombo->show();
}

void Gui::ajoutPermission::initComposant()
{
    typP = new Core::TypePermission;
    agent = new Core::Agent;
    datedebutEdit->setDate(QDate::currentDate());
    datefinEdit->setDate(QDate::currentDate());
    dateretoureffectifEdit->setDate(QDate::currentDate());
}

bool Gui::ajoutPermission::champsVide()
{
    if(agentEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir l'agent");
        btAgent->setFocus();
        return true;
    }
    return false;
}

void Gui::ajoutPermission::on_typepermissionCombo_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    query.clear();
    query.prepare("select * from typepermission where LibellePermission='"+arg1+"'");
    if(query.exec()){
        if(query.first()){
         typP->setCode(query.value(0).toString());
         typP->setLibelle(query.value(1).toString());
         typP->setNbrJours(query.value(2).toInt());
         datefinEdit->setDate(datedebutEdit->date().addDays(typP->getNbrJours()));
         dateretoureffectifEdit->setDate(datedebutEdit->date().addDays(typP->getNbrJours()));
        }
    }
}

void Gui::ajoutPermission::on_datedebutEdit_dateChanged(const QDate &date)
{
    QSqlQuery query;
    query.clear();
    query.prepare("select * from typepermission where LibellePermission='"+typepermissionCombo->currentText()+"'");
    if(query.exec()){
        if(query.first()){
         typP->setCode(query.value(0).toString());
         typP->setLibelle(query.value(1).toString());
         typP->setNbrJours(query.value(2).toInt());
         datefinEdit->setDate(date.addDays(typP->getNbrJours()));
         dateretoureffectifEdit->setDate(date.addDays(typP->getNbrJours()));
        }
    }
}

void Gui::ajoutPermission::on_btAgent_clicked()
{
    FenListe = new Gui::ListeAgent(agent,agentEdit,this);
    FenListe->showNormal();
}

void Gui::ajoutPermission::on_btValider_clicked()
{
    if(champsVide())
        return;
    permission = new Core::Permission;
    permission->setAgent(agent->getIdAgent());
    permission->setType(typP->getCode());
    permission->setMotif(motiftEdit->toPlainText());
    permission->setDebut(datedebutEdit->date());
    permission->setFin(datefinEdit->date());
    permission->setRetour(dateretoureffectifEdit->date());
    permission->setSuppr(false);
    permission->setCode(permission->generate());
    if(permission->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Permission déjà enregistrée."));
        delete permission;
        return;
    }
    if(permission->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Permission enregistrée"));
        delete permission;
        model->select();
        agentEdit->clear();
        motiftEdit->clear();
    }
}
