#ifndef GESAGENT_H
#define GESAGENT_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QModelIndexList>
#include <QSqlTableModel>
#include "Core/salaire.h"
#include "Reports/reportmodel.h"
#include "Gui/affectation.h"
#include "Gui/ajoutagent.h"
#include "Gui/modagent.h"
#include "Gui/nommeragent.h"
#include "Gui/mouvement.h"
#include "Core/agent.h"
#include "Reports/etatnomination.h"
#include "ui_gesAgent.h"

namespace Gui {
    class GesAgent : public QDialog, Ui::gesAgent
    {
        Q_OBJECT
    public:
        explicit GesAgent(QWidget *parent = 0);
        void initComposant();
        void initCombo();

    signals:

    public slots:

    private slots:
        void on_btNouveau_clicked();

        void on_btSupprimer_clicked();

        void on_btModifer_clicked();

        void on_agentTableView_clicked();

        void on_btActualiser_clicked();

        void on_nomEdit_textChanged(const QString &arg1);

        void on_prenomEdit_textChanged(const QString &arg1);

        void on_btAffecter_clicked();

        void on_btNommer_clicked();

        void on_btMouvement_clicked();

        void on_categorieComboBox_currentIndexChanged(const QString &arg1);

        void on_sexeComboBox_currentIndexChanged(const QString &arg1);

        void on_btBulletin_clicked();

        void on_btApercu_clicked();

    private:
        QSqlRelationalTableModel *model;
        QSqlTableModel *comboModel;
        QModelIndexList liste;

        Gui::AjoutAgent *FenAjoutAgent;
        Gui::ModAgent *FenMod;
        Gui::Affectation *FenAffectation;
        Gui::NommerAgent *FenNomination;
        Gui::Mouvement *FenMouvement;
        Core::Agent *agent;
        Core::Salaire *salaire;
        Reports::ReportModel *bulletin;

        QSqlQueryModel *modelEtat;
        Reports::EtatNomination *etat;
    };
}

#endif // GESAGENT_H
