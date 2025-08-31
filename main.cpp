
#include "Interface/FenetrePrincipal.h"
#include "DataBaseException.h"
#include "Interface/Login.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    const QIcon icon(":/Resources/iconmonstr-airport-10-240.png");

    Login l;
    l.setWindowIcon(icon);
    l.show();
    return QApplication::exec();
}
