#ifndef CORBEILLE_H
#define CORBEILLE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QModelIndexList>
#include "Core/dossier.h"
#include "Core/agent.h"
#include "Core/formation.h"
#include "Core/sanction.h"
#include "Core/utilisateur.h"
#include "Core/transporteur.h"
#include "ui_corbeille.h"

namespace Gui {
    class Corbeille : public QDialog, Ui::corbeille
    {
        Q_OBJECT
    public:
        explicit Corbeille(QWidget *parent = 0);
        void initComposantDossier();
        void initComposantAgent();
        void initComposantFormation();
        void initComposantSanction();
        void initComposantTransporteur();

    signals:

    public slots:

    private slots:
        void on_dossierTableView_clicked();

        void on_btdossierRestaurer_clicked();

        void on_btdossierSupprimer_clicked();


        void on_agentTableView_clicked();

        void on_btagentRestaurer_clicked();

        void on_btagentSupprimer_clicked();


        void on_formationTableView_clicked();

        void on_btformationRestaurer_clicked();

        void on_btformationSupprimer_clicked();


        void on_sanctionTableView_clicked();

        void on_btsanctionRestaurer_clicked();

        void on_btsanctionSupprimer_clicked();


        void on_transporteurTableView_clicked();

        void on_bttransporteurRestaurer_clicked();

        void on_bttransporteurSupprimer_clicked();

    private:
        QSqlRelationalTableModel *modelDos;
        QModelIndexList listeDossier;
        Core::Dossier *dossier;

        QSqlRelationalTableModel *model;
        QModelIndexList listeAgent;
        Core::Agent *agent;

        QSqlRelationalTableModel *modelFormation;
        QModelIndexList listeFormation;
        Core::Formation *formation;

        QSqlRelationalTableModel *modelSanction;
        QModelIndexList listeSanction;
        Core::sanction * sanction1;

        QSqlRelationalTableModel *modelTransporteur;
        QModelIndexList listeTransporteur;
        Core::transporteur * transporteur1;

    };
}

#endif // CORBEILLE_H
