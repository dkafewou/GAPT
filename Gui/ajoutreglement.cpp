#include "ajoutreglement.h"

using namespace Gui;

AjoutReglement::AjoutReglement(QString cont, QString tr, Core::Reglement *regl, QWidget *parent) :
    QDialog(parent),reglement(regl)
{
    setupUi(this);
    contEdit->setText(cont);
    transportEdit->setText(tr);
    initComoposant();

}

void AjoutReglement::initComoposant()
{
    validator = new QDoubleValidator(0,999999999,3,this);
    montantEdit->setValidator( validator );

    datereglementEdit->setDate(QDate::currentDate());
    timeEdit->setTime(QTime::currentTime());
}

bool AjoutReglement::champsVide()
{
    if(datereglementEdit->date().operator <(QDate::currentDate())){
                QMessageBox::critical(this,"ERREUR 11810","Date invalide");
                datereglementEdit->setFocus();
                return true;
            }
    if(montantEdit->text().isEmpty()){
                QMessageBox::critical(this,"ERREUR 11810","Veuillez renseigner le montant");
                montantEdit->setFocus();
                return true;
            }
    return false;
}

void Gui::AjoutReglement::on_btValider_clicked()
{
    if(champsVide())
        return;
    reglement->setDate(datereglementEdit->date());
    reglement->setTime(timeEdit->time());
    reglement->setMontant(montantEdit->text().toDouble());
    reglement->setSuppr(false);
    reglement->setCode(reglement->generate());
    if(reglement->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("Transport déjà payé"));
        return;
    }
    if(reglement->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("Transport payé"));
        this->close();
    }
}
