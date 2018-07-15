#include "reportdepense.h"

using namespace Reports;

ReportDepense::ReportDepense(Core::Dossier *dos, QSqlQueryModel *model)
{
    KDReports::Report report;

    KDReports::Header& header = report.header( KDReports::OddPages) ;
    KDReports::TextElement entete ;
    entete <<"ELI SONISE SARL";
    entete.setPointSize(40);
    entete.setItalic(true);
    entete.setBold(true);
    header.addElement(entete,Qt::AlignCenter);
    KDReports::TextElement companyAddressElement ;
    companyAddressElement <<"Commissionnaire en Douane Agr��e\n"
                          <<"Agr�ment N� 01910107 par arr�t� N� 019/MFBP/AD/DG du 12/02/07\n"
                          <<"Commerce G�n�ral - Prestataires de services\n"
                          <<"RCL 3 N� 1998 /B872 du 14/08/06 Quartier B� Ch�teau BP 1598\n"
                          <<"TEL 22 22 76 91 / 22 22 60 90 FAX 22 22 31 86 E-mail : elisonise@yahoo.fr\n"
                          <<"LOME - TOGO";
    header.addElement( companyAddressElement, Qt::AlignCenter );
    header.addElement(KDReports::HLineElement());

    KDReports::Footer& footer = report.footer();
    footer.addElement(KDReports::HLineElement());
    footer.addInlineElement(KDReports::TextElement("\t\t\t\t\t\tPage "));
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


    KDReports::TextElement titleElement;
    titleElement << "Pr�-Facture";
    titleElement.setPointSize( 18 );
    titleElement.setUnderline(true);
    titleElement.setBold(true);
    report.addElement( titleElement, Qt::AlignHCenter );
    report.addVerticalSpacing( 5 );

    KDReports::TextElement client;
    client <<"DOIT : "+dos->getClient();
    client.setPointSize( 12 );
    report.addElement( client, Qt::AlignRight );
    report.addVerticalSpacing( 5 );

    KDReports::TextElement dossier;
    dossier <<"REP N� : "+dos->getRep()
            <<"\nPRE-FACTURE N� : ";
    dossier.setPointSize( 12 );
    report.addElement( dossier, Qt::AlignLeft );
    report.addVerticalSpacing( 10 );

    KDReports::AutoTableElement tableElement(model);

    tableElement.setPadding(2);
    tableElement.setVerticalHeaderVisible(false);
    tableElement.setWidth(160);
    report.addElement( tableElement,Qt::AlignCenter ) ;


    QSqlQuery query;
    query.exec("select sum(MontantReel) from subir where RepDossier='"+dos->getRep()+"'");
    query.first();

    KDReports::TextElement total;
    total <<"\n\nTOTAL DEPENSE\t\t "+query.value(0).toString()+"Francs Cfa";
    total.setPointSize( 12 );
    total.setBold(true);
    report.addElement( total, Qt::AlignLeft );
    report.addVerticalSpacing( 10 );

    report.setOrientation(QPrinter::Portrait);
    KDReports::PreviewDialog preview( &report );
    preview.exec();
}
