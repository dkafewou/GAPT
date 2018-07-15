#ifndef PARAMETRE_H
#define PARAMETRE_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>
#include <QVariant>
#include <QValidator>
#include "ui_configuration.h"

namespace Gui {
    class Parametre : public QDialog, Ui::DialogConfiguration
    {
        Q_OBJECT
    public:
        explicit Parametre(QWidget *parent = 0);
        void initComposant();

        void initComposantSociete();
        void lireSociete();
        QStringList lireSocieteListe();
        void ecrireSociete();

        void initComposantBd();
        void lireBd();
        void ecrireBd();

        void initComposantSalaire();
        void lireSalaire();
        void ecrireSalaire();

        QString getSteSigle() const;
        void setSteSigle(const QString &value);

        QString getSteNom() const;
        void setSteNom(const QString &value);

        QString getStePays() const;
        void setStePays(const QString &value);

        QString getSteVille() const;
        void setSteVille(const QString &value);

        QString getSteBp() const;
        void setSteBp(const QString &value);

        QString getSteTel() const;
        void setSteTel(const QString &value);

        QString getSteAdesse() const;
        void setSteAdesse(const QString &value);

        QString getSteEmail() const;
        void setSteEmail(const QString &value);

        QString getSteSiteWeb() const;
        void setSteSiteWeb(const QString &value);

        QString getSteLogo() const;
        void setSteLogo(const QString &value);

        QString getAdressBd() const;
        void setAdressBd(const QString &value);

        QString getNomBd() const;
        void setNomBd(const QString &value);

        QString getPortBd() const;
        void setPortBd(const QString &value);

        QString getUserBd() const;
        void setUserBd(const QString &value);

        QString getPassBd() const;
        void setPassBd(const QString &value);

        QString getSocial() const;
        void setSocial(const QString &value);

        QString getTaxe() const;
        void setTaxe(const QString &value);

        QString getAssurance() const;
        void setAssurance(const QString &value);

        QString getConge() const;
        void setConge(const QString &value);

        QString getAvancement() const;
        void setAvancement(const QString &value);

    signals:

    public slots:

    private slots:
        void on_btOk_clicked();

        void on_btOk_2_clicked();

        void on_btOk_3_clicked();

    private:
        QValidator *validator;
        QString steSigle,steNom,stePays,steVille,steBp, steTel ,steAdesse,steEmail,steSiteWeb,steLogo;
        QString adressBd,nomBd,portBd,UserBd,passBd;
        QString social,taxe,assurance,conge,avancement;
    };
}

#endif // PARAMETRE_H
