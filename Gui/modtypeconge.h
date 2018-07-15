#ifndef MODTYPECONGE_H
#define MODTYPECONGE_H

#include <QDialog>
#include <QDialog>
#include <QSqlTableModel>
#include <QValidator>
#include "Core/typeconge.h"
#include "ui_modTypeConge.h"

namespace Gui {
    class ModTypeConge : public QDialog, Ui::modTypeConge
    {
        Q_OBJECT
    public:
        explicit ModTypeConge(Core::TypeConge *typ,QSqlTableModel *mod,QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        Core::TypeConge *TypCong,*modTyp;
        QSqlTableModel *model;
        QValidator *validator;

    };
}

#endif // MODTYPECONGE_H
