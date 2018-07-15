#ifndef MODTRANQPORTEUR_H
#define MODTRANQPORTEUR_H

#include <QDialog>
#include <QSqlTableModel>
#include <QValidator>
#include "Core/transporteur.h"
#include "ui_ModTransporteur.h"

namespace Gui {
    class ModTranqporteur : public QDialog,Ui::ModTransporteur
    {
        Q_OBJECT
    public:
        explicit ModTranqporteur(QSqlTableModel *mod,Core::transporteur *tr, QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btVlider_clicked();

    private:
        QSqlTableModel *model;
        QValidator *validator;

        Core::transporteur *transporteur;
        Core::transporteur *ModTransp;
    };
}

#endif // MODTRANQPORTEUR_H
