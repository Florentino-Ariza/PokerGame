#pragma once
#ifndef _HSAGE_H
#define _HSAGE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

namespace hsage
{
    #define HCON (char*)
    #define HVON (void*)

    extern int MAX_DISTANCE ;
    extern int feroblank;
    extern int ifinited;
    typedef void (*basic_persavefunc)(fstream&, void*);
    typedef void (*basic_pergetfunc)(fstream&, void*);
    typedef void (*adv_persavefunc)(string classname, fstream&, void*);
    typedef void* (*adv_pergetfunc)(string classname, fstream&);
    class hsageappendix;

    extern vector<string>* basictypes;
    extern vector<basic_persavefunc>* basicsave;
    extern vector<basic_pergetfunc>* basicget;
    extern vector<string>* advtypes;
    extern vector<adv_persavefunc>* advsave;
    extern vector<adv_pergetfunc>* advget;
    extern vector<hsageappendix*>* appendixes;

    string getNameinBracket(string name);
    string blanks();
    int ifbasictype(string type_name);
    int ifadvtype(string type_name);
    hsageappendix* fitch(string classname);
    void Init();
    void advNameRegister(string classname, int size);
    int distance(char* begin, char* src);
    void advItemRegister(string classname, string type_name, char* begin, char* src);
    void advsaveclass(string classname, fstream& fout, void* targetclass);
    string getname(fstream& fin);
    void skipbract(fstream& fin);
    void* advgetclass(string classname, fstream& fin);
    void saveObject(string classname, void* obj);
    void saveObject(string classname, void* obj, string filename);
    
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

    template<class Ty> void vectorsave(string classname, fstream& fout, void* target_vec)
    {
        if (target_vec == nullptr)
        {
            fout << blanks() << "NULL" << endl;
            return;
        }
        fout << blanks() << classname << endl;
        fout << blanks() << "{" << endl;
        feroblank++;
        string namein = getNameinBracket(classname);
        int index = ifbasictype(namein);
        if (index != EOF)
        {
            vector<Ty>* tmpvec = (vector<Ty>*)target_vec;
            int vecsize = int(tmpvec->size());
            fout << blanks() << "  " << vecsize << endl;
            for (int i = 0; i < vecsize; i++)
            {
                void* tarloc = HVON(&(*tmpvec)[i]);
                (*basicsave)[index](fout, tarloc);
            }
        }
        else
        {
            vector<Ty*>* advtmpvec = (vector<Ty*>*)target_vec;
            int vecsize = int(advtmpvec->size());
            fout << blanks() << "  " << vecsize << endl;
            for (int j = 0; j < vecsize; j++)
            {
                Ty* vtarloc = (Ty*)((*advtmpvec)[j]);
                index = ifadvtype(namein);
                // if(index != EOF)
                (*advsave)[index](namein, fout, HVON vtarloc);
            }
        }
        feroblank--;
        fout << blanks() << "}" << endl;
        return;
    }

    template<class Ty> void* vectorget(string classname, fstream& fin)
    {
        string name = getname(fin);
        string namein = getNameinBracket(name);
        if (name == "NULL")
            return nullptr;
        skipbract(fin);
        int vsize;
        fin >> vsize;
        int indexoftype = ifbasictype(namein);
        void* resvec;
        if (indexoftype != EOF)
        {
            vector<Ty>* newvec = new vector<Ty>;
            for (int i = 0; i < vsize; i++)
            {
                Ty* tmp = new Ty;
                (*basicget)[indexoftype](fin, tmp);
                newvec->push_back(*tmp);
            }
            resvec = HVON newvec;
        }
        else
        {
            indexoftype = ifadvtype(namein);
            vector<Ty*>* newvvec = new vector<Ty*>;
            for (int i = 0; i < vsize; i++)
            {
                void* res = (*advget)[indexoftype](namein, fin);
                newvvec->push_back((Ty*)(res));
            }
            resvec = HVON newvvec;
        }
        skipbract(fin);

        return resvec;
    }

    template<class T> void savetarget(fstream& fout, void* src)
    {
        char* csrc = HCON src;
        char* cbuf = new char[sizeof(T)];
        for (int i = 0; i<int(sizeof(T)); i++)
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
        for (int i = 0; i<int(sizeof(T)); i++)
        {
            cbuf[i] = csrc[i];
        }
        return;
    }
    
    template<class Ty> void vectorRegister(string classname)
    {
        appendixes->push_back(new hsageappendix(classname, sizeof(vector<Ty>)));
        advget->push_back(vectorget<Ty>);
        advsave->push_back(vectorsave<Ty>);
    }

    template<class typ> typ* getObject(string classname)
    {
        fstream fin;
        fin.open("OBJ.txt", ios::in);
        typ* obj = (typ*)advgetclass(classname, fin);
        fin.close();
        return obj;
    }

    template<class typ> typ* getObject(string classname, string filename)
    {
        fstream fin;
        fin.open(filename, ios::in);
        typ* obj = (typ*)advgetclass(classname, fin);
        fin.close();
        return obj;
    }
}

#endif