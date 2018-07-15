#ifndef AJOUTDIRECTION_H
#define AJOUTDIRECTION_H

#include <QDialog>
#include <QValidator>
#include <QSqlTableModel>
#include "ui_ajouterDirecteur.h"
#include "Core/direction.h"

namespace Gui {
    class AjoutDirection : public QDialog,Ui::ajoutDirection
    {
        Q_OBJECT
    public:
        explicit AjoutDirection(QSqlTableModel *mod,QWidget *parent = 0);
        void initComposant();
        bool champsVides();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QValidator *validator;
        QSqlTableModel *model;

        Core::Direction *direction;
    };
}

#endif // AJOUTDIRECTION_H
