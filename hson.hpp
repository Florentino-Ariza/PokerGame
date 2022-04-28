#ifndef _HSON_H
#define _HSON_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

namespace hsage 
{
    /////////////////////////////////////
    void* advgetclass(string classname, fstream& fin);
    void saveObject(string classname, void* obj);
    string getname(fstream& fin);
    int distance(char* begin, char* src);
    void skipbract(fstream& fin);
    string blanks();
    template<class T> void savetarget(fstream& fout, void* src);
    template<class T> void gettarget(fstream& fin, void* buffer);
    int ifbasictype(string type_name);
    void advsaveclass(string classname, fstream& fout, void* targetclass);
    template<class Ty> void vectorRegister(string classname);
    int ifadvtype(string type_name);
    /////////////////////////////////////
    #define HCON (char*)
    #define HVON (void*)

    int MAX_DISTANCE = 1000;
    typedef void (*basic_persavefunc)(fstream&, void*);
    typedef void (*basic_pergetfunc)(fstream&, void*);
    typedef void (*adv_persavefunc)(string classname, fstream&, void*);
    typedef void*(*adv_pergetfunc)(string classname, fstream&);
    class hsageappendix;

    vector<string> basictypes;
    vector<basic_persavefunc> basicsave;
    vector<basic_pergetfunc> basicget;

    vector<string> advtypes;
    vector<adv_persavefunc> advsave;
    vector<adv_pergetfunc> advget;

    vector<hsageappendix*> appendixes;

    int feroblank = 0;

    string getNameinBracket(string name)
    {
        stringstream tmpst ;
        tmpst << name;
        char c;
        string namein = "";
        int pbracket = 0;
        while(c = tmpst.get(), c != '<');
        while(c = tmpst.get(), c != EOF)
        {
            if(c == '<')
                pbracket ++;
            if(c == '>')
                pbracket --;
            if(pbracket < 0)
                return namein;
            namein += c;
        }

        return namein;
    }


    template<class Ty> void vectorsave(string classname, fstream& fout, void* target_vec)
    {
        if(target_vec == nullptr)
        {
            fout << blanks() << "NULL" << endl;
            return ;
        }
        fout << blanks() << classname << endl;
        fout << blanks() << "{"       << endl;
        feroblank ++;
        string namein = getNameinBracket(classname);
        int index = ifbasictype(namein);
        if(index != EOF)
        {
            vector<Ty>* tmpvec = (vector<Ty>*)target_vec; 
            int vecsize = int(tmpvec->size());
            fout << blanks() << "  " << vecsize << endl;
            for(int i=0; i<vecsize; i++)
            {
                void* tarloc = HVON (&(*tmpvec)[i]);
                basicsave[index](fout, tarloc);
            }
        }
        else 
        {
            vector<Ty*>* advtmpvec = (vector<Ty*>*)target_vec;
            int vecsize = int(advtmpvec->size());
            fout << blanks() << "  " << vecsize << endl;
            for(int j=0; j<vecsize; j++)
            {
                Ty* vtarloc = (Ty*)((*advtmpvec)[j]);
                index = ifadvtype(namein);
                // if(index != EOF)
                advsave[index](namein, fout, HVON vtarloc);
            }
        }
        feroblank --;
        fout << blanks() << "}"         << endl;
        return ;
    }

    template<class Ty> void* vectorget(string classname, fstream& fin)
    {
        string name = getname(fin);
        string namein = getNameinBracket(name);
        if(name == "NULL")
            return nullptr;
        skipbract(fin);
        int vsize;
        fin >> vsize;
        int indexoftype = ifbasictype(namein);
        void* resvec;
        if(indexoftype != EOF)
        {
            vector<Ty>* newvec = new vector<Ty>;
            for(int i=0; i<vsize; i++)
            {
                Ty* tmp = new Ty;
                basicget[indexoftype](fin, tmp);
                newvec->push_back(*tmp);
            }
            resvec = HVON newvec;
        }
        else 
        {
            indexoftype = ifadvtype(namein);
            vector<Ty*>* newvvec = new vector<Ty*>;
            for(int i=0; i<vsize; i++)
            {
                void* res = advget[indexoftype](namein, fin);
                newvvec->push_back((Ty*)(res));
            }
            resvec = HVON newvvec;
        }
        skipbract(fin);

        return resvec;
    }
    
