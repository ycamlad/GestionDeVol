//
// Created by chris on 7/24/2025.
//

#ifndef GESTION_DE_VOL_DATABASEEXCEPTION_H
#define GESTION_DE_VOL_DATABASEEXCEPTION_H

#include "stdexcept"
#include "ContratException.h"
#include "QString"

class DatabaseException: public std::runtime_error {
public:
    explicit DatabaseException(const QString& p_message,const QString& p_raison): runtime_error(p_raison.toStdString()),
                                                                                  m_message(p_message),m_raison(p_raison){}
private:
    QString m_raison;
    QString m_message;
};

#endif //GESTION_DE_VOL_DATABASEEXCEPTION_H
