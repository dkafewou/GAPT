#include "gesutilisateur.h"

using namespace Gui;

GesUtilisateur::GesUtilisateur(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    model = new QSqlRelationalTableModel(this);
    initComposant();
}

void GesUtilisateur::initComposant()
{
    model->setTable("utilisateur");
    model->setHeaderData(0,Qt::Horizontal,tr("Numero"));
    model->setHeaderData(1,Qt::Horizontal,tr("Agent"));
    model->setHeaderData(2,Qt::Horizontal,tr("Pseudo"));
    model->setHeaderData(3,Qt::Horizontal,tr("Mot de passe"));
    model->setHeaderData(4,Qt::Horizontal,tr("Profil"));
    model->setHeaderData(5,Qt::Horizontal,tr("Date création"));
    model->setHeaderData(6,Qt::Horizontal,tr("Suppr"));
    model->setRelation(1, QSqlRelation("agent", "IdAgent", "NomAgent"));
    model->setFilter("SupprUser=0");
    model->select();

    userTableView->setModel(model);
    userTableView->hideColumn(6);
    userTableView->hideColumn(3);
    userTableView->hideColumn(0);
    userTableView->show();
}

void Gui::GesUtilisateur::on_btNouveau_clicked()
{
    FenUser = new Gui::AjoutUser(model,this);
    FenUser->showNormal();
}

void Gui::GesUtilisateur::on_btModifier_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner la ligne à modifier</B>"));
        return;
    }
    user = new Core::Utilisateur;
    user->setCode(liste.at(0).data().toString());
    user->setAgent(liste.at(1).data().toString());
    user->setPseudo(liste.at(2).data().toString());
    user->setPassword(liste.at(3).data().toString());
    user->setProfil(liste.at(4).data().toString());
    user->setDate(liste.at(5).data().toDate());
    user->setSuppr(liste.at(6).data().toBool());

    FenModUser = new Gui::ModUser(model,user,this);
    FenModUser->showNormal();
}

void Gui::GesUtilisateur::on_userTableView_clicked()
{
    liste = userTableView->selectionModel()->selection().indexes();
}

void Gui::GesUtilisateur::on_btDesactiver_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner l'utilisateur à desactiver</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment desactiver cet utilisateur?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            user = new Core::Utilisateur;
            user->setCode(liste.at(0).data().toString());
           if(user->remove()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Utilisateur désactivé</B>") ) ;
               model->select();
               delete user;
           }
        }
}

void Gui::GesUtilisateur::on_btSupprimer_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner l'utilisateur à supprimer</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment supprimer cet utilisateur?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            user = new Core::Utilisateur;
            user->setCode(liste.at(0).data().toString());
           if(user->Delete()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Utilisateur supprimé</B>") ) ;
               model->select();
               delete user;
           }
        }
}

void Gui::GesUtilisateur::on_btReactiver_clicked()
{
    if(liste.isEmpty()){
        QMessageBox::warning(this,"ERREUR 20230",tr("<B>Veuillez selectionner l'utilisateur à réactiver</B>"));
        return;
    }

    int rep = QMessageBox::question(this,"Confirmation",tr("<B>Voulez vous vraiment réasactiver cet utilisateur?</B>"),QMessageBox::Yes|QMessageBox::No);
        if(rep == QMessageBox::Yes){
            user = new Core::Utilisateur;
            user->setCode(liste.at(0).data().toString());
           if(user->restore()){
               QMessageBox::information(this, tr("Succès"), tr("<B>Utilisateur Réasactivé</B>") ) ;
               model->select();
               delete user;
           }
        }
}

void Gui::GesUtilisateur::on_agentEdit_textChanged(const QString &arg1)
{
    model->setFilter("SupprUser=0 and NomAgent like '"+arg1+"%' ");
    liste.clear();
}

void Gui::GesUtilisateur::on_btActualiser_clicked()
{
    initComposant();
}

void Gui::GesUtilisateur::on_profilComboBox_currentIndexChanged(const QString &arg1)
{
    if(comboBox->currentText()=="Activer"){
        model->setFilter("SupprUser=0 and Profil like '"+arg1+"%' ");
    }else {
         model->setFilter("SupprUser=1 and Profil like '"+arg1+"%' ");
    }
    liste.clear();
}

void Gui::GesUtilisateur::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1=="Activer"){
        model->setFilter("SupprUser=0 and Profil like '"+profilComboBox->currentText()+"%' ");
    }else {
         model->setFilter("SupprUser=1 and Profil like '"+profilComboBox->currentText()+"%' ");
    }
    liste.clear();
}

void Gui::GesUtilisateur::on_btApercu_clicked()
{
}
