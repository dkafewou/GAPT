#ifndef GESTYPEDEPART_H
#define GESTYPEDEPART_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include "Gui/modtypedepart.h"
#include "Gui/ajouttypedep.h"
#include "Core/typedepart.h"
#include "ui_gesTypeDepart.h"

namespace Gui {
    class GesTypeDepart : public QDialog, Ui::gesTypeDepart
    {
        Q_OBJECT
    public:
        explicit GesTypeDepart(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btNouveau_clicked();

        void on_libelleEdit_textChanged(const QString &arg1);

        void on_btModifier_clicked();

        void on_btSupprimer_clicked();

        void on_typedepartTableView_clicked();

    private:
        QSqlTableModel *model;
        QModelIndexList liste;
        Core::TypeDepart *typedep;

        Gui::AjoutTypeDep *FenTypeDep;
        Gui::ModTypeDepart *FenModType;
    };
}

#endif // GESTYPEDEPART_H
