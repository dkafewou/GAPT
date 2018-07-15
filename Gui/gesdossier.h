#ifndef GESDOSSIER_H
#define GESDOSSIER_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QModelIndexList>
#include <QSystemTrayIcon>
#include "Core/conteneur.h"
#include <Core/dossier.h>
#include "Gui/ajoutdepdos.h"
#include "Gui/ajoutdossier.h"
#include "Gui/ajouttransport.h"
#include "Core/utilisateur.h"
#include "ui_gesDossier.h"

namespace Gui {
    class GesDossier : public QDialog, Ui::gesDossier
    {
        Q_OBJECT
    public:
        explicit GesDossier(Core::Utilisateur *use,QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_dossierTableView_clicked();

        void on_repEdit_textChanged(const QString &arg1);

        void on_clientEdit_textChanged(const QString &arg1);

        void on_btNouveau_clicked();

        void on_btModifier_clicked();

        void on_btSupprimer_clicked();

        void on_btDepense_clicked();

        void on_btTransport_clicked();

        void on_contTableView_clicked();

    private:
        QSqlRelationalTableModel *modelDos;
        QSqlTableModel *modelCont;
        QModelIndexList listeDos;
        QModelIndexList listeCont;

        Gui::AjoutDossier *FenAjoutDoss;
        Gui::AjoutDossier *FenModDoss;
        Gui::AjoutDepDos *FenAjoutDepDos;
        Gui::AjoutTransport *FenTransport;
        Core::Dossier *dossier;
        Core::Conteneur *conteneur;
        Core::Utilisateur *util;
    };
}

#endif // GESDOSSIER_H
