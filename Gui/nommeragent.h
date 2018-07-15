#ifndef NOMMERAGENT_H
#define NOMMERAGENT_H

#include <QDialog>
#include <QSqlTableModel>
#include "Core/agent.h"
#include "Core/dirige.h"
#include "ui_nommerAgent.h"

namespace Gui {
    class NommerAgent : public QDialog, Ui::nommerAgent
    {
        Q_OBJECT
    public:
        explicit NommerAgent(Core::Agent *ag,QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QSqlTableModel *model;
        Core::Agent *agent;
        Core::Dirige *diriger;
        Core::Dirige *fdiriger;
    };
}

#endif // NOMMERAGENT_H
