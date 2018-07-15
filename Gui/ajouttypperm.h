#ifndef AJOUTTYPPERM_H
#define AJOUTTYPPERM_H

#include <QDialog>
#include <QSqlTableModel>
#include <QValidator>
#include "Core/typepermission.h"
#include "ui_ajouterTypePermission.h"

namespace Gui {
    class AjoutTypPerm : public QDialog, Ui::ajoutTypePerm
    {
        Q_OBJECT
    public:
        explicit AjoutTypPerm(QSqlTableModel *mode,QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QSqlTableModel *model;
        QValidator *validator;

        Core::TypePermission *typePerm;
    };
}

#endif // AJOUTTYPPERM_H
