#ifndef AJOUTSANCTION_H
#define AJOUTSANCTION_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include "ui_ajouterSanction.h"
#include "Gui/listeagent.h"
#include "Core/sanction.h"
#include "Core/agent.h"

namespace Gui {
    class AjoutSanction : public QDialog, Ui::sanction
    {
        Q_OBJECT
    public:
        explicit AjoutSanction(QSqlRelationalTableModel *mod,QWidget *parent = 0);
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btAgent_clicked();

        void on_btValider_clicked();

    private:
        QSqlRelationalTableModel *model;

        Gui::ListeAgent *FenListeAgent;
        Core::sanction *Sanction;
        Core::Agent *agent;
    };
}

#endif // AJOUTSANCTION_H
