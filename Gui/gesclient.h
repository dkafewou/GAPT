#ifndef GESCLIENT_H
#define GESCLIENT_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include "Reports/etatnomination.h"
#include "Gui/ajoutclient.h"
#include "Gui/modclien.h"
#include "Core/client.h"
#include "ui_gesClient.h"

namespace Gui {
    class gesClient : public QDialog, Ui::gesClient
    {
        Q_OBJECT
    public:
        explicit gesClient(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btNouveau_clicked();

        void on_clientTableView_clicked();

        void on_btSupprimer_clicked();

        void on_nomEdit_textChanged(const QString &arg1);

        void on_btModifier_clicked();

        void on_btApercu_clicked();

    private:
        QSqlTableModel *model;
        QModelIndexList liste;

        Gui::AjoutClient *FenAjoutClient;
        Gui::ModClien *FenModclient;
        Core::Client *client;


        QSqlQueryModel *modelEtat;
        Reports::EtatNomination *etat;
    };
}

#endif // GESCLIENT_H
