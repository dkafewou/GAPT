#include "modtransp.h"

using namespace Gui;

ModTransp::ModTransp(QSqlRelationalTableModel *mod, Core::transport *tr, QWidget *parent) :
    QDialog(parent),model(mod),transport(tr)
{
    setupUi(this);
    initcomposant();
}

void ModTransp::initcomposant()
{
    conteneurEdit->setText(transport->getConteneur());
    transporteurEdit->setText(transport->getTransporteur());
    datetransportEdit->setDate(transport->getDatetransp());
    dateretourEdit->setDate(transport->getDateretour());
}

bool ModTransp::champsVide()
{
    if(conteneurEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le numero de conteneur");
                this->close();
                return true;
            }
    if(transporteurEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir le transporteur");
                this->close();
                return true;
            }
    if(datetransportEdit->date().operator >(QDate::currentDate())){
                QMessageBox::critical(this,"ERREUR 11810","La date doit être antérieure à la date d'aujourd'hui");
                datetransportEdit->setFocus();
                return true;
            }
    if(dateretourEdit->date().operator <(datetransportEdit->date())){
                QMessageBox::critical(this,"ERREUR 11810","La date retour doit être postérieur à la date de sortie");
                dateretourEdit->setFocus();
                return true;
            }
    return false;
}

void Gui::ModTransp::on_btValider_clicked()
{
    if(champsVide())
        return;
    modTrans = new Core::transport;
    modTrans->setCode(transport->getCode());
    modTrans->setDatetransp(datetransportEdit->date());
    modTrans->setDateretour(dateretourEdit->date());
    modTrans->setConteneur(transport->getConteneur());
    modTrans->setTransporteur(transport->getTransporteur());
    if(modTrans->Equal(transport)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        datetransportEdit->setFocus();
        delete modTrans;
    }
    if(modTrans->update()){
        QMessageBox::information(this, tr("Succès"), tr("<B>Transport modifié</B>") ) ;
        delete modTrans;
        delete transport;
        model->select();
        this->close();
    }

}
