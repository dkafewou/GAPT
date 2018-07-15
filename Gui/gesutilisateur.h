#ifndef GESUTILISATEUR_H
#define GESUTILISATEUR_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QModelIndexList>
#include "Gui/moduser.h"
#include "Gui/ajoutuser.h"
#include "Core/utilisateur.h"
#include "ui_gesUser.h"

namespace Gui {
    class GesUtilisateur : public QDialog,Ui::GesUser
    {
        Q_OBJECT
    public:
        explicit GesUtilisateur(QWidget *parent = 0);

        void initComposant();

    signals:

    public slots:

    private slots:
        void on_btNouveau_clicked();

        void on_btModifier_clicked();

        void on_userTableView_clicked();

        void on_btDesactiver_clicked();

        void on_btSupprimer_clicked();

        void on_btReactiver_clicked();

        void on_agentEdit_textChanged(const QString &arg1);

        void on_btActualiser_clicked();

        void on_profilComboBox_currentIndexChanged(const QString &arg1);

        void on_comboBox_currentIndexChanged(const QString &arg1);

        void on_btApercu_clicked();

    private:
        QSqlRelationalTableModel *model;
        QModelIndexList liste;

        Gui::AjoutUser *FenUser;
        Gui::ModUser *FenModUser;
        Core::Utilisateur *user;
    };
}

#endif // GESUTILISATEUR_H
