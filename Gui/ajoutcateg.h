#ifndef AJOUTCATEG_H
#define AJOUTCATEG_H

#include <QDialog>
#include <QValidator>
#include <QSqlTableModel>
#include "ui_ajouterCategorie.h"
#include <Core/categorie.h>

namespace Gui {
    class AjoutCateg : public QDialog, Ui::AjouCateg
    {
        Q_OBJECT
    public:
        explicit AjoutCateg(QSqlTableModel *mod,QWidget *parent = 0);

        bool champsVides();

        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QValidator *validator;
        QSqlTableModel *model;

        Core::Categorie *categorie;
    };
}

#endif // AJOUTCATEG_H
