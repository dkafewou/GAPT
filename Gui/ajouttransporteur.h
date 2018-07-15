#ifndef AJOUTTRANSPORTEUR_H
#define AJOUTTRANSPORTEUR_H

#include <QDialog>
#include <QSqlTableModel>
#include <QValidator>
#include "Core/transporteur.h"
#include "ui_ajouterTransporteur.h"

namespace Gui {
    class AjoutTransporteur : public QDialog, Ui::ajoutTransporteur
    {
        Q_OBJECT
    public:
        explicit AjoutTransporteur(QSqlTableModel *mod,QWidget *parent = 0);
        void initComposant();
        bool champsVides();

    signals:

    public slots:

    private slots:
        void on_btVlider_clicked();

    private:
        QSqlTableModel *model;
        QValidator *validator;

        Core::transporteur *transporteur;
    };
}

#endif // AJOUTTRANSPORTEUR_H
