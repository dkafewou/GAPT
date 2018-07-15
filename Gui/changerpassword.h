#ifndef CHANGERPASSWORD_H
#define CHANGERPASSWORD_H

#include <QDialog>
#include "Core/utilisateur.h"
#include "ui_password.h"

namespace Gui {
    class ChangerPassword : public QDialog, Ui::ChangerPassword
    {
        Q_OBJECT
    public:
        explicit ChangerPassword(Core::Utilisateur *use, QWidget *parent = 0);
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        Core::Utilisateur *user;
    };
}

#endif // CHANGERPASSWORD_H
