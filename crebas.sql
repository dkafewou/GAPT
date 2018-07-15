/*==============================================================*/
/* DBMS name:      MySQL 5.0                                    */
/* Created on:     27/08/2013 10:06:23                          */
/*==============================================================*/


drop table if exists Agent;

drop table if exists Categorie;

drop table if exists Client;

drop table if exists Conge;

drop table if exists Conteneur;

drop table if exists DIRIGE;

drop table if exists Depart;

drop table if exists Depense;

drop table if exists Direction;

drop table if exists Dossier;

drop table if exists Fonction;

drop table if exists Formation;

drop table if exists PARTICIPANT;

drop table if exists Permission;

drop table if exists Reglement;

drop table if exists SUBIR;

drop table if exists Sanction;

drop table if exists Salaire;

drop table if exists Service;

drop table if exists TRAVAIL;

drop table if exists Transport;

drop table if exists Transporteur;

drop table if exists TypeConge;

drop table if exists TypeDepart;

drop table if exists TypePermission;

drop table if exists Utilisateur;

/*==============================================================*/
/* Table: Agent                                                 */
/*==============================================================*/
create table Agent
(
   IdAgent              varchar(20) not null,
   CodeCategorie        varchar(15) not null,
   NomAgent             varchar(50) not null,
   PrenomAgent          varchar(50) not null,
   SexeAgent            varchar(10) not null,
   DateNaiss            date not null,
   Nationalite			varchar(25) not null,
   Situation			varchar(15) not null,
   Diplome				varchar(60) not null,
   Niveau				varchar(10) not null,
   TelAgent             varchar(20),
   AdrAgent             varchar(50) not null,
   DateEmbauche         date not null,
   SupprAgent           bool,
   primary key (IdAgent)
);

/*==============================================================*/
/* Table: Categorie                                             */
/*==============================================================*/
create table Categorie
(
   CodeCategorie        varchar(15) not null,
   LibelleCategorie     varchar(30) not null,
   SalaireBrute         numeric(8,0) not null,
   SupprCategorie       bool,
   primary key (CodeCategorie)
);

/*==============================================================*/
/* Table: Client                                                */
/*==============================================================*/
create table Client
(
   CodeClient           varchar(10) not null,
   NomClient            varchar(50) not null,
   TelClient            varchar(20) not null,
   AdresseClient        varchar(100) not null,
   Pays                 varchar(20),
   Ville                varchar(20),
   SupprClient          bool,
   primary key (CodeClient)
);

/*==============================================================*/
/* Table: Conge                                                 */
/*==============================================================*/
create table Conge
(
   CodeConge            varchar(10) not null,
   IdAgent              varchar(20) not null,
   CodeTypeConge        varchar(10) not null,
   MotifConge           varchar(100) not null,
   DateDebut            date,
   DateFin              date,
   DateRetourEffect     date,
   SupprConge           bool,
   primary key (CodeConge)
);

/*==============================================================*/
/* Table: Conteneur                                             */
/*==============================================================*/
create table Conteneur
(
   CodeConteneur        varchar(20) not null,
   RepDossier           varchar(15) not null,
   NumeroCont           varchar(25) not null,
   Marchandise          varchar(50) not null,
   Type                 varchar(10) not null,
   SupprConteneur       bool,
   primary key (CodeConteneur)
);

/*==============================================================*/
/* Table: DIRIGE                                                */
/*==============================================================*/
create table DIRIGE
(
   IdAgent              varchar(20) not null,
   CodeDirection        varchar(10) not null,
   Date_Deb             date		not null,
   Date_FinD            date,
   SupprD				bool,
   primary key (IdAgent, CodeDirection,Date_Deb)
);

/*==============================================================*/
/* Table: Depart                                                */
/*==============================================================*/
create table Depart
(
   CodeDepart           varchar(10) not null,
   CodeTypeDepart       varchar(10) not null,
   IdAgent              varchar(20) not null,
   MotifDepart          varchar(100),
   DateDepart           date not null,
   SupprDepart          bool,
   primary key (CodeDepart)
);

/*==============================================================*/
/* Table: Depense                                               */
/*==============================================================*/
create table Depense
(
   CodeDepense          varchar(10) not null,
   Libelle              varchar(50) not null,
   MontantDep           numeric(8,0) not null,
   SupprDep             bool,
   primary key (CodeDepense)
);

