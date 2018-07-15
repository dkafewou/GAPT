#ifndef GESSANCTION_H
#define GESSANCTION_H

#include <QDialog>
#include <QModelIndexList>
#include <QSqlRelationalTableModel>
#include "ui_gesSanction.h"
#include "Gui/ajoutsanction.h"
#include "Core/sanction.h"
#include "Gui/modifiersanction.h"

namespace Gui {
    class GesSanction : public QDialog, Ui::gesSanction
    {
        Q_OBJECT
    public:
        explicit GesSanction(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btNouveau_clicked();

        void on_agentEdit_textChanged(const QString &arg1);

        void on_btSupprimer_clicked();

        void on_sanctionTableView_clicked();

        void on_btModifier_clicked();

    private:
        Gui::AjoutSanction *FenSanction;
        Core::sanction *Sanction;
        Gui::ModifierSanction *FenModif;

        QModelIndexList liste;
        QSqlRelationalTableModel *model;
    };
}

#endif // GESSANCTION_H
