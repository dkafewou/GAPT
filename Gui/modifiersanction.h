#ifndef MODIFIERSANCTION_H
#define MODIFIERSANCTION_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include "Core/sanction.h"
#include "ui_modifierSanction.h"

namespace Gui {
    class ModifierSanction : public QDialog, Ui::modSanction
    {
        Q_OBJECT
    public:
        explicit ModifierSanction(Core::sanction *Sanc,QSqlRelationalTableModel *mod,QWidget *parent = 0);
        bool champVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        Core::sanction *Sanction;
        Core::sanction *ModSanc;

        QSqlRelationalTableModel *model;      
    };
}

#endif // MODIFIERSANCTION_H
