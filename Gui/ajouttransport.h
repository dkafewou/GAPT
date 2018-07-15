#ifndef AJOUTTRANSPORT_H
#define AJOUTTRANSPORT_H

#include <QDialog>
#include "Core/conteneur.h"
#include "Core/transport.h"
#include "Core/transporteur.h"
#include "Gui/listetransporteur.h"
#include "ui_ajouterTransport.h"

namespace Gui {
    class AjoutTransport : public QDialog, Ui::AjouterTransp
    {
        Q_OBJECT
    public:
        explicit AjoutTransport(Core::Conteneur *cont,QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_datetransportEdit_dateChanged(const QDate &date);

        void on_btValider_clicked();

        void on_btTr_clicked();

    private:
        Core::Conteneur *conteneur;
        Core::transporteur *transporteur;
        Core::transport *transp;

        Gui::ListeTransporteur *FenListe;
    };
}

#endif // AJOUTTRANSPORT_H
