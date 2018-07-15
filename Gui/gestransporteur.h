#ifndef GESTRANSPORTEUR_H
#define GESTRANSPORTEUR_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include "Gui/modtranqporteur.h"
#include "Gui/ajouttransporteur.h"
#include "Reports/etatnomination.h"
#include "ui_gesTransporteur.h"

namespace Gui {
    class GesTransporteur : public QDialog,Ui::gesTransporteur
    {
        Q_OBJECT
    public:
        explicit GesTransporteur(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btNouveau_clicked();

        void on_btModifier_clicked();

        void on_btSupprimer_clicked();

        void on_transporteurTableView_clicked();

        void on_nomEdit_textChanged(const QString &arg1);

        void on_prenomEdit_textChanged(const QString &arg1);

        void on_btApercu_clicked();

    private:
        Gui::AjoutTransporteur *FenAjoutTransp;
        Gui::ModTranqporteur *FenModTr;
        Core::transporteur *transp;

        QSqlTableModel *model;
        QModelIndexList liste;


        QSqlQueryModel *modelEtat;
        Reports::EtatNomination *etat;
    };
}

#endif // GESTRANSPORTEUR_H
