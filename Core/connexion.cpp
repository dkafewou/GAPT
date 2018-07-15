#include "connexion.h"

using namespace Core;

Connexion::Connexion()
{
}

bool Connexion::TestCon()
{
    //    connection Ã  la database
    parametre = new Gui::Parametre(0);
    parametre->lireBd();

            db = QSqlDatabase::addDatabase("QMYSQL");
            db.setHostName(parametre->getAdressBd());
            db.setPort(parametre->getPortBd().toInt());
            db.setUserName(parametre->getUserBd());
            db.setPassword(parametre->getPassBd());
            db.setDatabaseName(parametre->getNomBd());

            if(db.open())
            {
                qDebug() << "Vous etes connecte a " << db.hostName();
                return true;
            }else{
                qDebug() << "Connexion FAILED.";
                qDebug() << "Driver disponible: " << db.drivers();
                qDebug() << "Driver fonctionnel(QMYSQL): " << db.isDriverAvailable("QMYSQL");
                qDebug() << "numero de l'erreur: " << db.lastError().number();
                qDebug() << "database erreur: " << db.lastError().databaseText();
                qDebug() << "driver erreur: " << db.lastError().driverText();
                qDebug() << "type erreur: " << db.lastError().type();
                return false;
            }
}

void Core::Connexion::remove()
{
     db.close();
}