    string blanks()
    {
        string blank = "";
        for(int i=0; i<feroblank; i++)
        {
            blank += "    ";
        }
        return blank;
    }

    class hsageappendix
    {
    public:
        string classname;
        int size;
        vector<string> type_names;
        vector<int> type_locs;
        hsageappendix(string classname, int size)
        {
            this->classname = classname;
            this->size = size;
        }
    };  

    template<class T> void savetarget(fstream& fout, void* src)
    {
        char* csrc = HCON src;
        char* cbuf = new char[sizeof(T)];
        for(int i=0; i<int(sizeof(T)); i++)
        {
            cbuf[i] = csrc[i];
        }
        T tmp = *(T*)cbuf;
        fout << blanks() << tmp << endl;
    } 

    template<class T> void gettarget(fstream& fin, void* buffer)
    {
        T* tmp = new T;
        fin >> *tmp;
        char* csrc = HCON tmp;
        char* cbuf = HCON buffer;
        for(int i=0; i<int(sizeof(T)); i++)
        {
            cbuf[i] = csrc[i];
        }
        return;
    }

    int ifbasictype(string type_name)
    {
        for(int i=0; i<int(basictypes.size()); i++)
        {
            if(basictypes[i] == type_name)
            {
                return i;
            }
        }
        return EOF;
    }

    int ifadvtype(string type_name)
    {
        for(int i=0; i<int(appendixes.size()); i++)
        {
            if(type_name == appendixes[i]->classname)
            {
                return i;
            }
        }
        return EOF;
    }

    hsageappendix* fitch(string classname)
    {
        for(int i=0; i<int(appendixes.size()); i++)
        {
            if(appendixes[i]->classname == classname)
            {
                return appendixes[i];
            }
        }

        return nullptr;
    }

    void Init()
    {
        basictypes.push_back("int");
        basicget.push_back(gettarget<int>);
        basicsave.push_back(savetarget<int>);
        basictypes.push_back("double");
        basicget.push_back(gettarget<double>);
        basicsave.push_back(savetarget<double>);
        basictypes.push_back("float");
        basicget.push_back(gettarget<float>);
        basicsave.push_back(savetarget<float>);
        basictypes.push_back("string");
        basicget.push_back(gettarget<string>);
        basicsave.push_back(savetarget<string>);
        basictypes.push_back("char");
        basicget.push_back(gettarget<char>);
        basicsave.push_back(savetarget<char>);
        vectorRegister<int>("vector<int>");
        vectorRegister<double>("vector<double>");
        vectorRegister<float>("vector<float>");
        vectorRegister<string>("vector<string>");
        vectorRegister<vector<int>>("vector<vector<int>>");
        // vectorRegister<vector<vector<int>*>>("vector<vector<int>*>");
    }

    template<class Ty> void vectorRegister(string classname)
    {
        appendixes.push_back(new hsageappendix(classname, sizeof(vector<Ty>)));
        advget.push_back(vectorget<Ty>);
        advsave.push_back(vectorsave<Ty>);
    }

    void advNameRegister(string classname, int size)
    {
        appendixes.push_back(new hsageappendix(classname, size));
        advsave.push_back(advsaveclass);
        advget.push_back(advgetclass);
    }

    int distance(char* begin, char* src)
    {
        for(int i=0; i<MAX_DISTANCE; i++)
        {
            if(begin + i == src)
                return i;
        }

        return EOF;
    }

