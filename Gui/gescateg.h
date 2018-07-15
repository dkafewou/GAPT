#ifndef GESCATEG_H
#define GESCATEG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include "ui_gesCategorie.h"
#include "Gui/ajoutcateg.h"
#include "Gui/modcateg.h"
#include "Core/categorie.h"

namespace Gui {
    class GesCateg : public QDialog, Ui::GesCategorie
    {
        Q_OBJECT
    public:
        explicit GesCateg(QWidget *parent = 0);

        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btNouveau_clicked();

        void on_libelleEdit_textChanged(const QString &arg1);

        void on_categorieTableView_clicked();

        void on_btModifier_clicked();

        void on_btSupprimer_clicked();

    private:
        QSqlTableModel *model;
        QModelIndexList liste;

        Gui::AjoutCateg *FenAjoutCateg;
        Gui::ModCateg *FenModCateg;
        Core::Categorie *categorie;

    };
}

#endif // GESCATEG_H
