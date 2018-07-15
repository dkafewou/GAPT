#ifndef MODCLIEN_H
#define MODCLIEN_H

#include <QDialog>
#include <QSqlTableModel>
#include <QValidator>
#include "Core/client.h"
#include "ui_modClient.h"

namespace Gui {
    class ModClien : public QDialog, Ui::modClient
    {
        Q_OBJECT
    public:
        explicit ModClien(QSqlTableModel *mod,Core::Client *cli, QWidget *parent = 0);
        void initcomposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QSqlTableModel *model;
        QValidator *validator;

        Core::Client *client;
        Core::Client *modcli;
    };
}

#endif // MODCLIEN_H
