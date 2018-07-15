#ifndef GESDEPART_H
#define GESDEPART_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QModelIndexList>
#include "Gui/gestypedepart.h"
#include "Gui/moddepart.h"
#include "Core/depart.h"
#include "Core/agent.h"
#include "Gui/ajoutdepart.h"
#include "ui_gesDepart.h"

namespace Gui {
    class GesDepart : public QDialog, Ui::gesDepart
    {
        Q_OBJECT
    public:
        explicit GesDepart(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btType_clicked();

        void on_btNouveau_clicked();

        void on_AgentEdit_textChanged(const QString &arg1);

        void on_typeEdit_textChanged(const QString &arg1);

        void on_departTableView_clicked();

        void on_btModifier_clicked();

        void on_btSupprimer_clicked();

    private:
        Gui::GesTypeDepart *FenTypeDep;
        Gui::AjoutDepart *FenAjoutDepart;
        Gui::ModDepart *FenModDep;
        Core::Depart *depart;
        Core::Agent *agent;

        QSqlRelationalTableModel *model;
        QModelIndexList liste;
        QSqlQuery *query;
    };
}

#endif // GESDEPART_H
