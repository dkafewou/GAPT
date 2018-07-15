#ifndef AJOUTDOSSIER_H
#define AJOUTDOSSIER_H

#include <QDialog>
#include <QValidator>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QModelIndexList>
#include "Core/dossier.h"
#include "Core/conteneur.h"
#include "ui_ajoutDossier.h"

namespace Gui {
    class AjoutDossier : public QDialog, Ui::ajoutDossier
    {
        Q_OBJECT
    public:
        explicit AjoutDossier(QSqlRelationalTableModel *mod,QWidget *parent = 0);
        explicit AjoutDossier(Core::Dossier *dos,QSqlRelationalTableModel *mod,QWidget *parent = 0);
        void initComposant();
        void initCombo();
        void initComposantMod();
        void initConteneur();
        void initTable();
        bool champsVide();
        bool champsVideCont();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

        void on_btAjouter_clicked();

        void on_contTableView_clicked();

        void on_btSupprimer_clicked();

        void on_btModifier_clicked();

        void on_btValide_clicked();

        void on_btModif_clicked();

    private:
        QValidator *validator;
        QSqlTableModel *model;
        QSqlTableModel *modelCont;
        QSqlRelationalTableModel *modelDoss;
        QModelIndexList liste;

        Core::Dossier *dossier;
        Core::Dossier *ModDoss;
        Core::Conteneur *conteneur;
        Core::Conteneur *modCont;
    };
}

#endif // AJOUTDOSSIER_H
