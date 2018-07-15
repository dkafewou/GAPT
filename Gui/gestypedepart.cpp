#include "gestypedepart.h"

using namespace Gui;

GesTypeDepart::GesTypeDepart(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void GesTypeDepart::initComposant()
{
    model = new QSqlTableModel;
    model->setTable("typedepart");
    model->setHeaderData(0,Qt::Horizontal,tr("Code"));
    model->setHeaderData(1,Qt::Horizontal,tr("Libellé"));
    model->setHeaderData(2,Qt::Horizontal,tr("supr"));
    model->setFilter("SupprTypeDepart=0");
    model->select();

    typedepartTableView->setModel(model);
    typedepartTableView->hideColumn(2);
    typedepartTableView->show();
}

void Gui::GesTypeDepart::on_btNouveau_clicked()
{
    FenTypeDep = new Gui::AjoutTypeDep(model,this);
    FenTypeDep->show();
}

void Gui::GesTypeDepart::on_libelleEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprTypeDepart=0 and LibelleDepart like '"+arg1+"%' ");
    liste.clear();
}

void Gui::GesTypeDepart::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    typedep = new Core::TypeDepart;
    typedep->setCode(liste.at(0).data().toString());
    typedep->setLibelle(liste.at(1).data().toString());
    FenModType = new Gui::ModTypeDepart(typedep,model,this);
    FenModType->show();
}

void Gui::GesTypeDepart::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            typedep = new Core::TypeDepart;
            typedep->setCode(liste.at(0).data().toString());
           if(typedep->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               model->select();
               delete typedep;
           }
        }
}

void Gui::GesTypeDepart::on_typedepartTableView_clicked()
{
    liste = typedepartTableView->selectionModel()->selection().indexes();
}
