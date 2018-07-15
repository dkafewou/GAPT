#ifndef MODIFIERFORMATION_H
#define MODIFIERFORMATION_H

#include <QDialog>
#include "ui_modifierFormation.h"
#include <QSqlQueryModel>
#include <QModelIndexList>
#include <QSqlTableModel>
#include "Core/formation.h"
#include "Core/participant.h"
#include "Core/agent.h"
#include "Gui/listeagent.h"

namespace Gui {
    class ModifierFormation : public QDialog, Ui::modifierFormation
    {
        Q_OBJECT
    public:
        explicit ModifierFormation(Core::Formation *form,QSqlTableModel *mod,QWidget *parent = 0);
        void initComposant();
        bool champVideFormation();
        void initTable();

    signals:

    public slots:

    private slots:
        void on_btOk_clicked();

        void on_agentTableView_clicked();

        void on_btSupprimer_clicked();

        void on_btAgent_clicked();

        void on_btAjouter_clicked();

        void on_matrEdit_textChanged(const QString &arg1);

        void on_nomEdit_textChanged(const QString &arg1);

    private:
        Core::Formation *formation;
        Core::Formation *modForm;
        Core::Participant *participant;
        Core::Agent *agent;
        Gui::ListeAgent *FenListeAgent;

        QSqlQueryModel *model;
        QSqlTableModel *mode;
        QModelIndexList liste;
        QSqlQuery query;
    };
}

#endif // MODIFIERFORMATION_H
