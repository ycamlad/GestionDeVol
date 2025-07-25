#include <QApplication>
#include <iostream>
#include <QDialog>
#include "Interface/FenetrePrincipal.h"
#include "QDebug"
#include "databasemanager.h"
#include "DataBaseException.h"
#include "Interface/Login.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QIcon icon(":/Resources/iconmonstr-airport-10-240.png");
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

    Login l;
    l.setWindowIcon(icon);
    l.show();
    return QApplication::exec();
}
