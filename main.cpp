#include <QApplication>
#include "Interface/FenetrePrincipal.h"
#include "QDebug"


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
    palette.setBrush(f.backgroundRole(),QBrush(pixmap.scaled(f.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation)));
    f.setPalette(palette);

    f.show();
    return QApplication::exec();
}
