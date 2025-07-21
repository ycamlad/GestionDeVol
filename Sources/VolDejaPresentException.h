//
// Created by chris on 7/3/2025.
//

#ifndef TP3QT_VOLDEJAPRESENTEXCEPTION_H
#define TP3QT_VOLDEJAPRESENTEXCEPTION_H
#include "VolException.h"

class VolDejaPresentException : public VolException{
public:
    VolDejaPresentException(const std::string &p_raison) : VolException(p_raison) {
        //PRECONDITION(p_raison.empty())
        //POSTCONDITION(m_raison==p_raison);
        //INVARIANTS();
    }

private:
    std::string m_raison;
};


#endif //TP3QT_VOLDEJAPRESENTEXCEPTION_H
