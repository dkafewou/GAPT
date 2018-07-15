#ifndef GESTYPEPERM_H
#define GESTYPEPERM_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include "Core/typepermission.h"
#include "Gui/modtypperm.h"
#include "Gui/ajouttypperm.h"
#include "ui_gesTypePermission.h"

namespace Gui {
    class GesTypePerm : public QDialog,Ui::gesTypePerm
    {
        Q_OBJECT
    public:
        explicit GesTypePerm(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btNouveau_clicked();

        void on_typepermissionTableView_clicked();

        void on_btModifier_clicked();

        void on_btSupprimer_clicked();

        void on_libelleEdit_textChanged(const QString &arg1);

    private:
        QSqlTableModel *model;
        QModelIndexList liste;

        Gui::AjoutTypPerm *FenAjout;
        Gui::ModTypPerm *FenMod;
        Core::TypePermission *perm;
    };
}

#endif // GESTYPEPERM_H
