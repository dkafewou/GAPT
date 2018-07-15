#ifndef CONNEXION_H
#define CONNEXION_H

#include <QApplication>

#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtPlugin>
#include <QtSql>
#include <QDebug>
#include "Gui/parametre.h"

namespace Core {
    class Connexion
    {
    public:
         Connexion();
         bool TestCon();
         void remove();
    private:
         Gui::Parametre *parametre;
         QSqlDatabase db;
    };
}

#endif // CONNEXION_H
