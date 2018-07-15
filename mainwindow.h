#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QStyleFactory>
#include <QDial>
#include "ui_mainwindow.h"
#include "Gui/gesutilisateur.h"
#include "Gui/gescateg.h"
#include "Gui/gesagent.h"
#include "Gui/gesdepartement.h"
#include "Gui/gestransporteur.h"
#include "Gui/gesconge.h"
#include "Gui/gesdepart.h"
#include "Gui/gessanction.h"
#include "Gui/gespermission.h"
#include "Gui/gesformation.h"
#include "Gui/gesclient.h"
#include "Gui/gesdepense.h"
#include "Gui/gesreglement.h"
#include "Gui/gesdossier.h"
#include "Gui/changerpassword.h"
#include "Gui/gestransport.h"
#include "Gui/parametre.h"
#include "Gui/corbeille.h"
#include "Core/utilisateur.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow,Ui::MainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QDial *dia,Core::Utilisateur *user, QWidget *parent = 0);
    ~MainWindow();

    void initComposant();
    void initProfilChefP();
    void initProfilCaisse();
    void initProfilSecretaire();
    
private slots:
    void on_actionUtilisateur_triggered();

    void on_actionQuitter_triggered();

    void on_actionCategorie_triggered();

    void on_actionAgent_triggered();

    void on_actionDepartement_triggered();

    void on_actionTransporteur_triggered();

    void on_actionConge_triggered();

    void on_actionDepart_triggered();

    void on_actionSanction_triggered();

    void on_actionPermission_triggered();

    void on_actionFormation_triggered();

    void on_actionClient_triggered();

    void on_actionDepense_triggered();

    void on_actionReglement_triggered();

    void on_actionDossier_triggered();

    void on_actionDeconnexion_triggered();

    void on_actionChangerPassword_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionTransport_triggered();

    void on_actionParametre_triggered();

    void on_actionCorbeil_triggered();

private:
    QDial *dial;

    Gui::GesUtilisateur *FenGesUser;
    Gui::GesCateg *FenGesCateg;
    Gui::GesAgent *FenGesAgent;
    Gui::GesDepartement *FenGesDepart;
    Gui::GesTransporteur *FenGesTransporteur;
    Gui::GesConge *FenGesConge;
    Gui::GesDepart *FenGesDepar;
    Gui::GesPermission *FenGesPerm;
    Gui::GesSanction * FenGesSanction;
    Gui::GesFormation *FenGesFormation;
    Gui::gesClient *FenGesClient;
    Gui::gesDepense *FenGesdepense;
    Gui::gesReglement *FenGesRegl;
    Gui::GesDossier *FenGesDossier;
    Gui::ChangerPassword *FenChangerPassword;
    Gui::GesTransport *FenGesTransport;
    Gui::Parametre *FenParametre;
    Gui::Corbeille *FenCorbeil;
    Core::Utilisateur *Users;
};

#endif // MAINWINDOW_H
