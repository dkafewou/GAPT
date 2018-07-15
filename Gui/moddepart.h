#ifndef MODDEPART_H
#define MODDEPART_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include "Core/depart.h"
#include "ui_modifierdepart.h"

namespace Gui {
    class ModDepart : public QDialog, Ui::modDepart
    {
        Q_OBJECT
    public:
        explicit ModDepart(Core::Depart *dep,QSqlRelationalTableModel *mod,QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        Core::Depart *modDep;
        Core::Depart *depart;

        QSqlTableModel *model;
        QSqlRelationalTableModel *mode;
    };
}

#endif // MODDEPART_H
