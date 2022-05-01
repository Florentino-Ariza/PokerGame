#ifndef _HSON_H
#define _HSON_H
#include"hsage.h"

namespace HSON
{
#ifndef H_HCON
#define H_HCON (char*)
#endif

    template<class Ty_classname> inline void classRegister(string classname)
        //First of all you need to register the class name.
    {
        hsage::advNameRegister(classname, sizeof(Ty_classname));
    }

    template<class Ty_inside_vector> inline void vectorRegister(string vectortype)
        //basic types inside vector dosn't need to register 
        //but if you want to use vector<vector>> or vector<[new type of class]>
        //you need to register.
    {
        hsage::vectorRegister<Ty_inside_vector>(vectortype);
    }

    inline void classItemRegister(string classname, string val_type, char* _this_, char* _pointer_of_val)
    //Every class you need to save and read should be registered ONCE.
    {
        hsage::advItemRegister(classname, val_type, _this_, _pointer_of_val);
    }

    inline void Inithson()
        // INIT HSON BEFORE USING IT!!! 
    {
        hsage::Init();
    }

    template<class Ty> inline Ty* getobject(string classname, string filename)
    {
        return hsage::getObject<Ty>(classname, filename);
    }

    inline void saveobject(string classname, string filename, void* src_object)
    {
        hsage::saveObject(classname, src_object, filename);
    }
}

#endif