#include <QApplication>
#include <iostream>
#include "Interface/FenetrePrincipal.h"
#include "QDebug"
#include "databasemanager.h"
#include "DataBaseException.h"

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
    //DatabaseManager &db = DatabaseManager::instance();
    //db.connect();
//    try {
//        DatabaseManager &db = DatabaseManager::instance();
//        db.connect();
//        auto ls = db.reqVols("Admin");
//        for(auto &e : ls){
//            std::cout<<"ID: "<<e.first<<"\n";
//            for(auto &x:e.second){
//                for(auto &y : x){
//                    std::cout<<y.toStdString()<<"\n";
//                }
//            }
//        }
//    }catch(DatabaseException &e){
//        qDebug()<<e.what();
//    }

    f.show();
    return QApplication::exec();
}
