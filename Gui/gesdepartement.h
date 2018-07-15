#ifndef GESDEPARTEMENT_H
#define GESDEPARTEMENT_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include "ui_gesDepartement.h"
#include "Gui/ajoutservice.h"
#include "Gui/modservice.h"
#include "Gui/ajoutdirection.h"
#include "Gui/moddirection.h"
#include "Gui/ajoutfonction.h"
#include "Gui/modfonction.h"
#include "Core/service.h"
#include "Core/direction.h"
#include "Core/fonction.h"

namespace Gui {
    class GesDepartement : public QDialog,Ui::gesDepartement
    {
        Q_OBJECT
    public:
        explicit GesDepartement(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btSNouveau_clicked();

        void on_serviceEdit_textChanged(const QString &arg1);

        void on_btDNouveau_clicked();

        void on_directionEdit_textChanged(const QString &arg1);

        void on_btFNouveau_clicked();

        void on_fonctionEdit_textChanged(const QString &arg1);

        void on_btSModifier_clicked();

        void on_btSupprimer_clicked();

        void on_serviceTableView_clicked();

        void on_btDModifier_clicked();

        void on_btDSupprimer_clicked();

        void on_directionTableView_clicked();

        void on_btFModifier_clicked();

        void on_btFSupprimer_clicked();

        void on_fonctionTableView_clicked();

    private:
        QSqlTableModel *modelService;
        QSqlTableModel *modelDirection;
        QSqlTableModel *modelFonction;
        QModelIndexList listeService;
        QModelIndexList listeFonction;
        QModelIndexList listeDirection;

        Gui::AjoutService *FenAjoutService;
        Gui::AjoutDirection *FenAjoutDirection;
        Gui::AjoutFonction *FenAjoutFonction;
        Gui::ModService *FenModServ;
        Gui::ModDirection *FenModDirection;
        Gui::ModFonction *FenModFonct;

        Core::service *service;
        Core::Direction *direction;
        Core::Fonction *fonction;

    };
}

#endif // GESDEPARTEMENT_H
