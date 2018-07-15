#ifndef AJOUTDEPENSE_H
#define AJOUTDEPENSE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QValidator>
#include "Core/depense.h"
#include "ui_ajouterDepense.h"

namespace Gui {
    class AjoutDepense : public QDialog, Ui::ajoutDepense
    {
        Q_OBJECT
    public:
        explicit AjoutDepense(QSqlTableModel *mod, QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QSqlTableModel *model;
        QValidator *validator;

        Core::Depense *depense;
    };
}

#endif // AJOUTDEPENSE_H
