#include "modpermission.h"

using namespace Gui;

ModPermission::ModPermission(QSqlRelationalTableModel *mod, Core::Permission *perm, QWidget *parent):
    QDialog(parent),model(mod),Permit(perm)
{
    setupUi(this);
    initComposant();
    initCombo();
}

void ModPermission::initCombo()
{
    mode = new QSqlTableModel;
    mode->setTable("typepermission");
    mode->setHeaderData(0,Qt::Horizontal,tr("Code"));
    mode->setHeaderData(1,Qt::Horizontal,tr("Libellé"));
    mode->setHeaderData(2,Qt::Horizontal,tr("nbrejour"));
    mode->setHeaderData(3,Qt::Horizontal,tr("supr"));
    mode->setFilter("SupprTypePermission=0");
    mode->select();

    typepermissionCombo->setModel(mode);
    typepermissionCombo->setModelColumn(1);
    typepermissionCombo->show();
}

void ModPermission::initComposant()
{
    typP = new Core::TypePermission;
    agentEdit->setText(Permit->getAgent());
    typepermissionCombo->setCurrentIndex(typepermissionCombo->findText(Permit->getType()));
    motiftEdit->setPlainText(Permit->getMotif());
    datedebutEdit->setDate(Permit->getDebut());
    datefinEdit->setDate(Permit->getFin());
    dateretoureffectifEdit->setDate(Permit->getRetour());
}

bool ModPermission::champsVide()
{
    if(agentEdit->text().isEmpty()){
        QMessageBox::critical(this,"ERREUR 11810","Veuillez choisir l'agent");
        this->close();
        return true;
    }
    return false;
}

void Gui::ModPermission::on_typepermissionCombo_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    query.clear();
    query.prepare("select * from typepermission where LibellePermission='"+arg1+"'");
    if(query.exec()){
        if(query.first()){
         typP->setCode(query.value(0).toString());
         typP->setLibelle(query.value(1).toString());
         typP->setNbrJours(query.value(2).toInt());
         datefinEdit->setDate(datedebutEdit->date().addDays(typP->getNbrJours()));
         dateretoureffectifEdit->setDate(datedebutEdit->date().addDays(typP->getNbrJours()));
        }
    }
}

void Gui::ModPermission::on_btValider_clicked()
{
    if(champsVide())
        return;
    permission = new Core::Permission;
    permission->setAgent(Permit->getAgent());
    permission->setType(typP->getCode());
    permission->setMotif(motiftEdit->toPlainText());
    permission->setDebut(datedebutEdit->date());
    permission->setFin(datefinEdit->date());
    permission->setRetour(dateretoureffectifEdit->date());
    permission->setSuppr(false);
    permission->setCode(Permit->getCode());
    if(permission->Equal(Permit)){
        QMessageBox::critical(this, tr("Erreur 20230"), tr("<b>Aucune modification n'a été effectuer</b>")) ;
        delete permission;
        return;
    }
    if(permission->update()){
        QMessageBox::information(this, tr("Succès"), tr("<B>Permission modifiée</B>") ) ;
        delete permission;
        model->select();
        this->close();
    }
}
