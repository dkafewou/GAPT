#include "parametre.h"

using namespace Gui;

Parametre::Parametre(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    initComposant();
    initComposantSociete();
    initComposantBd();
    initComposantSalaire();
}

void Parametre::initComposant()
{

    validator = new QDoubleValidator(0,999999999,2,this);
    telEdit->setValidator( validator );
    portbdEdit->setValidator(validator);
    bpEdit->setValidator(validator);
    assuranceEdit->setValidator(validator);
    socialEdit->setValidator(validator);
    taxeEdit->setValidator(validator);
    congeEdit->setValidator(validator);
    avEdit->setValidator(validator);
}
//societÃ©
void Parametre::initComposantSociete()
{
    lireSociete();

    sigleEdit->setText(this->getSteSigle());
    nomEdit->setText(this->getSteNom());
    paysEdit->setText(this->getStePays());
    villeEdit->setText(this->getSteVille());
    bpEdit->setText(this->getSteBp());
    telEdit->setText(this->getSteTel());
    adresseEdit->setText(this->getSteAdesse());
    emailEdit->setText(this->getSteEmail());
    sitewebEdit->setText(this->getSteSiteWeb());
}

void Parametre::lireSociete()
{
    QSettings settings("projet","GAPT");
    settings.beginGroup("Societe");
    steSigle=settings.value("sigle").toString();
    steNom=settings.value("nom").toString();
    stePays=settings.value("pays").toString();
    steVille=settings.value("ville").toString();
    steTel=settings.value("Tel").toString();
    steAdesse=settings.value("adresse").toString();
    steBp=settings.value("Bp").toString();
    steEmail=settings.value("email").toString();
    steSiteWeb=settings.value("siteWeb").toString();
    settings.endGroup();
}

QStringList Parametre::lireSocieteListe()
{
    QStringList liste;
    QSettings settings("projets","SogemeProjet");
    settings.beginGroup("Societe");
    steSigle=settings.value("sigle").toString();
    steNom=settings.value("nom").toString();
    stePays=settings.value("pays").toString();
    steVille=settings.value("ville").toString();
    steTel=settings.value("Tel").toString();
    steAdesse=settings.value("adresse").toString();
    steBp=settings.value("Bp").toString();
    steEmail=settings.value("email").toString();
    steSiteWeb=settings.value("siteWeb").toString();
    settings.endGroup();

    liste << steSigle <<steNom <<stePays << steVille << steBp <<steTel << steAdesse << steEmail << steSiteWeb;
    return liste;
}

void Parametre::ecrireSociete()
{
    QSettings settings("projet","GAPT");
    settings.beginGroup("Societe");
    settings.setValue("sigle",sigleEdit->text());
    settings.setValue("nom",nomEdit->text());
    settings.setValue("pays",paysEdit->text());
    settings.setValue("ville",villeEdit->text());
    settings.setValue("Bp",bpEdit->text());
    settings.setValue("Tel",telEdit->text());
    settings.setValue("adresse",adresseEdit->text());
    settings.setValue("email",emailEdit->text());
    settings.setValue("siteWeb",sitewebEdit->text());

    settings.endGroup();
}
//Base de donnÃ©es
void Parametre::initComposantBd()
{
    lireBd();

    adressebdEdit->setText(this->getAdressBd());
    nombdEdit->setText(this->getNomBd());
    portbdEdit->setText(this->getPortBd());
    utilisateurEdit->setText(this->getUserBd());
    motpassebdEdit->setText(this->getPassBd());
}

void Parametre::lireBd()
{
    QSettings settings("projet","GAPT");
    settings.beginGroup("Bd");
    adressBd=settings.value("adresseBd").toString();
    nomBd=settings.value("nomBd").toString();
    portBd=settings.value("portBd").toString();
    UserBd=settings.value("UserBd").toString();
    passBd=settings.value("password").toString();
    settings.endGroup();
}

void Parametre::ecrireBd()
{
    QSettings settings("projet","GAPT");
    settings.beginGroup("Bd");
    settings.setValue("adresseBd",adressebdEdit->text());
    settings.setValue("nomBd",nombdEdit->text());
    settings.setValue("portBd",portbdEdit->text());
    settings.setValue("UserBd",utilisateurEdit->text());
    settings.setValue("password",motpassebdEdit->text());
    settings.endGroup();
}
//Salaire
void Parametre::initComposantSalaire()
{
    lireSalaire();

    socialEdit->setText(this->getSocial());
    taxeEdit->setText(this->getTaxe());
    assuranceEdit->setText(this->getAssurance());
    congeEdit->setText(this->getConge());
    avEdit->setText(this->getAvancement());
}

void Parametre::lireSalaire()
{
    QSettings settings("projet","GAPT");
    settings.beginGroup("Salaire");
    social=settings.value("sociale").toString();
    taxe=settings.value("taxe").toString();
    assurance=settings.value("assurance").toString();
    conge=settings.value("conge").toString();
    avancement=settings.value("avancement").toString();
    settings.endGroup();
}

