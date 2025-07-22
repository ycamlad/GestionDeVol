#include <QApplication>
#include "Interface/FenetrePrincipal.h"
#include "QDebug"
#include <QtGui>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPixmap pixmap(":/Resources/background.png");

    QIcon icon(":/Resources/iconmonstr-airport-10-240.png");
    //background.load()
    FenetrePrincipal f;
    f.setWindowIcon(icon);
    f.setFixedHeight(775);
    f.setFixedWidth(1018);
    f.setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(f.backgroundRole(),QBrush(pixmap.scaled(f.size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    f.setPalette(palette);
    //f.setStyleSheet("background-image: url(:/Resources/background.jpg);");
//    f.setStyleSheet(R"(background-image: url(:/Resources/iconmonstr-airport-10-24.png);"
//                    "background-repeat: no-repeat;"
//                    "background-position: center;"
//                    "background-size: cover;)");


    f.show();
    return QApplication::exec();
}
