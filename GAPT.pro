#-------------------------------------------------
#
# Project created by QtCreator 2013-08-30T10:48:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GAPT
TEMPLATE = app

include(C:\DQ\kdab\kdreports\kdreports.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    Core/connexion.cpp \
    Core/agent.cpp \
    Core/categorie.cpp \
    Core/client.cpp \
    Core/conge.cpp \
    Core/conteneur.cpp \
    Core/dirige.cpp \
    Core/depart.cpp \
    Core/depense.cpp \
    Core/direction.cpp \
    Core/dossier.cpp \
    Core/fonction.cpp \
    Core/formation.cpp \
    Core/permission.cpp \
    Core/reglement.cpp \
    Core/typepermission.cpp \
    Core/typedepart.cpp \
    Core/typeconge.cpp \
    Core/travail.cpp \
    Core/transporteur.cpp \
    Core/transport.cpp \
    Core/service.cpp \
    Core/sanction.cpp \
    Core/subir.cpp \
    Core/utilisateur.cpp \
    Core/participant.cpp \
    Gui/gesutilisateur.cpp \
    Gui/gescateg.cpp \
    Gui/ajoutcateg.cpp \
    Gui/gesagent.cpp \
    Gui/gesdepartement.cpp \
    Gui/ajoutagent.cpp \
    Gui/ajoutservice.cpp \
    Gui/ajoutdirection.cpp \
    Gui/ajoutfonction.cpp \
    Gui/gestransporteur.cpp \
    Gui/listeposte.cpp \
    Gui/listeservice.cpp \
    Gui/listecategorie.cpp \
    Gui/gesconge.cpp \
    Gui/gespermission.cpp \
    Gui/gessanction.cpp \
    Gui/gesdepart.cpp \
    Gui/gesformation.cpp \
    Gui/ajoutsanction.cpp \
    Gui/listeagent.cpp \
    Gui/modifiersanction.cpp \
    Gui/modcateg.cpp \
    Gui/gesreglement.cpp \
    Gui/gesdepense.cpp \
    Gui/gesclient.cpp \
    Gui/ajoutformation.cpp \
    Gui/modifierformation.cpp \
    Gui/gestypedepart.cpp \
    Gui/ajouttypedep.cpp \
    Gui/modtypedepart.cpp \
    Gui/ajoutdepart.cpp \
    Gui/moddepart.cpp \
    Gui/ajoutuser.cpp \
    Gui/moduser.cpp \
    Gui/ajoutclient.cpp \
    Gui/modclien.cpp \
    Gui/gesdossier.cpp \
    Gui/ajoutdossier.cpp \
    Gui/login.cpp \
    Gui/changerpassword.cpp \
    Gui/ajouttransporteur.cpp \
    Gui/gestransport.cpp \
    Gui/parametre.cpp \
    Gui/modservice.cpp \
    Gui/moddirection.cpp \
    Gui/modfonction.cpp \
    Gui/ajoutdepense.cpp \
    Gui/moddepense.cpp \
    Gui/listedepense.cpp \
    Gui/ajoutdepdos.cpp \
    Gui/modtranqporteur.cpp \
    Gui/listetransporteur.cpp \
    Gui/ajouttransport.cpp \
    Gui/ajoutreglement.cpp \
    Gui/modtransp.cpp \
    Gui/modreglement.cpp \
    Gui/modagent.cpp \
    Gui/affectation.cpp \
    Gui/nommeragent.cpp \
    Gui/mouvement.cpp \
    Reports/etatnomination.cpp \
    Gui/corbeille.cpp \
    Gui/gestypeperm.cpp \
    Gui/ajouttypperm.cpp \
    Gui/modtypperm.cpp \
    Gui/ajoutpermission.cpp \
    Gui/modpermission.cpp \
    Reports/reportmodel.cpp \
    Gui/gestypcong.cpp \
    Gui/ajouttypconge.cpp \
    Gui/modtypeconge.cpp \
    Gui/ajoutconge.cpp \
    Gui/modconge.cpp \
    Core/salaire.cpp \
    Reports/reportdepense.cpp

HEADERS  += mainwindow.h \
    Core/connexion.h \
    Core/agent.h \
    Core/categorie.h \
    Core/client.h \
    Core/conge.h \
    Core/conteneur.h \
    Core/dirige.h \
    Core/depart.h \
    Core/depense.h \
    Core/direction.h \
    Core/dossier.h \
    Core/fonction.h \
    Core/formation.h \
    Core/permission.h \
    Core/reglement.h \
    Core/typepermission.h \
    Core/typedepart.h \
    Core/typeconge.h \
    Core/travail.h \
    Core/transporteur.h \
    Core/transport.h \
    Core/service.h \
    Core/sanction.h \
    Core/subir.h \
    Core/utilisateur.h \
    Core/participant.h \
    Gui/gesutilisateur.h \
    Gui/gescateg.h \
    Gui/ajoutcateg.h \
    Gui/gesagent.h \
    Gui/gesdepartement.h \
    Gui/ajoutagent.h \
    Gui/ajoutservice.h \
    Gui/ajoutdirection.h \
    Gui/ajoutfonction.h \
    Gui/gestransporteur.h \
    Gui/listeposte.h \
    Gui/listeservice.h \
    Gui/listecategorie.h \
    Gui/gesconge.h \
    Gui/gespermission.h \
    Gui/gessanction.h \
    Gui/gesdepart.h \
    Gui/gesformation.h \
    Gui/ajoutsanction.h \
    Gui/listeagent.h \
    Gui/modifiersanction.h \
    Gui/modcateg.h \
    Gui/gesreglement.h \
    Gui/gesdepense.h \
    Gui/gesclient.h \
    Gui/ajoutformation.h \
    Gui/modifierformation.h \
    Gui/gestypedepart.h \
    Gui/ajouttypedep.h \
    Gui/modtypedepart.h \
    Gui/ajoutdepart.h \
    Gui/moddepart.h \
    Gui/ajoutuser.h \
    Gui/moduser.h \
    Gui/ajoutclient.h \
    Gui/modclien.h \
    Gui/gesdossier.h \
    Gui/ajoutdossier.h \
    Gui/login.h \
    Gui/changerpassword.h \
    Gui/ajouttransporteur.h \
    Gui/gestransport.h \
    Gui/parametre.h \
    Gui/modservice.h \
    Gui/moddirection.h \
    Gui/modfonction.h \
    Gui/ajoutdepense.h \
    Gui/moddepense.h \
    Gui/listedepense.h \
    Gui/ajoutdepdos.h \
    Gui/modtranqporteur.h \
    Gui/listetransporteur.h \
    Gui/ajouttransport.h \
    Gui/ajoutreglement.h \
    Gui/modtransp.h \
    Gui/modreglement.h \
    Gui/modagent.h \
    Gui/affectation.h \
    Gui/nommeragent.h \
    Gui/mouvement.h \
    Reports/etatnomination.h \
    Gui/corbeille.h \
    Gui/gestypeperm.h \
    Gui/ajouttypperm.h \
    Gui/modtypperm.h \
    Gui/ajoutpermission.h \
    Gui/modpermission.h \
    Reports/reportmodel.h \
    Gui/gestypcong.h \
    Gui/ajouttypconge.h \
    Gui/modtypeconge.h \
    Gui/ajoutconge.h \
    Gui/modconge.h \
    Core/salaire.h \
    Reports/reportdepense.h

FORMS    += mainwindow.ui \
    Ui/gesUser.ui \
    Ui/gesCategorie.ui \
    Ui/ajouterCategorie.ui \
    Ui/gesAgent.ui \
    Ui/gesDepartement.ui \
    Ui/ajouterService.ui \
    Ui/ajouterFonction.ui \
    Ui/ajouterDirecteur.ui \
    Ui/gesTransporteur.ui \
    Ui/listePoste.ui \
    Ui/listeService.ui \
    Ui/listeCategorie.ui \
    Ui/ajouterAgent.ui \
    Ui/gesSanction.ui \
    Ui/gesPermission.ui \
    Ui/gesFormation.ui \
    Ui/gesDepart.ui \
    Ui/gesConge.ui \
    Ui/ajouterSanction.ui \
    Ui/listeAgent.ui \
    Ui/modifierSanction.ui \
    Ui/modifierCategorie.ui \
    Ui/gesReglement.ui \
    Ui/gesDepense.ui \
    Ui/gesClient.ui \
    Ui/ajouterFormation.ui \
    Ui/modifierFormation.ui \
    Ui/gesTypeDepart.ui \
    Ui/ajouterTypeDepart.ui \
    Ui/modtypedepart.ui \
    Ui/ajouterdepart.ui \
    Ui/modifierdepart.ui \
    Ui/ajoutUser.ui \
    Ui/modUser.ui \
    Ui/ajouterClient.ui \
    Ui/modClient.ui \
    Ui/gesDossier.ui \
    Ui/ajoutDossier.ui \
    Ui/login.ui \
    Ui/password.ui \
    Ui/ajouterTransporteur.ui \
    Ui/gesTransport.ui \
    Ui/configuration.ui \
    Ui/ModService.ui \
    Ui/ModDirecteur.ui \
    Ui/ModFonction.ui \
    Ui/ajouterDepense.ui \
    Ui/ModDepense.ui \
    Ui/listeDepense.ui \
    Ui/ajoutDepDos.ui \
    Ui/ModTransporteur.ui \
    Ui/listeTransporteur.ui \
    Ui/ajouterTransport.ui \
    Ui/ajouterReglement.ui \
    Ui/modTransport.ui \
    Ui/modReglement.ui \
    Ui/modAgent.ui \
    Ui/affecterAgent.ui \
    Ui/nommerAgent.ui \
    Ui/mouvement.ui \
    Ui/corbeille.ui \
    Ui/gesTypePermission.ui \
    Ui/ajouterTypePermission.ui \
    Ui/modTypePermission.ui \
    Ui/ajouterPermission.ui \
    Ui/modPermission.ui \
    Ui/gesTypeConge.ui \
    Ui/ajouterTypeConge.ui \
    Ui/modTypeConge.ui \
    Ui/ajouterConge.ui \
    Ui/modConge.ui

RESOURCES += \
    Res.qrc














































