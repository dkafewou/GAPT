#ifndef MODTRANSP_H
#define MODTRANSP_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include "Core/transport.h"
#include "ui_modTransport.h"

namespace Gui {
    class ModTransp : public QDialog, Ui::modTransp
    {
        Q_OBJECT
    public:
        explicit ModTransp(QSqlRelationalTableModel *mod,Core::transport *tr,QWidget *parent = 0);
        void initcomposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QSqlRelationalTableModel *model;
        Core::transport *transport;
        Core::transport *modTrans;
    };
}

#endif // MODTRANSP_H
