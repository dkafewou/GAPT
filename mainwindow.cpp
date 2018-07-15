#include "mainwindow.h"

MainWindow::MainWindow(QDial *dia, Core::Utilisateur *user, QWidget *parent) :
    QMainWindow(parent),dial(dia),Users(user)
{
    setupUi(this);   
   // QApplication::setStyle(QStyleFactory::create("Fusion"));
    initComposant();
    if(Users->getProfil()=="Secrétariat")
        initProfilSecretaire();
    if(Users->getProfil()=="Caisse")
        initProfilCaisse();
    if(Users->getProfil()=="Chef Personnel")
        initProfilChefP();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initComposant()
{
    FenGesAgent = new Gui::GesAgent(0);
    FenGesDepart = new Gui::GesDepartement(0);
    FenGesDossier = new Gui::GesDossier(Users);
    FenGesTransport = new Gui::GesTransport(Users);
}

void MainWindow::initProfilChefP()
{
    actionParametre->setEnabled(false);
    actionUtilisateur->setEnabled(false);
    actionCorbeil->setEnabled(false);

    actionDossier->setEnabled(false);
    actionTransport->setEnabled(false);
    actionTransporteur->setEnabled(false);
    actionClient->setEnabled(false);
    actionDepense->setEnabled(false);
    actionReglement->setEnabled(false);
}

void MainWindow::initProfilCaisse()
{
    actionParametre->setEnabled(false);
    actionUtilisateur->setEnabled(false);
    actionCorbeil->setEnabled(false);

    actionAgent->setEnabled(false);
    actionDepartement->setEnabled(false);
    actionConge->setEnabled(false);
    actionPermission->setEnabled(false);
    actionDepart->setEnabled(false);
    actionSanction->setEnabled(false);
    actionFormation->setEnabled(false);
    actionCategorie->setEnabled(false);
    actionTransporteur->setEnabled(false);
    actionClient->setEnabled(false);
}

void MainWindow::initProfilSecretaire()
{
    actionParametre->setEnabled(false);
    actionUtilisateur->setEnabled(false);
    actionCorbeil->setEnabled(false);

    actionAgent->setEnabled(false);
    actionDepartement->setEnabled(false);
    actionConge->setEnabled(false);
    actionPermission->setEnabled(false);
    actionDepart->setEnabled(false);
    actionSanction->setEnabled(false);
    actionFormation->setEnabled(false);
    actionCategorie->setEnabled(false);
    actionDepense->setEnabled(false);
    actionReglement->setEnabled(false);
}

void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}

void MainWindow::on_actionUtilisateur_triggered()
{
    FenGesUser = new Gui::GesUtilisateur(this);
    FenGesUser->showMaximized();
}

void MainWindow::on_actionCategorie_triggered()
{
    FenGesCateg = new Gui::GesCateg(this);
    FenGesCateg->showMaximized();
}

void MainWindow::on_actionAgent_triggered()
{
    actionTransport->setChecked(false);
    actionDossier->setChecked(false);
    actionDepartement->setChecked(false);
    if(actionAgent->isChecked()){
        FenGesAgent = new Gui::GesAgent(0);
        this->setCentralWidget(FenGesAgent);
        FenGesAgent->show();
    }
    actionAgent->setChecked(true);
}

void MainWindow::on_actionDepartement_triggered()
{
    actionTransport->setChecked(false);
    actionDossier->setChecked(false);
    actionAgent->setChecked(false);
    if(actionDepartement->isChecked()){
        FenGesDepart = new Gui::GesDepartement(0);
        this->setCentralWidget(FenGesDepart);
        FenGesDepart->show();
    }
    actionDepartement->setChecked(true);
}

void MainWindow::on_actionDossier_triggered()
{
    actionTransport->setChecked(false);
    actionDepartement->setChecked(false);
    actionAgent->setChecked(false);
    if(actionDossier->isChecked()){
        FenGesDossier = new Gui::GesDossier(Users);
        this->setCentralWidget(FenGesDossier);
        FenGesDossier->show();
    }
    actionDossier->setChecked(true);
}

void MainWindow::on_actionTransport_triggered()
{
    actionDepartement->setChecked(false);
    actionAgent->setChecked(false);
    actionDossier->setChecked(false);
    if(actionTransport->isChecked()){
        FenGesTransport = new Gui::GesTransport(Users);
        this->setCentralWidget(FenGesTransport);
        FenGesTransport->show();
    }
    actionTransport->setChecked(true);
}

void MainWindow::on_actionTransporteur_triggered()
{
    FenGesTransporteur = new Gui::GesTransporteur(this);
    FenGesTransporteur->showMaximized();
}

void MainWindow::on_actionConge_triggered()
{
    FenGesConge = new Gui::GesConge(this);
    FenGesConge->showMaximized();
}

void MainWindow::on_actionDepart_triggered()
{
    FenGesDepar = new Gui::GesDepart(this);
    FenGesDepar->showMaximized();
}

void MainWindow::on_actionSanction_triggered()
{
    FenGesSanction= new Gui::GesSanction(this);
    FenGesSanction->showMaximized();
}

void MainWindow::on_actionPermission_triggered()
{
    FenGesPerm = new Gui::GesPermission(this);
    FenGesPerm->showMaximized();
}

void MainWindow::on_actionFormation_triggered()
{
    FenGesFormation =new Gui::GesFormation(this);
    FenGesFormation->showMaximized();
}

void MainWindow::on_actionClient_triggered()
{
    FenGesClient  = new Gui::gesClient(this);
    FenGesClient->showMaximized();
}

void MainWindow::on_actionDepense_triggered()
{
    FenGesdepense =new Gui::gesDepense(this);
    FenGesdepense->showMaximized();
}

void MainWindow::on_actionReglement_triggered()
{
    FenGesRegl = new Gui::gesReglement(this);
    FenGesRegl->showMaximized();
}

void MainWindow::on_actionDeconnexion_triggered()
{
    dial->setValue(1);
}

void MainWindow::on_actionChangerPassword_triggered()
{
    FenChangerPassword = new Gui::ChangerPassword(Users,this);
    FenChangerPassword->show();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    //QMessageBox::aboutQt(this);
}

void MainWindow::on_actionParametre_triggered()
{
    FenParametre = new Gui::Parametre(this);
    FenParametre->show();
}

void MainWindow::on_actionCorbeil_triggered()
{
    FenCorbeil = new Gui::Corbeille(this);
    FenCorbeil->showMaximized();
}
