#ifndef MODAGENT_H
#define MODAGENT_H

#include <QDialog>
#include <QValidator>
#include <QSqlRelationalTableModel>
#include "Core/agent.h"
#include "Gui/listecategorie.h"
#include "ui_modAgent.h"

namespace Gui {
    class ModAgent : public QDialog, Ui::modAgent
    {
        Q_OBJECT
    public:
        explicit ModAgent(QSqlRelationalTableModel *mod,Core::Agent *ag,QWidget *parent = 0);
        void initComposant();
        bool champsVides();

    signals:

    public slots:

    private slots:
        void on_datenaissEdit_dateChanged(const QDate &date);

        void on_btCategorie_clicked();

        void on_btValider_clicked();

    private:
        QValidator *validator;
        QSqlRelationalTableModel *model;

        Gui::ListeCategorie *FenCateg;
        Core::Agent *agent;
        Core::Agent *modAg;
    };
}

#endif // MODAGENT_H
