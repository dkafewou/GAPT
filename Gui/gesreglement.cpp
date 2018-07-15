#include "gesreglement.h"

using namespace Gui;
gesReglement::gesReglement(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
}

void gesReglement::initComposant()
{
    dateEdit->setDate(QDate::currentDate());
    query.prepare("select t.CodeRegl,t.CodeTransp,tr.NomTransporteur,t.DateRegl,t.HeureRegl,t.MontantRegl from reglement t,transport tp,transporteur tr where t.CodeTransp=tp.CodeTransp and tp.CodeTransporteur=tr.CodeTransporteur and t.SupprRegl=0");

    if(query.exec()){
        model = new QSqlQueryModel;
        model->setQuery(query);
        model->setHeaderData(0,Qt::Horizontal,tr("CodeRegl"));
        model->setHeaderData(1,Qt::Horizontal,tr("CodeTransp"));
        model->setHeaderData(2,Qt::Horizontal,tr("Transporteur"));
        model->setHeaderData(3,Qt::Horizontal,tr("Date"));
        model->setHeaderData(4,Qt::Horizontal,tr("Heure"));
        model->setHeaderData(5,Qt::Horizontal,tr("Montant"));

        reglementTableView->setModel(model);
        reglementTableView->hideColumn(0);
        reglementTableView->hideColumn(1);
        reglementTableView->show();
    }
    else{
        qDebug() << "Not updated" << query.lastError();
        return ;
    }
}

void Gui::gesReglement::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cette ligne?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            reglement = new Core::Reglement;
            reglement->setCode(liste.at(0).data().toString());
           if(reglement->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Ligne Supprimée </B>") ) ;
               query.exec();
               model->setQuery(query);
           }
        }
}

void Gui::gesReglement::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à supprimer</B>"));
        return;
    }
    reglement = new Core::Reglement;
    reglement->setCode(liste.at(0).data().toString());
    reglement->setTransport(liste.at(1).data().toString());
    reglement->setDate(liste.at(3).data().toDate());
    reglement->setTime(liste.at(4).data().toTime());
    reglement->setMontant(liste.at(5).data().toDouble());

    FenModRegl = new Gui::ModReglement(query,model,reglement,liste.at(2).data().toString(),this);
    FenModRegl->showNormal();
}

void Gui::gesReglement::on_transportEdit_textChanged(const QString &arg1)
{
    query.prepare("select t.CodeRegl,t.CodeTransp,tr.NomTransporteur,t.DateRegl,t.HeureRegl,t.MontantRegl from reglement t,transport tp,transporteur tr where t.CodeTransp=tp.CodeTransp and tp.CodeTransporteur=tr.CodeTransporteur and t.SupprRegl=0 and tr.NomTransporteur like '"+arg1+"%'");
    if(query.exec()){
        model = new QSqlQueryModel;
        model->setQuery(query);
        model->setHeaderData(0,Qt::Horizontal,tr("CodeRegl"));
        model->setHeaderData(1,Qt::Horizontal,tr("CodeTransp"));
        model->setHeaderData(2,Qt::Horizontal,tr("Transporteur"));
        model->setHeaderData(3,Qt::Horizontal,tr("Date"));
        model->setHeaderData(4,Qt::Horizontal,tr("Heure"));
        model->setHeaderData(5,Qt::Horizontal,tr("Montant"));

        reglementTableView->setModel(model);
        reglementTableView->hideColumn(0);
        reglementTableView->hideColumn(1);
        reglementTableView->show();
    }
    else{
        qDebug() << "Not updated" << query.lastError();
        return ;
    }

}

void Gui::gesReglement::on_dateEdit_dateChanged(const QDate &date)
{
    query.prepare("select t.CodeRegl,t.CodeTransp,tr.NomTransporteur,t.DateRegl,t.HeureRegl,t.MontantRegl from reglement t,transport tp,transporteur tr where t.CodeTransp=tp.CodeTransp and tp.CodeTransporteur=tr.CodeTransporteur and t.SupprRegl=0 and t.DateRegl=? and tr.NomTransporteur like '"+transportEdit->text()+"%'");
    query.bindValue(0,date);
    if(query.exec()){
        model = new QSqlQueryModel;
        model->setQuery(query);
        model->setHeaderData(0,Qt::Horizontal,tr("CodeRegl"));
        model->setHeaderData(1,Qt::Horizontal,tr("CodeTransp"));
        model->setHeaderData(2,Qt::Horizontal,tr("Transporteur"));
        model->setHeaderData(3,Qt::Horizontal,tr("Date"));
        model->setHeaderData(4,Qt::Horizontal,tr("Heure"));
        model->setHeaderData(5,Qt::Horizontal,tr("Montant"));

        reglementTableView->setModel(model);
        reglementTableView->hideColumn(0);
        reglementTableView->hideColumn(1);
        reglementTableView->show();
    }
    else{
        qDebug() << "Not updated" << query.lastError();
        return ;
    }
}

void Gui::gesReglement::on_reglementTableView_clicked()
{
    liste = reglementTableView->selectionModel()->selection().indexes();
}

void Gui::gesReglement::on_btApercu_clicked()
{
    QSqlQuery query;
        query.clear();
        query.prepare("select tr.NomTransporteur,t.DateRegl,t.HeureRegl,t.MontantRegl from reglement t,transport tp,transporteur tr where t.CodeTransp=tp.CodeTransp and tp.CodeTransporteur=tr.CodeTransporteur and t.SupprRegl=0");
        if(query.exec()){
            modelEtat = new QSqlQueryModel;
            modelEtat->setQuery(query);
            model->setHeaderData(0,Qt::Horizontal,tr("Transporteur"));
            model->setHeaderData(1,Qt::Horizontal,tr("Date"));
            model->setHeaderData(2,Qt::Horizontal,tr("Heure"));
            model->setHeaderData(3,Qt::Horizontal,tr("Montant"));
            etat = new Reports::EtatNomination("Liste des transporteurs",modelEtat);
        }
}
