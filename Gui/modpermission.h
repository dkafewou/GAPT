#ifndef MODPERMISSION_H
#define MODPERMISSION_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "Gui/listeagent.h"
#include "Core/permission.h"
#include "Core/typepermission.h"
#include "ui_modPermission.h"

namespace Gui {
    class ModPermission : public QDialog, Ui::DialogMod
    {
        Q_OBJECT
    public:
        explicit ModPermission(QSqlRelationalTableModel *mod,Core::Permission *perm,QWidget *parent = 0);
        void initCombo();
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_typepermissionCombo_currentIndexChanged(const QString &arg1);

        void on_btValider_clicked();

    private:
        QSqlRelationalTableModel *model;
        QSqlTableModel *mode;

        Core::TypePermission *typP;
        Core::Permission *permission,*Permit;
        Gui::ListeAgent *FenListe;
    };
}

#endif // MODPERMISSION_H
