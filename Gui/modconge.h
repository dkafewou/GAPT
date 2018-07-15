#ifndef MODCONGE_H
#define MODCONGE_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "Gui/listeagent.h"
#include "Core/conge.h"
#include "Core/agent.h"
#include "Core/typeconge.h"
#include "ui_modConge.h"

namespace Gui {
    class ModConge : public QDialog, Ui::modConge
    {
        Q_OBJECT
    public:
        explicit ModConge(QSqlRelationalTableModel * mod,Core::Conge *Cng,QWidget *parent = 0);
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
        Core::Conge *modCong;
        Gui::ListeAgent *FenListe;
    };
}

#endif // MODCONGE_H