    void advItemRegister(string classname, string type_name, char* begin, char* src)
    {
        hsageappendix* thisclass = fitch(classname);
        thisclass->type_names.push_back(type_name);
        thisclass->type_locs.push_back(distance(begin, src));
    }

    void advsaveclass(string classname, fstream& fout, void* targetclass)
    {
        if(targetclass == nullptr)
        {
            fout << blanks() << "NULL"  << endl;
            return ;
        }
        fout << blanks() << classname   << endl;
        fout << blanks() << "{"         << endl;
        feroblank ++;
        hsageappendix* thisclass = fitch(classname);
        for(int i=0; i<int(thisclass->type_names.size()); i++)
        {
            string thisname = thisclass->type_names[i];
            int indexoftype = ifbasictype(thisname);
            void* tarloc = (void*)((char*)targetclass 
                         + thisclass->type_locs[i]);
            if(indexoftype != EOF)
            {
                basicsave[indexoftype](fout, tarloc);
            }
            else 
            {
                char* csrc = HCON tarloc;
                void* cbuf ;
                for(int i=0; i<int(sizeof(void*)); i++)
                {
                    *(HCON &cbuf + i) = csrc[i];
                }
                // advsaveclass(thisname, fout, cbuf);
                int indexoftype = ifadvtype(thisname);
                // cout << "This name :" <<thisname << endl;
                if(indexoftype != EOF)
                {
                    advsave[indexoftype](thisname, fout, cbuf);
                }
            }
        }
        feroblank --;
        fout << blanks() << "}"         << endl;

        return ;
    }

    string getname(fstream& fin)
    {
        string name = "";
        char c;
        while(c = char(fin.get()), 
              c == ' ' || c == '\n' || c == ' ');
        name += c;
        while(c = char(fin.get()), c != '\n' && c != EOF)
        {
            name += c;
        }

        return name;
    }

    void skipbract(fstream& fin)
    {
        char c;
        while(c = char(fin.get()), c != '{' && c != '}');
    }

    void* advgetclass(string classname, fstream& fin)
    {
        string name = getname(fin);
        if(name == "NULL")
            return nullptr;
        skipbract(fin);
        hsageappendix* thisclass = fitch(classname);
        char* buffer = new char[thisclass->size];
        for(int i=0; i<int(thisclass->type_names.size()); i++)
        {
            string thisname = thisclass->type_names[i];
            int indexoftype = ifbasictype(thisname);
            void* tarloc = HVON (buffer + thisclass->type_locs[i]);
            if(indexoftype != EOF)
            {
                basicget[indexoftype](fin, tarloc);
            }
            else 
            {
                indexoftype = ifadvtype(thisname);
                if(indexoftype != EOF)
                {
                    void* res = advget[indexoftype](thisname, fin);
                    char* csrc = HCON &res;
                    char* cbuf = HCON tarloc;
                    for(int i=0; i<int(sizeof(void*)); i++)
                    {
                        cbuf[i] = csrc[i];
                    }
                }
                
            }
        }
        skipbract(fin);

        return HVON buffer;
    }

    void saveObject(string classname, void* obj)
    {
        fstream fout;
        fout.open("OBJ.txt", ios::out);
        advsaveclass(classname, fout, obj);
        fout.close();
        return ;
    }

    void saveObject(string classname, void* obj, string filename)
    {
        fstream fout;
        fout.open(filename.c_str(), ios::out);
        advsaveclass(classname, fout, obj);
        fout.close();
        return ;
    }

    template<class typ> typ* getObject(string classname)
    {
        fstream fin;
        fin.open("OBJ.txt", ios::in);
        typ* obj = (typ*) advgetclass(classname, fin);
        fin.close();
        return obj;
    }

    template<class typ> typ* getObject(string classname, string filename)
    {
        fstream fin;
        fin.open(filename, ios::in);
        typ* obj = (typ*) advgetclass(classname, fin);
        fin.close();
        return obj;
    }
}

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

    void classItemRegister(string classname, string val_type, char* _this_, char* _pointer_of_val)
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