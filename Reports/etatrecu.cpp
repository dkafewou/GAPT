#include "etatrecu.h"

using namespace Reports;

EtatRecu::EtatRecu()
{
    KDReports::Report report;

    KDReports::Header& header = report.header( KDReports::OddPages) ;
    header.addVerticalSpacing(5);
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
    footer.addInlineElement(KDReports::TextElement("\t\t\t\t\t\t\t\t\t Page "));
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
    titleElement << "Reçu";
    titleElement.setPointSize( 18 );
    titleElement.setUnderline(true);
    titleElement.setBold(true);
    report.addElement( titleElement, Qt::AlignHCenter );

    report.addVerticalSpacing( 5 );


    KDReports::AutoTableElement tableElement();

    tableElement.setPadding(2);
    tableElement.setVerticalHeaderVisible(false);
    tableElement.setWidth(200);

    report.addElement( tableElement,Qt::AlignCenter ) ;
    report.setOrientation(QPrinter::Landscape);
    KDReports::PreviewDialog preview( &report );
    preview.exec();
}
