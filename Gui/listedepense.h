#ifndef LISTEDEPENSE_H
#define LISTEDEPENSE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include "Core/depense.h"
#include "ui_listeDepense.h"

namespace Gui {
    class ListeDepense : public QDialog,Ui::listeDepense
    {
        Q_OBJECT
    public:
        explicit ListeDepense(QLineEdit *edi,Core::Depense *dep, QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_depenseEdit_textChanged(const QString &arg1);

        void on_depenseTableView_clicked();

        void on_btOk_clicked();

    private:
        QSqlTableModel *model;
        QModelIndexList liste;
        QLineEdit *edit;
        Core::Depense *depense;
    };
}

#endif // LISTEDEPENSE_H
