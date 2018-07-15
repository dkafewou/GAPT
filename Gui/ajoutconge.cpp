#include "ajoutconge.h"

using namespace Gui;

AjoutConge::AjoutConge(QSqlRelationalTableModel *mod, QWidget *parent) :
    QDialog(parent),model(mod)
{
    setupUi(this);
    initComposant();
    initCombo();
}

void Gui::AjoutConge::initComposant()
{
    typP = new Core::TypeConge;
    agent = new Core::Agent;
    datedebutEdit->setDate(QDate::currentDate());
    datefinEdit->setDate(QDate::currentDate());
    dateretoureffectifEdit->setDate(QDate::currentDate());
}

bool Gui::AjoutConge::champsVide()
{
    if(agentEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir l'agent");
        btAgent->setFocus();
        return true;
    }
    return false;
}

void Gui::AjoutConge::initCombo()
{
    mode = new QSqlTableModel;
    mode->setTable("typeConge");
    mode->setHeaderData(0,Qt::Horizontal,tr("Code"));
    mode->setHeaderData(1,Qt::Horizontal,tr("Libellé"));
    mode->setHeaderData(2,Qt::Horizontal,tr("nbrejour"));
    mode->setHeaderData(3,Qt::Horizontal,tr("supr"));
    mode->setFilter("SupprTypeConge=0");
    mode->select();

    typecongeCombo->setModel(mode);
    typecongeCombo->setModelColumn(1);
    typecongeCombo->show();
}

void Gui::AjoutConge::on_typecongeCombo_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    query.clear();
    query.prepare("select * from typeconge where LibelleConge='"+arg1+"'");
    if(query.exec()){
        if(query.first()){
         typP->setCode(query.value(0).toString());
         typP->setLibelle(query.value(1).toString());
         typP->setNbrjrs(query.value(2).toInt());
         datefinEdit->setDate(datedebutEdit->date().addDays(typP->getNbrjrs()));
         dateretoureffectifEdit->setDate(datedebutEdit->date().addDays(typP->getNbrjrs()));
        }
    }
}

void Gui::AjoutConge::on_datedebutEdit_dateChanged(const QDate &date)
{
    QSqlQuery query;
    query.clear();
    query.prepare("select * from typeconge where LibelleConge='"+typecongeCombo->currentText()+"'");
    if(query.exec()){
        if(query.first()){
         typP->setCode(query.value(0).toString());
         typP->setLibelle(query.value(1).toString());
         typP->setNbrjrs(query.value(2).toInt());
         datefinEdit->setDate(date.addDays(typP->getNbrjrs()));
         dateretoureffectifEdit->setDate(date.addDays(typP->getNbrjrs()));
        }
    }
}

void Gui::AjoutConge::on_btValider_clicked()
{
    if(champsVide())
        return;
    conge = new Core::Conge;
    conge->setAgent(agent->getIdAgent());
    conge->setType(typP->getCode());
    conge->setMotif(motifEdit->toPlainText());
    conge->setDebut(datedebutEdit->date());
    conge->setFin(datefinEdit->date());
    conge->setRetour(dateretoureffectifEdit->date());
    conge->setSuppr(false);
    conge->setCode(conge->generate());
    if(conge->Existe()){
        QMessageBox::critical(this,tr("Doublon"),tr("conge déjà enregistré."));
        delete conge;
        return;
    }
    if(typecongeCombo->currentText()=="Normal"){
        QSqlQuery query;
        query.clear();
        query.prepare("select * from conge where IdAgent='"+conge->getAgent()+"'");
        if(query.exec()){
            if(query.last()){
                verif = new Core::Conge;
                verif->setCode(query.value(0).toString());
                verif->setDebut(query.value(4).toDate());
                verif->setFin(query.value(5).toDate());
                verif->setRetour(query.value(6).toDate());
                if(verif->getRetour().addYears(1).operator >(conge->getDebut())){
                    QMessageBox::critical(this,tr("Doublon"),tr("Vérifier la date de debut de conge.\n Il faut un an de service pour pouvoir prendre un congé normal"));
                    datedebutEdit->setFocus();
                    return;
                }
            }
            else if (agent->getDateAmb().addYears(1).operator >(conge->getDebut())) {
                QMessageBox::critical(this,tr("Doublon"),tr("Vérifier la date de debut de conge.\n Il faut un an de service pour pouvoir prendre un congé normal"));
                datedebutEdit->setFocus();
                return;
            }
        }
    }
    if(typecongeCombo->currentText()=="Matèrnité"&&agent->getSexe()=="Masculin"){
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible d'octroyer un congé de matèrnité à un homme"));
        typecongeCombo->setFocus();
        return;
    }
    if(typecongeCombo->currentText()=="Patèrnité"&&agent->getSexe()=="Feminin"){
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible d'octroyer un congé de patèrnité à une femme"));
        typecongeCombo->setFocus();
        return;
    }
    if(conge->save()){
        QMessageBox::information(this,tr("SUCCES"),tr("conge enregistré."));
        delete conge;
        model->select();
        agentEdit->clear();
        motifEdit->clear();
    }
}

void Gui::AjoutConge::on_btAgent_clicked()
{
    FenListe = new Gui::ListeAgent(agent,agentEdit,this);
    FenListe->showNormal();
}
