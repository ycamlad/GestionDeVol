#include <QApplication>
#include "Interface/FenetrePrincipal.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    FenetrePrincipal f;
    f.show();
    return QApplication::exec();
}
