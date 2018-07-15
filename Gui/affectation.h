#ifndef AFFECTATION_H
#define AFFECTATION_H

#include <QDialog>
#include "Gui/listeposte.h"
#include "Gui/listeservice.h"
#include "Core/agent.h"
#include "Core/travail.h"
#include "ui_affecterAgent.h"

namespace Gui {
    class Affectation : public QDialog,Ui::affecterAgent
    {
        Q_OBJECT
    public:
        explicit Affectation(Core::Agent *ag,QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btPoste_clicked();

        void on_btService_clicked();

        void on_btValider_clicked();

    private:
        Core::Agent *agent;
        Core::travail *travail,*FinTtravail;
        Gui::ListePoste *FenPoste;
        Gui::ListeService *FenService;
    };
}

#endif // AFFECTATION_H
