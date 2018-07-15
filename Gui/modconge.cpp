#include "modconge.h"

using namespace Gui;

ModConge::ModConge(QSqlRelationalTableModel *mod, Core::Conge *Cng, QWidget *parent) :
    QDialog(parent),model(mod),modCong(Cng)
{
    setupUi(this);
    typP = new Core::TypeConge;
    initCombo();
    initComposant();
}

void ModConge::initComposant()
{
    agent = new Core::Agent;

    QSqlQuery query;
    query.clear();
    query.prepare("select * from typeconge where LibelleConge='"+modCong->getType()+"'");
    if(query.exec()){
        if(query.first()){
         typP->setCode(query.value(0).toString());
         typP->setLibelle(query.value(1).toString());
         typP->setNbrjrs(query.value(2).toInt());
        }
    }

    agentEdit->setText(modCong->getAgent());
    motifEdit->setPlainText(modCong->getMotif());
    typecongeCombo->setCurrentIndex(typecongeCombo->findText(modCong->getType()));
    datedebutEdit->setDate(modCong->getDebut());
    datefinEdit->setDate(modCong->getFin());
    dateretoureffectifEdit->setDate(modCong->getRetour());
    modCong->setType(typP->getCode());

    QSqlQuery qu;
    if(qu.exec("select IdAgent from conge Where CodeConge='"+modCong->getCode()+"'")){
        qu.first();
        agent->setIdAgent(qu.value(0).toString());
        modCong->setAgent(agent->getIdAgent());
        qu.clear();
        if(qu.exec("select SexeAgent from agent where IdAgent='"+agent->getIdAgent()+"'")){
            qu.first();
            agent->setSexe(qu.value(0).toString());
        }
    }
}

bool ModConge::champsVide()
{
    if(agentEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir l'agent");
        this->close();
        return true;
    }
    return false;
}

void ModConge::initCombo()
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

void Gui::ModConge::on_typecongeCombo_currentIndexChanged(const QString &arg1)
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

void Gui::ModConge::on_datedebutEdit_dateChanged(const QDate &date)
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

void Gui::ModConge::on_btValider_clicked()
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
    conge->setCode(modCong->getCode());
    if(conge->Equal(modCong)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        delete conge;
        return;
    }

    if(typecongeCombo->currentText()=="Normal"){
        if(datedebutEdit->date().addMonths(1).operator <(modCong->getDebut())){
          QMessageBox::critical(this,tr("Erreur"),tr("Vérifier la date de debut de conge.\n Il ne peut être ramener à moins de un mois de l'ancienne"));
          datedebutEdit->setFocus();
          return;
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
    if(conge->update()){
        QMessageBox::information(this,tr("SUCCES"),tr("conge modifié."));
        delete conge;
        delete modCong;
        delete typP;
        model->select();
        this->close();
    }
}

void Gui::ModConge::on_btAgent_clicked()
{
    FenListe = new Gui::ListeAgent(agent,agentEdit,this);
    FenListe->showNormal();
}
