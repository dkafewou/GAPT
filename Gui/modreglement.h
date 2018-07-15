#ifndef MODREGLEMENT_H
#define MODREGLEMENT_H

#include <QDialog>
#include <QValidator>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "Core/reglement.h"
#include "ui_modReglement.h"

namespace Gui {
    class ModReglement : public QDialog, Ui::modReglement
    {
        Q_OBJECT
    public:
        explicit ModReglement(QSqlQuery &q,QSqlQueryModel *mo,Core::Reglement *regl,QString tra,QWidget *parent = 0);
        void initComposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QValidator *validator;
        QSqlQuery &query;
        QSqlQueryModel *model;

        Core::Reglement *reglement;
        Core::Reglement *modReg;
    };
}

#endif // MODREGLEMENT_H
