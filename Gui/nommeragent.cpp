#include "nommeragent.h"

using namespace Gui;

NommerAgent::NommerAgent(Core::Agent *ag, QWidget *parent) :
    QDialog(parent),agent(ag)
{
    setupUi(this);
    initComposant();
}

void NommerAgent::initComposant()
{
    debutDateEdit->setDate(QDate::currentDate());
    agentEdit->setText(agent->getNomAgent()+" "+agent->getPrenomAgent());

    model = new QSqlTableModel;
    model->setTable("direction");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Libellé"));
    model->setHeaderData(2,Qt::Horizontal,tr("Prime Directeur"));
    model->setHeaderData(3,Qt::Horizontal,tr("supr"));
    model->setFilter("SupprDirection=0");
    model->select();

    comboDirection->setModel(model);
    comboDirection->setModelColumn(1);
    comboDirection->show();
}

bool NommerAgent::champsVide()
{
    if(debutDateEdit->date() < QDate::currentDate()){
        QMessageBox::critical(this,"ERREUR 102340","Date debut de service incorrecte\n Ne doit pas être anterieure à celle d'aujourd'huit");
        debutDateEdit->setFocus();
        return true;
    }
    return false;
}

void Gui::NommerAgent::on_btValider_clicked()
{
    if(champsVide())
        return;
    diriger = new Core::Dirige;
    diriger->setAgent(agent->getIdAgent());
    diriger->setDebut(debutDateEdit->date());
    diriger->setSuppr(false);
    QSqlQuery query;
    query.clear();
    query.prepare("select CodeDirection from direction where LibelleDirection='"+comboDirection->currentText()+"'");
    if(query.exec()){
        if(query.first())
            diriger->setDirection(query.value(0).toString());
    }
    if(diriger->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Nomination déjà  enrégistrée"));
        comboDirection->setFocus();
        return;
    }
    query.clear();
    query.prepare("SELECT * FROM dirige  where CodeDirection='"+diriger->getDirection()+"' and Date_FinD is null");
    if(query.exec()){
        if(query.first()){
            fdiriger = new Core::Dirige;
            fdiriger->setAgent(query.value(0).toString());
            fdiriger->setDirection(query.value(1).toString());
            fdiriger->setDebut(query.value(2).toDate());
            fdiriger->setFin(debutDateEdit->date());
            fdiriger->update();
            delete fdiriger;
        }
    }
    if(diriger->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Nomination enregistrée"));
        this->close();
        delete diriger;
        delete agent;
    }
}
