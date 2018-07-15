#include "mainwindow.h"
#include "Core/connexion.h"
#include "Gui/login.h"
#include "Gui/parametre.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QPlastiqueStyle>
#include "QEventLoop"
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(new QPlastiqueStyle);
    QEventLoop eventLoop;
    QTimer::singleShot (4000, &eventLoop, SLOT(quit()));
    QSplashScreen splash (QPixmap (":/icones/Icones/lo2.gif"));
    splash.show();
    eventLoop.exec ();
    Core::Connexion con;
    if(con.TestCon()){
        Gui::Login FenLog;
        splash.finish(&FenLog);
        FenLog.show();
        return a.exec();
    }
    else {
        QMessageBox::information(0,"Configuration","Configurez les paramètres de base de données pour pouvoir prendre en charge la base.");
        Gui::Parametre FenPar;
        FenPar.showNormal();
        return a.exec();
    }
    return a.exec();
}
