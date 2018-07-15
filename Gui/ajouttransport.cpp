#include "ajouttransport.h"

using namespace Gui;

AjoutTransport::AjoutTransport(Core::Conteneur *cont, QWidget *parent) :
    QDialog(parent),conteneur(cont)
{
    setupUi(this);
    initComposant();
}

void AjoutTransport::initComposant()
{
    conteneurEdit->setText(conteneur->getNumero());

    datetransportEdit->setDate(QDate::currentDate());
    dateretourEdit->setDate(QDate::currentDate().addDays(2));
    transporteur = new Core::transporteur;
}

bool AjoutTransport::champsVide()
{
    if(conteneurEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le numero de conteneur");
                this->close();
                return true;
            }
    if(transporteurEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir le transporteur");
                btTr->setFocus();
                return true;
            }
    if(datetransportEdit->date().operator <(QDate::currentDate())){
                QMessageBox::critical(this,"ERREUR 11810","La date doit être postérieur à la date d'aujourd'hui");
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

void Gui::AjoutTransport::on_datetransportEdit_dateChanged(const QDate &date)
{
    dateretourEdit->setDate(date.addDays(2));
}

void Gui::AjoutTransport::on_btValider_clicked()
{
    if(champsVide())
        return;
    transp = new Core::transport;
    transp->setConteneur(conteneur->getCode());
    transp->setTransporteur(transporteur->getCode());
    transp->setDatetransp(datetransportEdit->date());
    transp->setDateretour(dateretourEdit->date());
    transp->setSuppr(false);
    transp->setCode(transp->generate());
    if(transp->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Conteneur déjà transporté"));
        delete transp;
        return;
    }
    if(transp->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Transport enregistré"));
        delete conteneur;
        delete transporteur;
        delete transp;
        this->close();
    }
}

void Gui::AjoutTransport::on_btTr_clicked()
{
    FenListe = new Gui::ListeTransporteur(transporteurEdit,transporteur,this);
    FenListe->showNormal();
}
