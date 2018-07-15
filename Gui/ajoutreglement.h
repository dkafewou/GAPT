#ifndef AJOUTREGLEMENT_H
#define AJOUTREGLEMENT_H

#include <QDialog>
#include <QValidator>
#include <QString>
#include "Core/reglement.h"
#include "ui_ajouterReglement.h"

namespace Gui {
    class AjoutReglement : public QDialog, Ui::AjoutReglement
    {
        Q_OBJECT
    public:
        explicit AjoutReglement(QString cont, QString tr,Core::Reglement *regl, QWidget *parent = 0);
        void initComoposant();
        bool champsVide();

    signals:

    public slots:

    private slots:
        void on_btValider_clicked();

    private:
        QValidator *validator;
        Core::Reglement *reglement;
    };
}

#endif // AJOUTREGLEMENT_H
