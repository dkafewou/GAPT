#ifndef GESPERMISSION_H
#define GESPERMISSION_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlQueryModel>
#include <QModelIndexList>
#include "Reports/etatnomination.h"
#include "Core/permission.h"
#include "Gui/gestypeperm.h"
#include "Gui/ajoutpermission.h"
#include "Gui/modpermission.h"
#include "ui_gesPermission.h"

namespace Gui {
    class GesPermission : public QDialog, Ui::gesPermission
    {
        Q_OBJECT
    public:
        explicit GesPermission(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btTypePermission_clicked();

        void on_btNouveau_clicked();

        void on_permissionTableView_clicked();

        void on_btValider_2_clicked();

        void on_btSupprimer_clicked();

        void on_agentEdit_textChanged(const QString &arg1);

        void on_permissionEdit_textChanged(const QString &arg1);

        void on_btAper_clicked();

    private:
        QSqlRelationalTableModel *model;
        QModelIndexList liste;
        QSqlQueryModel *modelEtat;

        Core::Permission *permission;
        Gui::GesTypePerm *FenTypePer;
        Gui::ajoutPermission *FenPermission;
        Gui::ModPermission *FenMod;
        Reports::EtatNomination *prevision;
    };
}

#endif // GESPERMISSION_H
