#ifndef GESTRANSPORT_H
#define GESTRANSPORT_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QModelIndexList>
#include "Gui/ajoutreglement.h"
#include "Gui/modtransp.h"
#include "Core/transport.h"
#include "Core/reglement.h"
#include "Core/utilisateur.h"
#include "ui_gesTransport.h"

namespace Gui {
    class GesTransport : public QDialog, Ui::gesTransport
    {
        Q_OBJECT
    public:
        explicit GesTransport(Core::Utilisateur *use,QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_transportTableView_clicked();

        void on_btPaye_clicked();

        void on_TransporteurEdit_textChanged(const QString &arg1);

        void on_btModifier_clicked();

        void on_btSupprimer_clicked();

    private:
        QSqlRelationalTableModel *model;
        QModelIndexList liste;
        Core::Reglement *reglement;

        Gui::AjoutReglement *FenReglement;
        Gui::ModTransp *FenModTr;
        Core::transport *transport;
        Core::Utilisateur *util;
    };
}

#endif // GESTRANSPORT_H
