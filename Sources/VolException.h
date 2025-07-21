//
// Created by chris on 7/3/2025.
//

#ifndef TP3QT_VOLEXCEPTION_H
#define TP3QT_VOLEXCEPTION_H
#include <stdexcept>
#include "string"
#include "ContratException.h"

class VolException : public std::runtime_error {
public:
    VolException(const std::string &p_raison) : runtime_error(p_raison),m_raison(p_raison){
        //PRECONDITION(p_raison.empty())
        //POSTCONDITION(m_raison==p_raison);
        //INVARIANTS();
    }

    void verifierInvariant() const {
        INVARIANT(!m_raison.empty())
    }
private:
    std::string m_raison;
};



#endif //TP3QT_VOLEXCEPTION_H
