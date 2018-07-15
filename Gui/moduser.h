#ifndef MODUSER_H
#define MODUSER_H

#include <QDialog>
#include "Core/utilisateur.h"
#include <QSqlRelationalTableModel>
#include "ui_modUser.h"

namespace Gui {
    class ModUser : public QDialog, Ui::modUser
    {
        Q_OBJECT
    public:
        explicit ModUser(QSqlRelationalTableModel *mod,Core::Utilisateur *use, QWidget *parent = 0);
        void initcompsant();
        bool champsVides();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QSqlRelationalTableModel *model;

        Core::Utilisateur *user;
        Core::Utilisateur *modUse;
    };
}

#endif // MODUSER_H
