#ifndef AJOUTPERMISSION_H
#define AJOUTPERMISSION_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "Gui/listeagent.h"
#include "Core/permission.h"
#include "Core/typepermission.h"
#include "Core/agent.h"
#include "ui_ajouterPermission.h"

namespace Gui {
    class ajoutPermission : public QDialog, Ui::Dialog
    {
        Q_OBJECT
    public:
        explicit ajoutPermission(QSqlRelationalTableModel *mod,QWidget *parent = 0);
        void initCombo();
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_typepermissionCombo_currentIndexChanged(const QString &arg1);

        void on_datedebutEdit_dateChanged(const QDate &date);

        void on_btAgent_clicked();

        void on_btValider_clicked();

    private:
        QSqlRelationalTableModel *model;
        QSqlTableModel *mode;

        Core::Agent *agent;
        Core::TypePermission *typP;
        Core::Permission *permission;
        Gui::ListeAgent *FenListe;
    };
}

#endif // AJOUTPERMISSION_H
