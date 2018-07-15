#ifndef AJOUTFORMATION_H
#define AJOUTFORMATION_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QModelIndexList>
#include <QSqlTableModel>
#include "ui_ajouterFormation.h"
#include "Core/formation.h"
#include "Core/participant.h"
#include "Core/agent.h"
#include "Gui/listeagent.h"

namespace Gui {
    class AjoutFormation : public QDialog, Ui::ajouterFormation
    {
        Q_OBJECT
    public:
        explicit AjoutFormation(QSqlTableModel *mod,QWidget *parent = 0);
        void initComposant();
        bool champVideFormation();
        void initParticipant();
        void initTable();

    signals:

    public slots:

    private slots:
        void on_finDateEdit_dateChanged(const QDate &date);

        void on_btOk_clicked();

        void on_btAgent_clicked();

        void on_btAjouter_clicked();

        void on_agentTableView_clicked();

        void on_btSupprimer_clicked();

        void on_matrEdit_textChanged(const QString &arg1);

        void on_nomEdit_textChanged(const QString &arg1);

    private:
        Core::Formation *formation;
        Core::Participant *participant;
        Core::Agent *agent;
        Gui::ListeAgent *FenListeAgent;

        QSqlQueryModel *model;
        QSqlTableModel *mode;
        QModelIndexList liste;
        QSqlQuery query;
    };
}

#endif // AJOUTFORMATION_H
