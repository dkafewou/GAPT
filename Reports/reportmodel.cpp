#include "reportmodel.h"

using namespace Reports;

ReportModel::ReportModel(Core::Agent *agen):
    agent(agen)
{
    config = new Gui::Parametre(0);
    query = new QSqlQuery;
    qu = new QSqlQuery;
    config->lireSalaire();
    KDReports::Report report;

    KDReports::Header& header = report.header( KDReports::OddPages) ;
    KDReports::TextElement entete ;
    entete <<"ELI SONISE SARL";
    entete.setPointSize(40);
    entete.setItalic(true);
    entete.setBold(true);
    header.addElement(entete,Qt::AlignCenter);
    KDReports::TextElement companyAddressElement ;
    companyAddressElement <<"Commissionnaire en Douane Agréée\n"
                          <<"Agrément N° 01910107 par arrêté N° 019/MFBP/AD/DG du 12/02/07\n"
                          <<"Commerce Général - Prestataires de services\n"
                          <<"RCL 3 N° 1998 /B872 du 14/08/06 Quartier Bè Château BP 1598\n"
                          <<"TEL 22 22 76 91 / 22 22 60 90 FAX 22 22 31 86 E-mail : elisonise@yahoo.fr\n"
                          <<"LOME - TOGO";
    header.addElement( companyAddressElement, Qt::AlignCenter );
    header.addElement(KDReports::HLineElement());

    KDReports::Footer& footer = report.footer();
    footer.addElement(KDReports::HLineElement());
    footer.addInlineElement(KDReports::TextElement("\t\t\t\t\t\t Page "));
    footer.addVariable( KDReports::PageNumber );
    footer.addInlineElement( KDReports::TextElement( " / " ) );
    footer.addVariable( KDReports::PageCount );
    footer.addInlineElement( KDReports::TextElement( ", Date: " ) );
    footer.addVariable( KDReports::LocaleDate );
    footer.addInlineElement( KDReports::TextElement( ", Heure: " ) );
    footer.addVariable( KDReports::TextTime );
    footer.addVerticalSpacing(10);

    KDReports::Footer& evenPagesHeader = report.footer( KDReports::EvenPages );
    //evenPagesHeader.addElement( imageElement );
    evenPagesHeader.addInlineElement( KDReports::TextElement( "Even pages header: " ) );
    evenPagesHeader.addVariable( KDReports::PageNumber );
    evenPagesHeader.addInlineElement( KDReports::TextElement( " / " ) );
    evenPagesHeader.addVariable( KDReports::PageCount );

    prime =0;
    query->clear();
    if(query->exec("select SalaireBrute from categorie where CodeCategorie=(select CodeCategorie from agent where IdAgent='"+agent->getIdAgent()+"')")){
        if(query->first())
             brute = query->value(0).toDouble();
    }else query->lastError();

    query->clear();
    query->exec("select  CodeDirection from dirige where IdAgent='"+agent->getIdAgent()+"' and Date_FinD is null");
    if(query->first()){
        qu->exec("select Prime from direction where CodeDirection='"+query->value(0).toString()+"'");
        if(qu->first())
            prime = qu->value(0).toDouble();
    }else query->lastError();

    query->clear();
    query->exec("select  CodeService from Travail where IdAgent='"+agent->getIdAgent()+"' and Date_Fin is null and CodeFonction ='CHS'");
    if(query->first()){
        qu->exec("select PrimeChef from service where CodeService='"+query->value(0).toString()+"'");
        if(qu->first())
            prime =prime+ qu->value(0).toDouble();
    }else query->lastError();

    KDReports::TextElement titleElement;
    titleElement << "BULLETIN DE PAYE";
    titleElement.setPointSize( 18 );
    titleElement.setUnderline(true);
    titleElement.setBold(true);
    report.addElement( titleElement, Qt::AlignHCenter );
    report.addVerticalSpacing( 5 );

    KDReports::TextElement title;
    title <<"Nom :  "+agent->getNomAgent()
          <<"\nPrénom :  "+agent->getPrenomAgent()
          <<"\nSalaire du mois:  "+QDate::longMonthName(QDate::currentDate().month());
    title.setPointSize( 12 );
    title.setBold(true);
    report.addElement( title, Qt::AlignLeft );
    report.addVerticalSpacing( 10 );

    KDReports::TextElement tit;
    tit <<"\t\t          Rubrique\t       Montant";
    tit.setPointSize( 12 );
    tit.setBold(true);
    report.addElement( tit );

    int i = agent->getDateAmb().year()-QDate::currentDate().year();
    Positif = brute+ (brute*config->getConge().toDouble()) + prime + (brute*config->getAvancement().toDouble()*i);
    negatif = brute*config->getSocial().toDouble() + brute*config->getTaxe().toDouble() +config->getAssurance().toDouble();
    KDReports::TextElement tite;
    tite<<"\n\nSalaire brute\t"+QString::number(brute)
        <<"\n\nCNSS\t\t"+QString::number(brute*config->getSocial().toDouble())
        <<"\n\nTaxe\t\t"+QString::number(brute*config->getTaxe().toDouble())
        <<"\n\nAssurance\t\t"+config->getAssurance()
        <<"\n\nCongé Payé\t"+QString::number(brute*config->getConge().toDouble())
        <<"\n\nAvancement\t"+QString::number(brute*config->getAvancement().toDouble()*i)
        <<"\n\n Prime\t\t"+QString::number(prime);
    tite.setPointSize( 12 );
    report.addElement( tite ,Qt::AlignCenter);
    KDReports::TextElement total;
    total <<"\n\n\nSalaire net à recevoir    "+QString::number(Positif-negatif)+"  Francs cfa";
    total.setPointSize( 12 );
    total.setBold(true);
    report.addElement( total, Qt::AlignCenter );
    report.addVerticalSpacing( 25 );

    KDReports::TextElement ti;
    ti <<"Le Directeur Administratif et Financier";
    ti.setPointSize( 12 );
    report.addElement( ti, Qt::AlignRight );

    report.setOrientation(QPrinter::Portrait);
    KDReports::PreviewDialog preview( &report );
    preview.exec();
}

