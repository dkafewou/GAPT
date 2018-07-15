#ifndef MODFONCTION_H
#define MODFONCTION_H

#include <QDialog>
#include <QSqlTableModel>
#include "Core/fonction.h"
#include "ui_ModFonction.h"

namespace Gui {
    class ModFonction : public QDialog, Ui::ModFonction
    {
        Q_OBJECT
    public:
        explicit ModFonction(QSqlTableModel *mod, Core::Fonction *fonc, QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QSqlTableModel *model;

        Core::Fonction *modFonct;
        Core::Fonction *fonction;
    };
}

#endif // MODFONCTION_H
