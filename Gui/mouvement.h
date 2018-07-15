#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QSqlQueryModel>
#include <QModelIndexList>
#include "Reports/etatnomination.h"
#include "ui_mouvement.h"

namespace Gui {
    class Mouvement : public QDialog, Ui::mouvement
    {
        Q_OBJECT
    public:
        explicit Mouvement(QWidget *parent = 0);
        void initAffectation();
        void initNomination();

    signals:

    public slots:

    private slots:
        void on_agenEdit_textChanged(const QString &arg1);

        void on_directionEdit_textChanged(const QString &arg1);

        void on_agentEdit_textChanged(const QString &arg1);

        void on_fonctionEdit_textChanged(const QString &arg1);

        void on_serviceEdit_textChanged(const QString &arg1);

        void on_btApercu_clicked();

        void on_btAper_clicked();

    private:
        QSqlRelationalTableModel *modelAfec;
        QSqlRelationalTableModel *modelNom;
        QSqlQueryModel *modelEtat;
        QModelIndexList listeA;
        QModelIndexList listeN;

        Reports::EtatNomination *etat;
    };
}

#endif // MOUVEMENT_H
