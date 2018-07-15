#ifndef LISTETRANSPORTEUR_H
#define LISTETRANSPORTEUR_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include "Core/transporteur.h"
#include "ui_listeTransporteur.h"

namespace Gui {
    class ListeTransporteur : public QDialog, Ui::ListeTransporteur
    {
        Q_OBJECT
    public:
        explicit ListeTransporteur(QLineEdit *edi,Core::transporteur *tr, QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_nomEdit_textChanged(const QString &arg1);

        void on_transporteurTableView_clicked();

        void on_btOk_clicked();

    private:
        QLineEdit *edit;
        QSqlTableModel *model;
        QModelIndexList liste;

        Core::transporteur *transporteur;
    };
}

#endif // LISTETRANSPORTEUR_H