/*==============================================================*/
/* Table: Direction                                             */
/*==============================================================*/
create table Direction
(
   CodeDirection        varchar(10) not null,
   LibelleDirection     varchar(50) not null,
   Prime                numeric(8,0) not null,
   SupprDirection       bool,
   primary key (CodeDirection)
);

/*==============================================================*/
/* Table: Dossier                                               */
/*==============================================================*/
create table Dossier
(
   RepDossier           varchar(15) not null,
   CodeClient           varchar(10) not null,
   DateReception        date not null,
   DateArrive           date not null,
   SupprDossier         bool,
   primary key (RepDossier)
);

/*==============================================================*/
/* Table: Fonction                                              */
/*==============================================================*/
create table Fonction
(
   CodeFonction         varchar(10) not null,
   LibelleFonction      varchar(50) not null,
   SupprFonction        bool,
   primary key (CodeFonction)
);

/*==============================================================*/
/* Table: Formation                                             */
/*==============================================================*/
create table Formation
(
   CodeFormation        varchar(10) not null,
   LibelleFormation     varchar(50) not null,
   Ville                varchar(20),
   Pays                 varchar(20),
   DateDebut            date,
   DateFin              date,
   DateFinEffectif      date,
   SupprFormation       bool,
   primary key (CodeFormation)
);

/*==============================================================*/
/* Table: PARTICIPANT                                           */
/*==============================================================*/
create table PARTICIPANT
(
   CodeFormation        varchar(10) not null,
   IdAgent              varchar(20) not null,
   SupprPart		    bool,
   primary key (CodeFormation, IdAgent)
);

/*==============================================================*/
/* Table: Permission                                            */
/*==============================================================*/
create table Permission
(
   CodePermission       varchar(10) not null,
   IdAgent              varchar(20) not null,
   CodeTypepermission   varchar(10) not null,
   MotifPermission      varchar(50),
   DateDebut            date not null,
   DateFin              date not null,
   DateRetourEffect     date,
   SupprPermission      bool,
   primary key (CodePermission)
);

/*==============================================================*/
/* Table: Reglement                                             */
/*==============================================================*/
create table Reglement
(
   CodeRegl             varchar(10) not null,
   CodeTransp           varchar(10) not null,
   DateRegl             date not null,
   HeureRegl            time,
   MontantRegl          numeric(8,0) not null,
   SupprRegl            bool,
   primary key (CodeRegl)
);

/*==============================================================*/
/* Table: SUBIR                                                 */
/*==============================================================*/
create table SUBIR
(
   RepDossier           varchar(15) not null,
   IdAgent              varchar(20) not null,
   CodeDepense          varchar(10) not null,
   DateDepense          date not null,
   HeureDepense         time,
   MontantReel          numeric(8,0) not null,
   supprSubir			bool,
   primary key (RepDossier, IdAgent, CodeDepense)
);

/*==============================================================*/
/* Table: Salaire                                              */
/*==============================================================*/
create table Salaire
(
   CodeSalaire          varchar(10) not null,
   IdAgent              varchar(20) not null,
   DateSal				date not null,
   SalBrute             numeric(8,0) not null,
   MontantCNSS          numeric(8,0) not null,
   MontantTaxe          numeric(8,0) not null,
   MontantAssurance     numeric(8,0) not null,
   MontantCongP         numeric(8,0) not null,
   MontantAv            numeric(8,0) not null,
   MontantPrime         numeric(8,0) not null,
   SupprSal             bool,
   primary key (CodeSalaire)
);

/*==============================================================*/
/* Table: Sanction                                              */
/*==============================================================*/
create table Sanction
(
   CodeSanction         varchar(10) not null,
   IdAgent              varchar(20) not null,
   MotifSanction        varchar(100) not null,
   DateSanction         date not null,
   SupprSanction        bool,
   primary key (CodeSanction)
);

/*==============================================================*/
/* Table: Service                                               */
/*==============================================================*/
create table Service
(
   CodeService          varchar(10) not null,
   LibelleService       varchar(50) not null,
   PrimeChef            numeric(8,0) not null,
   SupprService         bool,
   primary key (CodeService)
);

