#ifndef LISTESERVICE_H
#define LISTESERVICE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndexList>
#include <QMessageBox>
#include "Core/travail.h"
#include "ui_listeService.h"

namespace Gui {
    class ListeService : public QDialog, Ui::listeService
    {
        Q_OBJECT
    public:
        explicit ListeService(QLineEdit *edi,Core::travail *taf,QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_ServiceEdit_textChanged(const QString &arg1);
        void on_serviceTableView_clicked();

        void on_btOk_clicked();

    private:
        QModelIndexList liste;
        QSqlTableModel *modelService;
        QLineEdit *edit;

        Core::travail *travail;
    };
}

#endif // LISTESERVICE_H