void Parametre::ecrireSalaire()
{
    QSettings settings("projet","GAPT");
    settings.beginGroup("Salaire");
    settings.setValue("sociale",socialEdit->text());
    settings.setValue("taxe",taxeEdit->text());
    settings.setValue("assurance",assuranceEdit->text());
    settings.setValue("conge",congeEdit->text());
    settings.setValue("avancement",avEdit->text());
    settings.endGroup();
}

QString Parametre::getSocial() const
{
    return social;
}

void Parametre::setSocial(const QString &value)
{
    social = value;
}

QString Parametre::getTaxe() const
{
    return taxe;
}

void Parametre::setTaxe(const QString &value)
{
    taxe = value;
}

QString Parametre::getAssurance() const
{
    return assurance;
}

void Parametre::setAssurance(const QString &value)
{
    assurance = value;
}

QString Parametre::getConge() const
{
    return conge;
}

void Parametre::setConge(const QString &value)
{
    conge = value;
}

QString Parametre::getAvancement() const
{
    return avancement;
}

void Parametre::setAvancement(const QString &value)
{
    avancement = value;
}

QString Parametre::getAdressBd() const
{
    return adressBd;
}

void Parametre::setAdressBd(const QString &value)
{
    adressBd = value;
}

QString Parametre::getNomBd() const
{
    return nomBd;
}

void Parametre::setNomBd(const QString &value)
{
    nomBd = value;
}

QString Parametre::getPortBd() const
{
    return portBd;
}

void Parametre::setPortBd(const QString &value)
{
    portBd = value;
}

QString Parametre::getUserBd() const
{
    return UserBd;
}

void Parametre::setUserBd(const QString &value)
{
    UserBd = value;
}

QString Parametre::getPassBd() const
{
    return passBd;
}

void Parametre::setPassBd(const QString &value)
{
    passBd = value;
}


QString Parametre::getSteSigle() const
{
    return steSigle;
}

void Parametre::setSteSigle(const QString &value)
{
    steSigle = value;
}

QString Parametre::getSteNom() const
{
    return steNom;
}

void Parametre::setSteNom(const QString &value)
{
    steNom = value;
}

QString Parametre::getStePays() const
{
    return stePays;
}

void Parametre::setStePays(const QString &value)
{
    stePays = value;
}

QString Parametre::getSteVille() const
{
    return steVille;
}

void Parametre::setSteVille(const QString &value)
{
    steVille = value;
}

QString Parametre::getSteBp() const
{
    return steBp;
}

void Parametre::setSteBp(const QString &value)
{
    steBp = value;
}

QString Parametre::getSteTel() const
{
    return steTel;
}

void Parametre::setSteTel(const QString &value)
{
    steTel = value;
}

QString Parametre::getSteAdesse() const
{
    return steAdesse;
}

void Parametre::setSteAdesse(const QString &value)
{
    steAdesse = value;
}

QString Parametre::getSteEmail() const
{
    return steEmail;
}

void Parametre::setSteEmail(const QString &value)
{
    steEmail = value;
}

QString Parametre::getSteSiteWeb() const
{
    return steSiteWeb;
}

void Parametre::setSteSiteWeb(const QString &value)
{
    steSiteWeb = value;
}

QString Parametre::getSteLogo() const
{
    return steLogo;
}

void Parametre::setSteLogo(const QString &value)
{
    steLogo = value;
}

void Gui::Parametre::on_btOk_clicked()
{
    int reponse ;
    reponse = QMessageBox::question(this, tr("Enregistrement"),
                                    tr("Paramètres de configuration de l'application\nSi vous êtes sur des données "
                                       "cliquez oui sinon cliquez non"),QMessageBox::No | QMessageBox::Yes ) ;
    if( reponse == QMessageBox::No){
        QMessageBox::information(this, tr("Annulation"), tr("Enregistrement annulé") ) ;
    }
    else {
        ecrireSociete();
        QMessageBox::information(this, tr("Succès"), tr("Enregistrement effectué") ) ;
        this->close() ;
    }
}

void Gui::Parametre::on_btOk_2_clicked()
{
    int reponse ;
    reponse = QMessageBox::question(this, tr("Enregistrement"),
                                    tr("Paramètres de configuration de l'application\nSi vous êtes sur des données "
                                       "cliquez oui sinon cliquez non"),QMessageBox::No | QMessageBox::Yes ) ;
    if( reponse == QMessageBox::No){
        QMessageBox::information(this, tr("Annulation"), tr("Enregistrement annulé") ) ;
    }
    else {
        ecrireBd();
        QMessageBox::information(this, tr("Succès"), tr("Enregistrement effectué") ) ;
        this->close() ;
    }
}

void Gui::Parametre::on_btOk_3_clicked()
{
    int reponse ;
    reponse = QMessageBox::question(this, tr("Enregistrement"),
                                    tr("Paramètres de configuration de l'application\nSi vous êtes sur des données "
                                       "cliquez oui sinon cliquez non"),QMessageBox::No | QMessageBox::Yes ) ;
    if( reponse == QMessageBox::No){
        QMessageBox::information(this, tr("Annulation"), tr("Enregistrement annulé") ) ;
    }
    else {
        ecrireSalaire();
        QMessageBox::information(this, tr("Succès"), tr("Enregistrement effectué") ) ;
        this->close() ;
    }
}
