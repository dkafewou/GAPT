#ifndef AJOUTAGENT_H
#define AJOUTAGENT_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QValidator>
#include "ui_ajouterAgent.h"
#include "Gui/listeposte.h"
#include "Gui/listeservice.h"
#include "Gui/listecategorie.h"
#include "Core/agent.h"
#include "Core/travail.h"

namespace Gui {
    class AjoutAgent : public QDialog,Ui::ajouterAgent
    {
        Q_OBJECT
    public:
        explicit AjoutAgent(QSqlRelationalTableModel *mod,QWidget *parent = 0);
        void initComposant();
        bool champsVides();

    signals:

    public slots:


    private slots:
        void on_btPoste_clicked();

        void on_btService_clicked();

        void on_btCategorie_clicked();

        void on_datenaissEdit_dateChanged(const QDate &date);

        void on_btValider_clicked();

    private:
        QSqlRelationalTableModel *model;
        QValidator *validator;

        Gui::ListePoste *FenListePoste;
        Gui::ListeService *FenListeService;
        Gui::ListeCategorie *FenListeCategorie;
        Core::Agent *agent;
        Core::travail *travai;
    };
}

#endif // AJOUTAGENT_H
