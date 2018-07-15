#ifndef ETATNOMINATION_H
#define ETATNOMINATION_H

#include <QDebug>
#include <QSqlQueryModel>
#include <QString>
#include <KDReports>
#include "Gui/parametre.h"
#include <KDReports>
#include <KDReportsReport.h>
#include <KDReportsTextElement.h>
#include <KDReportsPreviewDialog.h>
#include <QPrintDialog>

namespace Reports {
    class EtatNomination
    {
    public:
        EtatNomination(QString text,QSqlQueryModel *model);

    private:
        Gui::Parametre *config;
    };
}

#endif // ETATNOMINATION_H
