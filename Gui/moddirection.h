#ifndef MODDIRECTION_H
#define MODDIRECTION_H

#include <QDialog>
#include <QValidator>
#include <QSqlTableModel>
#include "core/direction.h"
#include "ui_ModDirecteur.h"

namespace Gui {
    class ModDirection : public QDialog, Ui::ModDirection
    {
        Q_OBJECT
    public:
        explicit ModDirection(QSqlTableModel *mod, Core::Direction *dir, QWidget *parent = 0);
        void initComposant();
        bool champsVides();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QSqlTableModel *model;
        QValidator *validator;

        Core::Direction *modDirect;
        Core::Direction *direction;
    };
}

#endif // MODDIRECTION_H
