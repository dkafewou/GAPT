#ifndef LISTECATEGORIE_H
#define LISTECATEGORIE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QLineEdit>
#include "ui_listeCategorie.h"
#include "Core/agent.h"
#include <QModelIndexList>

namespace Gui {
    class ListeCategorie : public QDialog, Ui::listeCategorie
    {
        Q_OBJECT
    public:
        explicit ListeCategorie(QLineEdit *edi, Core::Agent *agen, QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_categorieEdit_textChanged(const QString &arg1);

        void on_categorieTableView_clicked();

        void on_btOk_clicked();

    private:
        QModelIndexList liste;
        QSqlTableModel *model;
        QLineEdit *edit;

        Core::Agent *agent;
    };
}

#endif // LISTECATEGORIE_H
