#ifndef AJOUTDEPART_H
#define AJOUTDEPART_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include "listeagent.h"
#include "Core/agent.h"
#include "Core/depart.h"
#include "Core/utilisateur.h"
#include "ui_ajouterdepart.h"

namespace Gui {
    class AjoutDepart : public QDialog, Ui::ajoutDepart
    {
        Q_OBJECT
    public:
        explicit AjoutDepart(QSqlRelationalTableModel *mod,QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btAgent_clicked();

        void on_btValider_clicked();

    private:
        QSqlTableModel *model;
        QSqlRelationalTableModel *mode;
        Gui::ListeAgent *FenListe;
        Core::Agent *agent;
        Core::Depart *depart;
        Core::Utilisateur *users;
    };
}

#endif // AJOUTDEPART_H
