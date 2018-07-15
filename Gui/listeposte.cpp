#include "listeposte.h"

using namespace Gui;

ListePoste::ListePoste(QLineEdit *edi, Core::travail *taf, QWidget *parent) :
    QDialog(parent),edit(edi),travail(taf)
{
    setupUi(this);
    initComposant();
}

void ListePoste::initComposant()
{
    modelFonction = new QSqlTableModel;
    modelFonction->setTable("fonction");
    modelFonction->setHeaderData(0,Qt::Horizontal,tr("Code"));
    modelFonction->setHeaderData(1,Qt::Horizontal,tr("Libellé"));
    modelFonction->setHeaderData(2,Qt::Horizontal,tr("supr"));
    modelFonction->setFilter("SupprFonction=0");
    modelFonction->select();

    fonctionTableView->setModel(modelFonction);
    fonctionTableView->hideColumn(2);
    fonctionTableView->show();
}

void Gui::ListePoste::on_posteEdit_textChanged(const QString &arg1)
{
    modelFonction->setFilter("SupprFonction=0 and LibelleFonction like '"+arg1+"%' ");
    liste.clear();
}

void Gui::ListePoste::on_btOk_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir le Poste");
        return;
    }
    edit->setText(liste.at(1).data().toString());
    travail->setFonction(liste.at(0).data().toString());
    this->close();
}

void Gui::ListePoste::on_fonctionTableView_clicked()
{
    liste = fonctionTableView->selectionModel()->selection().indexes();
}