/*==============================================================*/
/* Table: TRAVAIL                                               */
/*==============================================================*/
create table TRAVAIL
(
   IdAgent              varchar(20) not null,
   CodeFonction         varchar(10) not null,
   CodeService          varchar(10) not null,
   Date_Debut           date not null,
   Date_Fin             date,
   primary key (IdAgent, CodeFonction, CodeService)
);

/*==============================================================*/
/* Table: Transport                                             */
/*==============================================================*/
create table Transport
(
   CodeTransp           varchar(10) not null,
   CodeConteneur        varchar(10) not null,
   CodeTransporteur     varchar(10) not null,
   DateTransp           date not null,
   DateRetour           date,
   SupprTransp          bool,
   primary key (CodeTransp)
);

/*==============================================================*/
/* Table: Transporteur                                          */
/*==============================================================*/
create table Transporteur
(
   CodeTransporteur     varchar(10) not null,
   NomTransporteur      varchar(20) not null,
   PrenomTransporteur   varchar(30),
   TelTransporteur      varchar(20) not null,
   AdresseTransporteur  varchar(50) not null,
   SupprTransporteur    bool,
   primary key (CodeTransporteur)
);

/*==============================================================*/
/* Table: TypeConge                                             */
/*==============================================================*/
create table TypeConge
(
   CodeTypeConge        varchar(10) not null,
   LibelleConge         varchar(30) not null,
   NbreJours            integer not null,
   SupprTypeConge       bool,
   primary key (CodeTypeConge)
);

/*==============================================================*/
/* Table: TypeDepart                                            */
/*==============================================================*/
create table TypeDepart
(
   CodeTypeDepart       varchar(10) not null,
   LibelleDepart        varchar(30) not null,
   SupprTypeDepart      bool,
   primary key (CodeTypeDepart)
);

/*==============================================================*/
/* Table: TypePermission                                        */
/*==============================================================*/
create table TypePermission
(
   CodeTypepermission   varchar(10) not null,
   LibellePermission    varchar(30) not null,
   NbreJours            integer not null,
   SupprTypePermission  bool,
   primary key (CodeTypepermission)
);

/*==============================================================*/
/* Table: Utilisateur                                           */
/*==============================================================*/
create table Utilisateur
(
   IdUtilisateur        varchar(10) not null,
   IdAgent              varchar(20) not null,
   Pseudo               varchar(20) not null,
   Password             varchar(30) not null,
   Profil               varchar(20) not null,
   DateCreation         date not null,
   SupprUser            bool,
   primary key (IdUtilisateur)
);

alter table Agent add constraint FK_AVOIR foreign key (CodeCategorie)
      references Categorie (CodeCategorie) on delete cascade on update cascade;

alter table Conge add constraint FK_CONGETYPECONGE foreign key (CodeTypeConge)
      references TypeConge (CodeTypeConge) on delete cascade on update cascade;

alter table Conge add constraint FK_PARTIR foreign key (IdAgent)
      references Agent (IdAgent) on delete cascade on update cascade;

alter table Conteneur add constraint FK_CONTIENT foreign key (RepDossier)
      references Dossier (RepDossier) on delete cascade on update cascade;

alter table DIRIGE add constraint FK_DIRIGE foreign key (IdAgent)
      references Agent (IdAgent) on delete cascade on update cascade;

alter table DIRIGE add constraint FK_DIRIGE_Dir foreign key (CodeDirection)
      references Direction (CodeDirection) on delete cascade on update cascade;

alter table Depart add constraint FK_CONCERNE foreign key (CodeTypeDepart)
      references TypeDepart (CodeTypeDepart) on delete cascade on update cascade;

alter table Depart add constraint FK_EFFECTUER foreign key (IdAgent)
      references Agent (IdAgent) on delete cascade on update cascade;

alter table Dossier add constraint FK_REMET foreign key (CodeClient)
      references Client (CodeClient) on delete cascade on update cascade;

alter table PARTICIPANT add constraint FK_PARTICIPANT foreign key (IdAgent)
      references Agent (IdAgent) on delete cascade on update cascade;

alter table PARTICIPANT add constraint FK_PARTICIPANT_Form foreign key (CodeFormation)
      references Formation (CodeFormation) on delete cascade on update cascade;

