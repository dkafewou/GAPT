#include "gesdepart.h"

using namespace Gui;

GesDepart::GesDepart(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void GesDepart::initComposant()
{
    model = new QSqlRelationalTableModel(this);
    model->setTable("depart");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Type"));
    model->setHeaderData(2,Qt::Horizontal,tr("Agent"));
    model->setHeaderData(3,Qt::Horizontal,tr("Cause"));
    model->setHeaderData(4,Qt::Horizontal,tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,tr("suppr"));
    model->setRelation(1, QSqlRelation("typedepart", "CodeTypeDepart", "LibelleDepart"));
    model->setRelation(2, QSqlRelation("Agent", "IdAgent", "NomAgent"));
    model->setFilter("SupprDepart=0");
    model->select();

    departTableView->setModel(model);
    departTableView->hideColumn(0);
    departTableView->hideColumn(5);
    departTableView->show();
}

void Gui::GesDepart::on_btType_clicked()
{
    FenTypeDep = new Gui::GesTypeDepart(this);
    FenTypeDep->showNormal();
}

void Gui::GesDepart::on_btNouveau_clicked()
{
    FenAjoutDepart = new Gui::AjoutDepart(model,this);
    FenAjoutDepart->showNormal();
}

void Gui::GesDepart::on_AgentEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprDepart=0 and NomAgent like '"+arg1+"%' and LibelleDepart like '"+typeEdit->text()+"%' ");
    liste.clear();
}

void Gui::GesDepart::on_typeEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprDepart=0 and NomAgent like '"+AgentEdit->text()+"%' and LibelleDepart like '"+arg1+"%'");
    liste.clear();
}

void Gui::GesDepart::on_departTableView_clicked()
{
    liste = departTableView->selectionModel()->selection().indexes();
}

void Gui::GesDepart::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    depart = new Core::Depart;
    depart->setCode(liste.at(0).data().toString());
    depart->setType(liste.at(1).data().toString());
    depart->setAgent(liste.at(2).data().toString());
    depart->setMotif(liste.at(3).data().toString());
    depart->setDdep(liste.at(4).data().toDate());

    FenModDep = new Gui::ModDepart(depart,model,this);
    FenModDep->showNormal();
}

void Gui::GesDepart::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            depart = new Core::Depart;
            depart->setCode(liste.at(0).data().toString());
           if(depart->remove()){
               QMessageBox::information(this, tr("SuccÃ¨s"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
               query = new QSqlQuery;
               if(query->exec("select IdAgent from depart where CodeDepart='"+depart->getCode()+"' ")){
                   query->first();
                   agent = new Core::Agent;
                   agent->setIdAgent(query->value(0).toString());
                   agent->restore();
                   delete agent;
                   delete depart;
                   delete query;
               }

           }
        }
}
