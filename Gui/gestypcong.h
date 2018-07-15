#ifndef GESTYPCONG_H
#define GESTYPCONG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include "Core/typeconge.h"
#include "Gui/ajouttypconge.h"
#include "Gui/modtypeconge.h"
#include "ui_gesTypeConge.h"

namespace Gui {
    class GesTypCong : public QDialog, Ui::DialogConge
    {
        Q_OBJECT
    public:
        explicit GesTypCong(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btNouveau_clicked();

        void on_btModifier_clicked();

        void on_btSupprimer_clicked();

        void on_typecongeTableView_clicked();

        void on_libelleEdit_textChanged(const QString &arg1);

    private:
        QSqlTableModel *model;
        QModelIndexList liste;

        Gui::ajoutTypConge *FenAjouT;
        Gui::ModTypeConge*FenModCong;
        Core::TypeConge *TypCong;
    };
}

#endif // GESTYPCONG_H
