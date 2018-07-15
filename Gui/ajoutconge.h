#ifndef AJOUTCONGE_H
#define AJOUTCONGE_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "Gui/listeagent.h"
#include "Core/conge.h"
#include "Core/typeconge.h"
#include "Core/agent.h"
#include "ui_ajouterConge.h"

namespace Gui {
    class AjoutConge : public QDialog, Ui::AjoutConge
    {
        Q_OBJECT
    public:
        explicit AjoutConge(QSqlRelationalTableModel * mod,QWidget *parent = 0);
        void initComposant();
        void initCombo();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_typecongeCombo_currentIndexChanged(const QString &arg1);

        void on_datedebutEdit_dateChanged(const QDate &date);

        void on_btValider_clicked();

        void on_btAgent_clicked();

    private:
        QSqlRelationalTableModel *model;
        QSqlTableModel *mode;

        Core::Agent *agent;
        Core::TypeConge *typP;
        Core::Conge *conge;
        Core::Conge *verif;
        Gui::ListeAgent *FenListe;
    };
}

#endif // AJOUTCONGE_H
