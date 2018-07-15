#ifndef MODTYPPERM_H
#define MODTYPPERM_H

#include <QDialog>
#include <QSqlTableModel>
#include <QValidator>
#include "Core/typepermission.h"
#include "ui_modTypePermission.h"

namespace Gui {
    class ModTypPerm : public QDialog, Ui::modTypePerm
    {
        Q_OBJECT
    public:
        explicit ModTypPerm(QSqlTableModel *mode,Core::TypePermission *perm,QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QValidator *validator;
        QSqlTableModel *model;
        Core::TypePermission *TypeP,*typePerm;
    };
}

#endif // MODTYPPERM_H
