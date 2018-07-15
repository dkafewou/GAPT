#include "gessanction.h"

using namespace Gui;

GesSanction::GesSanction(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void GesSanction::initComposant()
{
    model = new QSqlRelationalTableModel(this);
    model->setTable("sanction");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Agent"));
    model->setHeaderData(2,Qt::Horizontal,tr("Motif"));
    model->setHeaderData(3,Qt::Horizontal,tr("Date"));
    model->setHeaderData(4,Qt::Horizontal,tr("Suppr"));
    model->setRelation(1, QSqlRelation("Agent", "IdAgent", "NomAgent"));
    model->setFilter("SupprSanction=0");
    model->select();

    sanctionTableView->setModel(model);
    sanctionTableView->hideColumn(0);
    sanctionTableView->hideColumn(4);
    sanctionTableView->show();
}

void Gui::GesSanction::on_btNouveau_clicked()
{
    FenSanction = new Gui::AjoutSanction(model,this);
    FenSanction->showNormal();
}

void Gui::GesSanction::on_agentEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprSanction=0 and NomAgent like '"+arg1+"%' ");
    liste.clear();
}

void Gui::GesSanction::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            Sanction = new Core::sanction();
            Sanction->setCode(liste.at(0).data().toString());
           if(Sanction->remove()){
               QMessageBox::information(this, tr("Succés"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
           }
        }
}

void Gui::GesSanction::on_sanctionTableView_clicked()
{
    liste = sanctionTableView->selectionModel()->selection().indexes();
}

void Gui::GesSanction::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    Sanction = new Core::sanction();
    Sanction->setCode(liste.at(0).data().toString());
    Sanction->setAgent(liste.at(1).data().toString());
    Sanction->setMotif(liste.at(2).data().toString());
    Sanction->setDate(liste.at(3).data().toDate());
    Sanction->setSuppr(liste.at(4).data().toBool());

    FenModif = new Gui::ModifierSanction(Sanction,model,this);
    FenModif->showNormal();
}
