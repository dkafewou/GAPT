#include "gesformation.h"

using namespace Gui;

GesFormation::GesFormation(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void GesFormation::initComposant()
{
    model = new QSqlTableModel(this);
    model->setTable("formation");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Libelle"));
    model->setHeaderData(2,Qt::Horizontal,tr("Ville"));
    model->setHeaderData(3,Qt::Horizontal,tr("Pays"));
    model->setHeaderData(4,Qt::Horizontal,tr("Date Debut"));
    model->setHeaderData(5,Qt::Horizontal,tr("Date Fin"));
    model->setHeaderData(6,Qt::Horizontal,tr("Fin Effective"));
    model->setHeaderData(7,Qt::Horizontal,tr("Suppr"));
    model->setFilter("SupprFormation=0");
    model->select();

    FormationTableView->setModel(model);
    FormationTableView->hideColumn(7);
    FormationTableView->hideColumn(0);
    FormationTableView->show();
}

void Gui::GesFormation::on_btNouveau_clicked()
{
    FenAjoutForm = new Gui::AjoutFormation(model,this);
    FenAjoutForm->showMaximized();
}

void Gui::GesFormation::on_formationEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprFormation=0 and LibelleFormation like '"+arg1+"%' and Ville like '"+villeEdit->text()+"%' ");
}

void Gui::GesFormation::on_btInit_clicked()
{
    initComposant();
}

void Gui::GesFormation::on_villeEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprFormation=0 and LibelleFormation like '"+formationEdit->text()+"%' and Ville like '"+arg1+"%' ");
}

void Gui::GesFormation::on_FormationTableView_clicked()
{
    liste = FormationTableView->selectionModel()->selection().indexes();
}

void Gui::GesFormation::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            formation = new Core::Formation;
            formation->setCode(liste.at(0).data().toString());
           if(formation->remove()){
               QMessageBox::information(this, tr("Succés"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
               delete formation;
           }
        }
}

void Gui::GesFormation::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    formation = new Core::Formation;
    formation->setCode(liste.at(0).data().toString());
    formation->setLibelle(liste.at(1).data().toString());
    formation->setVille(liste.at(2).data().toString());
    formation->setPays(liste.at(3).data().toString());
    formation->setDebut(liste.at(4).data().toDate());
    formation->setFin(liste.at(5).data().toDate());
    formation->setReel(liste.at(6).data().toDate());

    FenMomForm = new Gui::ModifierFormation(formation,model,this);
    FenMomForm->showMaximized();
}
