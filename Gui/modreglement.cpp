#include "modreglement.h"

using namespace Gui;

ModReglement::ModReglement(QSqlQuery &q, QSqlQueryModel *mo, Core::Reglement *regl, QString tra, QWidget *parent) :
    QDialog(parent),query(q),model(mo),reglement(regl)
{
    setupUi(this);
    transportEdit->setText(tra);
    initComposant();
}

void ModReglement::initComposant()
{
    if(reglement->getDate().operator <(QDate::currentDate().addDays(-1)))
                montantEdit->setReadOnly(true);
    validator = new QDoubleValidator(0,99999999,3,this);
    montantEdit->setValidator( validator );

    datereglementEdit->setDate(reglement->getDate());
    timeEdit->setTime(reglement->getTime());
    montantEdit->setText(QString::number(reglement->getMontant()));
}

bool ModReglement::champsVide()
{
    if(datereglementEdit->date().operator >(QDate::currentDate())||datereglementEdit->date().operator <(reglement->getDate())){
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

void Gui::ModReglement::on_btValider_clicked()
{
    if(champsVide())
        return;
    modReg = new Core::Reglement;
    modReg->setCode(reglement->getCode());
    modReg->setDate(datereglementEdit->date());
    modReg->setTime(timeEdit->time());
    modReg->setMontant(montantEdit->text().toDouble());
    if(modReg->Equal(reglement)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        delete modReg;
        return;
    }
    if(modReg->update()){
        QMessageBox::information(this, tr("Succès"), tr("<B>Reglement modifié</B>") ) ;
        delete modReg;
        delete reglement;
        query.exec();
        model->setQuery(query);
        this->close();
    }
}
