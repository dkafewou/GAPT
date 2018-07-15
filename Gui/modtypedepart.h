#ifndef MODTYPEDEPART_H
#define MODTYPEDEPART_H

#include <QDialog>
#include <QSqlTableModel>
#include "Core/typedepart.h"
#include "ui_modtypedepart.h"

namespace Gui {
    class ModTypeDepart : public QDialog ,Ui::modTypeDepart
    {
        Q_OBJECT
    public:
        explicit ModTypeDepart(Core::TypeDepart *type,QSqlTableModel *mod,QWidget *parent = 0);
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        Core::TypeDepart *typedep;
        Core::TypeDepart *modtype;

        QSqlTableModel *model;
    };
}

#endif // MODTYPEDEPART_H
