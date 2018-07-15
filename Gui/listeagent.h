#ifndef LISTEAGENT_H
#define LISTEAGENT_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include <QLineEdit>
#include "ui_listeAgent.h"
#include "Core/agent.h"

namespace Gui {
    class ListeAgent : public QDialog, Ui::ListeAgent
    {
        Q_OBJECT
    public:
        explicit ListeAgent(Core::Agent *agen,QLineEdit *edi,QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_matrEdit_textChanged(const QString &arg1);

        void on_nomEdit_textChanged(const QString &arg1);

        void on_btOk_clicked();

        void on_agentTableView_clicked();

    private:
        QSqlTableModel *model;
        QModelIndexList liste;

        Core::Agent *agent;
        QLineEdit *edit;
    };
}

#endif // LISTEAGENT_H
