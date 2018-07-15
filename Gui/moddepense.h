#ifndef MODDEPENSE_H
#define MODDEPENSE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QValidator>
#include "Core/depense.h"
#include "ui_ModDepense.h"

namespace Gui {
    class ModDepense : public QDialog, Ui::ModDepense
    {
        Q_OBJECT
    public:
        explicit ModDepense(QSqlTableModel *mod, Core::Depense *dep, QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QSqlTableModel *model;
        QValidator *validator;

        Core::Depense *modDep;
        Core::Depense *depense;
    };
}

#endif // MODDEPENSE_H
