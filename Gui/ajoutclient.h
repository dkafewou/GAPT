#ifndef AJOUTCLIENT_H
#define AJOUTCLIENT_H

#include <QDialog>
#include <QValidator>
#include <QSqlTableModel>
#include "Core/client.h"
#include "ui_ajouterClient.h"

namespace Gui {
    class AjoutClient : public QDialog, Ui::ajoutClient
    {
        Q_OBJECT
    public:
        explicit AjoutClient(QSqlTableModel *mod,QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QValidator *validator;
        QSqlTableModel *model;
        Core::Client *client;
    };
}

#endif // AJOUTCLIENT_H
