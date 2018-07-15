#include "listeagent.h"

using namespace Gui;

ListeAgent::ListeAgent(Core::Agent *agen, QLineEdit *edi, QWidget *parent) :
    QDialog(parent),agent(agen),edit(edi)
{
    setupUi(this);
    initComposant();
}

void ListeAgent::initComposant()
{
    model = new QSqlTableModel(this);
    model->setTable("agent");
    model->setHeaderData(0,Qt::Horizontal,tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,tr("Categorie"));
    model->setHeaderData(2,Qt::Horizontal,tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal,tr("Prénom"));
    model->setHeaderData(4,Qt::Horizontal,tr("Sexe"));
    model->setHeaderData(5,Qt::Horizontal,tr("Date Naissance"));
    model->setHeaderData(6,Qt::Horizontal,tr("Nationalité"));
    model->setHeaderData(7,Qt::Horizontal,tr("Situation"));
    model->setHeaderData(8,Qt::Horizontal,tr("Diplôme"));
    model->setHeaderData(9,Qt::Horizontal,tr("Niveau"));
    model->setHeaderData(10,Qt::Horizontal,tr("Telephone"));
    model->setHeaderData(11,Qt::Horizontal,tr("Adresse"));
    model->setHeaderData(12,Qt::Horizontal,tr("Ambauché le"));
    model->setHeaderData(13,Qt::Horizontal,tr("Suppr"));
    model->setFilter("SupprAgent=0");
    model->select();

    agentTableView->setModel(model);
    agentTableView->hideColumn(1);
    agentTableView->hideColumn(5);
    agentTableView->hideColumn(7);
    agentTableView->hideColumn(8);
    agentTableView->hideColumn(9);
    agentTableView->hideColumn(11);
    agentTableView->hideColumn(12);
    agentTableView->hideColumn(13);
    agentTableView->show();
}

void Gui::ListeAgent::on_matrEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprAgent=0 and IdAgent like '"+arg1+"%' and NomAgent like '"+nomEdit->text()+"%'");
    liste.clear();
}

void Gui::ListeAgent::on_nomEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprAgent=0 and IdAgent like '"+matrEdit->text()+"%' and NomAgent like '"+arg1+"%'");
    liste.clear();
}

void Gui::ListeAgent::on_btOk_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir l'Agent");
        return;
    }
    edit->setText(liste.at(2).data().toString()+" "+liste.at(3).data().toString());
    agent->setIdAgent(liste.at(0).data().toString());
    agent->setNomAgent(liste.at(2).data().toString());
    agent->setSexe(liste.at(4).data().toString());
    agent->setDateAmb(liste.at(12).data().toDate());
    this->close();
}

void Gui::ListeAgent::on_agentTableView_clicked()
{
    liste = agentTableView->selectionModel()->selection().indexes();
}
