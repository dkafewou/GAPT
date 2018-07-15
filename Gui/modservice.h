#ifndef MODSERVICE_H
#define MODSERVICE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QValidator>
#include "Core/service.h"
#include "ui_ModService.h"

namespace Gui {
    class ModService : public QDialog, Ui::ModService
    {
        Q_OBJECT
    public:
        explicit ModService(QSqlTableModel *mod,Core::service *serv, QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QSqlTableModel *model;
        QValidator *validator;

        Core::service *service;
        Core::service *modServ;
    };
}

#endif // MODSERVICE_H
