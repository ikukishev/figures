#include "cfigureregistry.h"

std::map<std::string, void*>* CFigureRegistry::sPointers = 0;

inline bool print()
{
    std::cout<<"bla" << " ";
    return true;
}

bool ss=print();

bool CFigureRegistry::insert(const std::string &name, void *pLoad)
{
    static std::map<std::string, void*> pointers;
    std::map< std::string, void* >::iterator it = pointers.find(name);
    bool result = it == pointers.end() ;
    if ( result )
    {
        //sPointers[ name ] = (void*)(loader); //static_cast<tLoader>( T::load );
        //std::cout << __FUNCTION__ << " : " << name << std::endl;
        pointers.insert(std::pair<std::string, void*>(name, pLoad));
    }

    sPointers = &pointers;

    return result;
}
