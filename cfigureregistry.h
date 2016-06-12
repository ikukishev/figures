#ifndef CFIGUREREGISTRY_H
#define CFIGUREREGISTRY_H

#include <QJsonObject>
#include <string>
#include <iostream>
#include <map>
#include <typeinfo>
#include <memory>

#define DECLARE_FIGURE \
public: \
    virtual const std::string type() const { return __static_type_name__; } \
private: \
    static std::string __static_type_name__;


#define REGISTER_FIGURE( __class_name ) std::string __class_name::__static_type_name__ = CFigureRegistry::registerLoad<__class_name>();

class CFigureRegistry
{
public:

    template<typename T>
    class tFigPointer
    {
        friend class CFigureRegistry;

        typedef std::shared_ptr<T>(*tLoader)(const QJsonObject&);
    private:
        tLoader mLoader;

    public:
        tFigPointer()
            : mLoader(nullptr)
        {}

        tFigPointer(tLoader loader)
            : mLoader(loader)
        {}

        std::shared_ptr<T> operator()(const QJsonObject& object)
        {
            if (mLoader == nullptr)
            {
                return nullptr;
            }
            return mLoader(object);
        }

        operator bool()
        {
            return mLoader == nullptr;
        }

    };

private:
    CFigureRegistry();
    CFigureRegistry(const CFigureRegistry&);
    ~CFigureRegistry();

    static std::map<std::string, void*> *sPointers;

    static bool insert(const std::string& name, void* pLoad);

public:


    template<typename T>
    static std::string registerLoad()
    {
        typename tFigPointer<T>::tLoader loader = T::load;

        const std::type_info& typeInfo = typeid(T);
        std::string name( typeInfo.name() );
        /*
        std::map< std::string, void* >::iterator it = sPointers.find(name);
        if (it == sPointers.end() )
        {
            //sPointers[ name ] = (void*)(loader); //static_cast<tLoader>( T::load );
            //std::cout << __FUNCTION__ << " : " << name << std::endl;
            sPointers.insert(std::pair<std::string, void*>(name, (void*)(loader)));
        }
        */
        insert(name, (void*)(loader));

        return name;
    }

    template<class T>
    static tFigPointer<T> get(const std::string& name)
    {
        typedef typename tFigPointer<T>::tLoader loader;

        if (sPointers == 0)
        {
            return tFigPointer<T>();
        }

        auto it = sPointers->find(name);
        if (it != sPointers->end() )
        {
            return tFigPointer<T>((loader)(*it).second);
        }
        else
        {
            return tFigPointer<T>();
        }
    }


};



#endif // CFIGUREREGISTRY_H
