#include "gesconge.h"

using namespace Gui;

GesConge::GesConge(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void GesConge::initComposant()
{
    model = new QSqlRelationalTableModel(this);
    model->setTable("conge");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Agent"));
    model->setHeaderData(2,Qt::Horizontal,tr("Type"));
    model->setHeaderData(3,Qt::Horizontal,tr("Motif"));
    model->setHeaderData(4,Qt::Horizontal,tr("Debut"));
    model->setHeaderData(5,Qt::Horizontal,tr("Fin"));
    model->setHeaderData(6,Qt::Horizontal,tr("Retour"));
    model->setHeaderData(7,Qt::Horizontal,tr("Suppr"));
    model->setRelation(1, QSqlRelation("agent", "IdAgent", "NomAgent"));
    model->setRelation(2, QSqlRelation("typeconge", "CodeTypeConge", "LibelleConge"));
    model->setFilter("SupprConge=0");
    model->select();

    congeTableView->setModel(model);
    congeTableView->hideColumn(0);
    congeTableView->hideColumn(7);
    congeTableView->show();
}

void Gui::GesConge::on_btType_clicked()
{
    FenGesTyp = new Gui::GesTypCong(this);
    FenGesTyp->showNormal();
}

void Gui::GesConge::on_btNouveau_clicked()
{
    FenAjoutConge = new Gui::AjoutConge(model,this);
    FenAjoutConge->showNormal();
}

void Gui::GesConge::on_btModifer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    conge = new Core::Conge;
    conge->setCode(liste.at(0).data().toString());
    conge->setAgent(liste.at(1).data().toString());
    conge->setType(liste.at(2).data().toString());
    conge->setMotif(liste.at(3).data().toString());
    conge->setDebut(liste.at(4).data().toDate());
    conge->setFin(liste.at(5).data().toDate());
    conge->setRetour(liste.at(6).data().toDate());

    FenModConge = new Gui::ModConge(model,conge,this);
    FenModConge->showNormal();
}

void Gui::GesConge::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            conge = new Core::Conge;
            conge->setCode(liste.at(0).data().toString());
           if(conge->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
               delete conge;
           }
        }
}

void Gui::GesConge::on_congeTableView_clicked()
{
    liste = congeTableView->selectionModel()->selection().indexes();
}

void Gui::GesConge::on_agentEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprConge=0 and NomAgent like '"+arg1+"%' and LibelleConge like '"+typeEdit->text()+"%'");
    liste.clear();
}

void Gui::GesConge::on_typeEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprConge=0 and NomAgent like '"+agentEdit->text()+"%' and LibelleConge like '"+arg1+"%'");
    liste.clear();
}

void Gui::GesConge::on_btPre_clicked()
{
    QSqlQuery query;
    query.clear();
    query.prepare("select a.NomAgent,a.PrenomAgent,t.LibelleConge,c.motifConge,c.Datedebut,c.dateFin,c.DateRetourEffect from agent a,typeConge t,conge c where a.IdAgent=c.IdAgent and c.CodeTypeConge=t.CodeTypeConge and a.NomAgent like'"+agentEdit->text()+"%' and t.LibelleConge like'"+typeEdit->text()+"%' and c.SupprConge=0");
    if(query.exec()){
        modelEtat = new QSqlQueryModel;
        modelEtat->setQuery(query);
        modelEtat->setHeaderData(0,Qt::Horizontal,tr("Nom"));
        modelEtat->setHeaderData(1,Qt::Horizontal,tr("Prénom"));
        modelEtat->setHeaderData(2,Qt::Horizontal,tr("Type Congé"));
        modelEtat->setHeaderData(3,Qt::Horizontal,tr("Motif"));
        modelEtat->setHeaderData(4,Qt::Horizontal,tr("Debut"));
        modelEtat->setHeaderData(5,Qt::Horizontal,tr("Fin"));
        modelEtat->setHeaderData(6,Qt::Horizontal,tr("Retour"));

        prevision = new Reports::EtatNomination("Liste des congés",modelEtat);
    }
}
