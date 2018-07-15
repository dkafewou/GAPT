#ifndef REPORTMODEL_H
#define REPORTMODEL_H

#include <QDebug>
#include <QSqlQuery>
#include <QDate>
#include <QSqlTableModel>
#include <QString>
#include <KDReports>
#include "Core/agent.h"
#include "Core/salaire.h"
#include "Gui/parametre.h"
#include <KDReports>
#include <KDReportsReport.h>
#include <KDReportsTextElement.h>
#include <KDReportsPreviewDialog.h>
#include <QPrintDialog>

namespace Reports {
    class ReportModel
    {
    public:
        ReportModel(Core::Agent *agen);

    private:
        QSqlQuery *query,*qu;
        Gui::Parametre *config;
        Core::Agent *agent;
        QSqlQueryModel *model;

        double brute,prime;
        double Positif,negatif;
    };
}

#endif // REPORTMODEL_H
