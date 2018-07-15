#ifndef AJOUTTYPEDEP_H
#define AJOUTTYPEDEP_H

#include <QDialog>
#include <QSqlTableModel>
#include "Core/typedepart.h"
#include "ui_ajouterTypeDepart.h"

namespace Gui {
    class AjoutTypeDep : public QDialog, Ui::ajoutTypeDepart
    {
        Q_OBJECT
    public:
        explicit AjoutTypeDep(QSqlTableModel *mod,QWidget *parent = 0);
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        Core::TypeDepart *typedep;

        QSqlTableModel *model;
    };
}

#endif // AJOUTTYPEDEP_H
