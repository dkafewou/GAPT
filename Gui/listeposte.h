#ifndef LISTEPOSTE_H
#define LISTEPOSTE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include "Core/travail.h"
#include "ui_listePoste.h"

namespace Gui {
    class ListePoste : public QDialog,Ui::listePoste
    {
        Q_OBJECT
    public:
        explicit ListePoste(QLineEdit *edi,Core::travail *taf,QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_posteEdit_textChanged(const QString &arg1);

        void on_btOk_clicked();

        void on_fonctionTableView_clicked();

    private:
        QSqlTableModel *modelFonction;
        QModelIndexList liste;
        QLineEdit *edit;
        Core::travail *travail;
    };
}

#endif // LISTEPOSTE_H
