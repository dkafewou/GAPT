#ifndef GESCONGE_H
#define GESCONGE_H

#include <QDialog>
#include "Gui/gestypcong.h"
#include "Gui/ajoutconge.h"
#include <QSqlRelationalTableModel>
#include "Reports/etatnomination.h"
#include <QModelIndexList>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "Gui/modconge.h"
#include "Core/conge.h"
#include "ui_gesConge.h"

namespace Gui {
    class GesConge : public QDialog, Ui::gesConge
    {
        Q_OBJECT
    public:
        explicit GesConge(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btType_clicked();

        void on_btNouveau_clicked();

        void on_btModifer_clicked();

        void on_btSupprimer_clicked();

        void on_congeTableView_clicked();

        void on_agentEdit_textChanged(const QString &arg1);

        void on_typeEdit_textChanged(const QString &arg1);

        void on_btPre_clicked();

    private:
        QSqlRelationalTableModel *model;
        QModelIndexList liste;
        QSqlQueryModel *modelEtat;

        Gui::GesTypCong *FenGesTyp;
        Gui::AjoutConge *FenAjoutConge;
        Gui::ModConge *FenModConge;
        Core::Conge *conge;
        Reports::EtatNomination *prevision;
    };
}

#endif // GESCONGE_H
