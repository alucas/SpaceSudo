#include <QtGui>
#include "Fenetre.h"

int main(int argc, char *argv[]){

    QApplication app(argc, argv);

    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    Fenetre *fenetre = new Fenetre();
    fenetre->show();

    return app.exec();
}
