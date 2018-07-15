#ifndef GESREGLEMENT_H
#define GESREGLEMENT_H

#include <QDialog>
#include <QDebug>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QModelIndexList>
#include "Reports/etatnomination.h"
#include "Core/reglement.h"
#include "Gui/modreglement.h"
#include "ui_gesReglement.h"

namespace Gui {
    class gesReglement : public QDialog,Ui::gesReglement
    {
        Q_OBJECT
    public:
        explicit gesReglement(QWidget *parent = 0);
        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btSupprimer_clicked();

        void on_btModifier_clicked();

        void on_transportEdit_textChanged(const QString &arg1);

        void on_dateEdit_dateChanged(const QDate &date);

        void on_reglementTableView_clicked();

        void on_btApercu_clicked();

    private:
        QSqlQueryModel *model,*modelEtat;
        QSqlQuery query;
        QModelIndexList liste;

        Core::Reglement *reglement;
        Gui::ModReglement *FenModRegl;
        Reports::EtatNomination *etat;
    };
}


#endif // GESREGLEMENT_H
