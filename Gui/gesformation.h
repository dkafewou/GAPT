#ifndef GESFORMATION_H
#define GESFORMATION_H

#include <QDialog>
#include <QModelIndexList>
#include <QSqlTableModel>
#include "Gui/ajoutformation.h"
#include "Gui/modifierformation.h"
#include "Core/formation.h"
#include "ui_gesFormation.h"

namespace Gui {
    class GesFormation : public QDialog, Ui::gesFormation
    {
        Q_OBJECT
    public:
        explicit GesFormation(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btNouveau_clicked();
        void on_formationEdit_textChanged(const QString &arg1);
        void on_btInit_clicked();

        void on_villeEdit_textChanged(const QString &arg1);

        void on_FormationTableView_clicked();

        void on_btSupprimer_clicked();

        void on_btModifier_clicked();

    private:
        QSqlTableModel *model;
        QModelIndexList liste;

        Gui::AjoutFormation *FenAjoutForm;
        Gui::ModifierFormation *FenMomForm;
        Core::Formation *formation;
    };
}

#endif // GESFORMATION_H
