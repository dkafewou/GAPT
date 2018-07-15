#ifndef REPORTDEPENSE_H
#define REPORTDEPENSE_H

#include <QDebug>
#include <QSqlQuery>
#include <QDate>
#include <QSqlQueryModel>
#include <QString>
#include <KDReports>
#include "Core/dossier.h"
#include "Gui/parametre.h"
#include <KDReports>
#include <KDReportsReport.h>
#include <KDReportsTextElement.h>
#include <KDReportsPreviewDialog.h>
#include <QPrintDialog>

namespace Reports {
    class ReportDepense
    {
    public:
        ReportDepense(Core::Dossier *dos,QSqlQueryModel *model);

    private:
    };
}

#endif // REPORTDEPENSE_H
