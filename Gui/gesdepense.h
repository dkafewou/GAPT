#ifndef GESDEPENSE_H
#define GESDEPENSE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include "Gui/moddepense.h"
#include "Gui/ajoutdepense.h"
#include "Core/depense.h"
#include "ui_gesDepense.h"

namespace Gui {

    class gesDepense : public QDialog,Ui::gesDepense
    {
        Q_OBJECT
    public:
        explicit gesDepense(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btNouveau_clicked();

        void on_btSupprimer_clicked();

        void on_depenseTableView_clicked();

        void on_depenseEdit_textChanged(const QString &arg1);

        void on_btModifier_clicked();

    private:
        QSqlTableModel *model;
        QModelIndexList liste;

        Gui::AjoutDepense *FenDepense;
        Gui::ModDepense *FenModDep;
        Core::Depense *depense;
    };

}

#endif // GESDEPENSE_H
