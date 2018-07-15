#ifndef AJOUTFONCTION_H
#define AJOUTFONCTION_H

#include <QDialog>
#include <QSqlTableModel>
#include "ui_ajouterFonction.h"
#include "Core/fonction.h"

namespace Gui {
    class AjoutFonction : public QDialog,Ui::ajoutFonction
    {
        Q_OBJECT
    public:
        explicit AjoutFonction(QSqlTableModel *mod,QWidget *parent = 0);
        bool champsVides();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        Core::Fonction *fonction;

        QSqlTableModel *model;
    };
}

#endif // AJOUTFONCTION_H