alter table Permission add constraint FK_AGENT_PERM foreign key (IdAgent)
      references Agent (IdAgent) on delete cascade on update cascade;

alter table Permission add constraint FK_PERM_TYP foreign key (CodeTypepermission)
      references TypePermission (CodeTypepermission) on delete cascade on update cascade;

alter table Reglement add constraint FK_REGLE foreign key (CodeTransp)
      references Transport (CodeTransp) on delete cascade on update cascade;

alter table SUBIR add constraint FK_SUBIR foreign key (IdAgent)
      references Agent (IdAgent) on delete cascade on update cascade;

alter table SUBIR add constraint FK_SUBIR_1 foreign key (CodeDepense)
      references Depense (CodeDepense) on delete cascade on update cascade;

alter table SUBIR add constraint FK_SUBIR_2 foreign key (RepDossier)
      references Dossier (RepDossier) on delete cascade on update cascade;
	  
alter table Salaire add constraint FK_Bulletin foreign key (IdAgent)
      references Agent (IdAgent) on delete cascade on update cascade;

alter table Sanction add constraint FK_RECEVOIR foreign key (IdAgent)
      references Agent (IdAgent) on delete cascade on update cascade;

alter table TRAVAIL add constraint FK_TRAVAIL foreign key (IdAgent)
      references Agent (IdAgent) on delete cascade on update cascade;

alter table TRAVAIL add constraint FK_TRAVAIL_1 foreign key (CodeFonction)
      references Fonction (CodeFonction) on delete cascade on update cascade;

alter table TRAVAIL add constraint FK_TRAVAIL_2 foreign key (CodeService)
      references Service (CodeService) on delete cascade on update cascade;

alter table Transport add constraint FK_TRANSPORTE foreign key (CodeTransporteur)
      references Transporteur (CodeTransporteur) on delete cascade on update cascade;

alter table Transport add constraint FK_TRANSPORTER foreign key (CodeConteneur)
      references Conteneur (CodeConteneur) on delete cascade on update cascade;

alter table Utilisateur add constraint FK_ETRE foreign key (IdAgent)
      references Agent (IdAgent) on delete cascade on update cascade;

INSERT INTO `categorie` (`CodeCategorie`,`LibelleCategorie`,`SalaireBrute`,`SupprCategorie`) VALUES ('INF','Informatique','100000',0),('INT1','Informatique','120000',0),('TRT1','Transitaire categorie1','85000',0);

INSERT INTO `agent` (`IdAgent`,`CodeCategorie`,`NomAgent`,`PrenomAgent`,`SexeAgent`,`DateNaiss`,`Nationalite`,`Situation`,`Diplome`,`Niveau`,`TelAgent`,`AdrAgent`,`DateEmbauche`,`SupprAgent`) VALUES ('AFE-Kod-001','TRT1','AFEWOU','Kodjo Désiré','Masculin','1991-09-02','Togo','Célibataire','Ingenieur','BAC+3','90043064','Avenou Rue 22 maison10','2013-09-09',0),('EPE-Kom-003','TRT1','EPEH','Komi','Masculin','1978-09-10','Togo','Marié(e)','Licence en Comptabilité','BAC+2','22897632','Bè Rue 5 Maison7	','2013-09-10',1),('KAN-Kof-004','TRT1','KANGNI','Koffi','Masculin','1975-09-17','Togo','Marié(e)','Transitaire','BAC','786543333','Bè Chateau','2013-09-17',0),('KUD-Fab-002','TRT1','KUDJOH','Fabrice','Masculin','1988-08-24','Togo','Célibataire','Ingenieur','BAC+3','90397541','Nyekonakpoe Rue 22 maison10','2013-09-09',0);

INSERT INTO `utilisateur` (`IdUtilisateur`,`IdAgent`,`Pseudo`,`Password`,`Profil`,`DateCreation`,`SupprUser`) VALUES ('User01','AFE-Kod-001','dkafewou','desiredoreen','Admin','2013-09-17',0),('User02','KUD-Fab-002','fabr22','liliane','Chef Personel','2013-09-17',0),('User03','KAN-Kof-004','kangni','Elisonise2013','Caisse','2013-09-17',0);
