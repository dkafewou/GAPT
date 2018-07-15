#ifndef AJOUTUSER_H
#define AJOUTUSER_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include "Core/utilisateur.h"
#include "Core/agent.h"
#include "Gui/listeagent.h"
#include "ui_ajoutUser.h"

namespace Gui {
    class AjoutUser : public QDialog, Ui::ajoutUser
    {
        Q_OBJECT
    public:
        explicit AjoutUser(QSqlRelationalTableModel *mod,QWidget *parent = 0);
        void initComposnat();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btAgent_clicked();

        void on_btValider_clicked();

    private:
        Gui::ListeAgent *FenListe;
        Core::Agent *agent;
        Core::Utilisateur *user;

        QSqlRelationalTableModel *model;
    };
}

#endif // AJOUTUSER_H
