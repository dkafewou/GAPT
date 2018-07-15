#include "gespermission.h"

using namespace Gui;

GesPermission::GesPermission(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void GesPermission::initComposant()
{
    model = new QSqlRelationalTableModel(this);
    model->setTable("permission");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Agent"));
    model->setHeaderData(2,Qt::Horizontal,tr("Type"));
    model->setHeaderData(3,Qt::Horizontal,tr("Motif"));
    model->setHeaderData(4,Qt::Horizontal,tr("Debut"));
    model->setHeaderData(5,Qt::Horizontal,tr("Fin"));
    model->setHeaderData(6,Qt::Horizontal,tr("Retour"));
    model->setHeaderData(7,Qt::Horizontal,tr("Suppr"));
    model->setRelation(1, QSqlRelation("agent", "IdAgent", "NomAgent"));
    model->setRelation(2, QSqlRelation("typepermission", "CodeTypepermission", "LibellePermission"));
    model->setFilter("SupprPermission=0");
    model->select();

    permissionTableView->setModel(model);
    permissionTableView->hideColumn(0);
    permissionTableView->hideColumn(7);
    permissionTableView->show();
}

void Gui::GesPermission::on_btTypePermission_clicked()
{
    FenTypePer = new Gui::GesTypePerm(this);
    FenTypePer->showNormal();
}

void Gui::GesPermission::on_btNouveau_clicked()
{
    FenPermission = new Gui::ajoutPermission(model,this);
    FenPermission->showNormal();
}

void Gui::GesPermission::on_permissionTableView_clicked()
{
    liste = permissionTableView->selectionModel()->selection().indexes();
}

void Gui::GesPermission::on_btValider_2_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    permission = new Core::Permission;
    permission->setCode(liste.at(0).data().toString());
    permission->setAgent(liste.at(1).data().toString());
    permission->setType(liste.at(2).data().toString());
    permission->setMotif(liste.at(3).data().toString());
    permission->setDebut(liste.at(4).data().toDate());
    permission->setFin(liste.at(5).data().toDate());
    permission->setRetour(liste.at(6).data().toDate());
    permission->setSuppr(liste.at(7).data().toBool());

    FenMod = new Gui::ModPermission(model,permission,this);
    FenMod->showNormal();
}

void Gui::GesPermission::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            permission = new Core::Permission;
            permission->setCode(liste.at(0).data().toString());
           if(permission->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
               delete permission;
           }
        }
}

void Gui::GesPermission::on_agentEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprPermission=0 and NomAgent like '"+arg1+"%' and LibellePermission like '"+permissionEdit->text()+"%'");
    liste.clear();
}

void Gui::GesPermission::on_permissionEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprPermission=0 and NomAgent like '"+agentEdit->text()+"%' and LibellePermission like '"+arg1+"%'");
    liste.clear();
}

void Gui::GesPermission::on_btAper_clicked()
{
    QSqlQuery query;
    query.clear();
    query.prepare("select a.NomAgent,a.PrenomAgent,t.LibellePermission,c.motifPermission,c.Datedebut,c.dateFin,c.DateRetourEffect from agent a,typePermission t,Permission c where a.IdAgent=c.IdAgent and c.CodeTypepermission=t.CodeTypepermission and a.NomAgent like'"+agentEdit->text()+"%' and t.LibellePermission like'"+permissionEdit->text()+"%' and c.SupprPermission=0");
    if(query.exec()){
        modelEtat = new QSqlQueryModel;
        modelEtat->setQuery(query);
        modelEtat->setHeaderData(0,Qt::Horizontal,tr("Nom"));
        modelEtat->setHeaderData(1,Qt::Horizontal,tr("Prénom"));
        modelEtat->setHeaderData(2,Qt::Horizontal,tr("Type Permission"));
        modelEtat->setHeaderData(3,Qt::Horizontal,tr("Motif"));
        modelEtat->setHeaderData(4,Qt::Horizontal,tr("Debut"));
        modelEtat->setHeaderData(5,Qt::Horizontal,tr("Fin"));
        modelEtat->setHeaderData(6,Qt::Horizontal,tr("Retour"));

        prevision = new Reports::EtatNomination("Liste des Permissions",modelEtat);
    }
}
