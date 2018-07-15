#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "Core/connexion.h"
#include "Core/utilisateur.h"
#include "mainwindow.h"
#include "Gui/changerpassword.h"
#include "ui_login.h"

namespace Gui {
    class Login : public QDialog, Ui::DialogLogin
    {
        Q_OBJECT
    public:
        explicit Login(QWidget *parent = 0);
        bool champsVide() ;
        void initComposants() ;
        void raz() ;

    signals:

    public slots:

    private slots:
        void on_btLogin_clicked();

        void on_dial_valueChanged();

    private:
        Core::Utilisateur *user ;
        MainWindow *fenetrePrincipale ;
        Gui::ChangerPassword *FenChPass;
        QPalette paletteRouge ;
        int compteurErreur ;
    };
}

#endif // LOGIN_H
