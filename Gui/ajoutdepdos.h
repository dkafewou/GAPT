#ifndef AJOUTDEPDOS_H
#define AJOUTDEPDOS_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QModelIndexList>
#include <QValidator>
#include <Reports/reportdepense.h>
#include <QSqlQueryModel>
#include "Core/agent.h"
#include "Core/depense.h"
#include "Core/dossier.h"
#include "Core/subir.h"
#include "Gui/listeagent.h"
#include "Gui/listedepense.h"
#include "ui_ajoutDepDos.h"

namespace Gui {
    class AjoutDepDos : public QDialog, Ui::ajoutDepDossier
    {
        Q_OBJECT
    public:
        explicit AjoutDepDos(Core::Dossier *dos,QWidget *parent = 0);
        void initComposant();
        void initDossier();
        void initTable();
        void initCombo();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btAgent_clicked();

        void on_btDep_clicked();

        void on_bonEdit_textChanged();

        void on_btAjouter_clicked();

        void on_btValide_clicked();

        void on_contTableView_clicked();

        void on_btSupprimer_clicked();

        void on_btModifier_clicked();

        void on_btVoir_clicked();

    private:
        QSqlTableModel *model;
        QSqlRelationalTableModel *modelCont;
        QValidator *validator;
        QModelIndexList liste;
        QSqlQueryModel *modelEtat;

        Core::Dossier *dossier;
        Core::Depense *depense;
        Core::Agent *agent;
        Core::Subir *subir;
        Core::Subir *modSub;

        Gui::ListeAgent *FenAgent;
        Gui::ListeDepense *FenDepense;
        Reports::ReportDepense *prefact;
    };
}

#endif // AJOUTDEPDOS_H
