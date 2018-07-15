#ifndef AJOUTTYPCONGE_H
#define AJOUTTYPCONGE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QValidator>
#include "Core/typeconge.h"
#include "ui_ajouterTypeConge.h"

namespace Gui {
    class ajoutTypConge : public QDialog, Ui::AjouterTypeConge
    {
        Q_OBJECT
    public:
        explicit ajoutTypConge(QSqlTableModel *mode,QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QSqlTableModel *model;
        QValidator *validator;

        Core::TypeConge *TypCong;
    };
}

#endif // AJOUTTYPCONGE_H
