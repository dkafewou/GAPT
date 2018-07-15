#ifndef AJOUTSERVICE_H
#define AJOUTSERVICE_H

#include <QDialog>
#include <QValidator>
#include <QSqlTableModel>
#include "ui_ajouterService.h"
#include "Core/service.h"

namespace Gui {
    class AjoutService : public QDialog,Ui::ajoutService
    {
        Q_OBJECT
    public:
        explicit AjoutService(QSqlTableModel *mod,QWidget *parent = 0);

        void initComposant();
        bool champsVides();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QValidator *validator;
        QSqlTableModel *model;

        Core::service *service;
    };
}

#endif // AJOUTSERVICE_H
