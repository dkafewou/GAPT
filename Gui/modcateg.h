#ifndef MODCATEG_H
#define MODCATEG_H

#include <QDialog>
#include <QValidator>
#include <QSqlTableModel>
#include "ui_modifierCategorie.h"
#include "Core/categorie.h"

namespace Gui {
    class ModCateg : public QDialog, Ui::modCateg
    {
        Q_OBJECT
    public:
        explicit ModCateg(Core::Categorie *categ,QSqlTableModel *mod,QWidget *parent = 0);
        void initComposant();
        bool champVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        Core::Categorie *categorie;
        Core::Categorie *ModCategorie;

        QValidator *validator;
        QSqlTableModel *model;
    };
}

#endif // MODCATEG_H
