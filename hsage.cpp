#include "hsage.h"

using namespace hsage;

int hsage::MAX_DISTANCE = 1000;

int hsage::feroblank = 0;

int hsage::ifinited = 0;

vector<string>* hsage::basictypes = new vector<string>;
vector<hsage::basic_persavefunc>* hsage::basicsave 
= new vector<hsage::basic_persavefunc>;
vector<hsage::basic_pergetfunc>* hsage::basicget 
= new vector<hsage::basic_pergetfunc>;
vector<string>* hsage::advtypes
= new vector<string>;
vector<hsage::adv_persavefunc>* hsage::advsave
= new vector<hsage::adv_persavefunc>;
vector<hsage::adv_pergetfunc>* hsage::advget
= new vector<hsage::adv_pergetfunc>;
vector<hsage::hsageappendix*>* hsage::appendixes 
= new vector<hsage::hsageappendix*>;


string hsage::getNameinBracket(string name)
{
    stringstream tmpst;
    tmpst << name;
    char c;
    string namein = "";
    int pbracket = 0;
    while (c = tmpst.get(), c != '<');
    while (c = tmpst.get(), c != EOF)
    {
        if (c == '<')
            pbracket++;
        if (c == '>')
            pbracket--;
        if (pbracket < 0)
            return namein;
        namein += c;
    }

    return namein;
}

string hsage::blanks()
{
    string blank = "";
    for (int i = 0; i < feroblank; i++)
    {
        blank += "    ";
    }
    return blank;
}

int hsage::ifbasictype(string type_name)
{
    for (int i = 0; i<int(basictypes->size()); i++)
    {
        if ((*basictypes)[i] == type_name)
        {
            return i;
        }
    }
    return EOF;
}

int hsage::ifadvtype(string type_name)
{
    for (int i = 0; i<int((*appendixes).size()); i++)
    {
        if (type_name == (*appendixes)[i]->classname)
        {
            return i;
        }
    }
    return EOF;
}

hsage::hsageappendix* hsage::fitch(string classname)
{
    for (int i = 0; i<int((*appendixes).size()); i++)
    {
        if ((*appendixes)[i]->classname == classname)
        {
            return (*appendixes)[i];
        }
    }

    return nullptr;
}


void hsage::Init()
{
    if (ifinited)
        return;
    ifinited = 1;
    //basictypes = new vector<string>;
    //basicsave
    //    = new vector<hsage::basic_persavefunc>;
    //basicget
    //    = new vector<hsage::basic_pergetfunc>;
    //advtypes
    //    = new vector<string>;
    //advsave
    //    = new vector<hsage::adv_persavefunc>;
    //advget
    //    = new vector<hsage::adv_pergetfunc>;
    //hsage::appendixes
    //    = new vector<hsage::hsageappendix*>;
    basictypes->push_back("int");
    basicget->push_back(gettarget<int>);
    basicsave->push_back(savetarget<int>);
    basictypes->push_back("double");
    basicget->push_back(gettarget<double>);
    basicsave->push_back(savetarget<double>);
    basictypes->push_back("float");
    basicget->push_back(gettarget<float>);
    basicsave->push_back(savetarget<float>);
    basictypes->push_back("string");
    basicget->push_back(gettarget<string>);
    basicsave->push_back(savetarget<string>);
    basictypes->push_back("char");
    basicget->push_back(gettarget<char>);
    basicsave->push_back(savetarget<char>);
    vectorRegister<int>("vector<int>");
    vectorRegister<double>("vector<double>");
    vectorRegister<float>("vector<float>");
    vectorRegister<string>("vector<string>");
    vectorRegister<vector<int>>("vector<vector<int>>");
    // vectorRegister<vector<vector<int>*>>("vector<vector<int>*>");
}

void hsage::advNameRegister(string classname, int size)
{
    appendixes->push_back(new hsageappendix(classname, size));
    advsave->push_back(advsaveclass);
    advget->push_back(advgetclass);
}


int hsage::distance(char* begin, char* src)
{
    for (int i = 0; i < MAX_DISTANCE; i++)
    {
        if (begin + i == src)
            return i;
    }

    return EOF;
}

void hsage::advItemRegister(string classname, string type_name, char* begin, char* src)
{
    hsageappendix* thisclass = fitch(classname);
    thisclass->type_names.push_back(type_name);
    thisclass->type_locs.push_back(distance(begin, src));
}

void hsage::advsaveclass(string classname, fstream& fout, void* targetclass)
{
    if (targetclass == nullptr)
    {
        fout << blanks() << "NULL" << endl;
        return;
    }
    fout << blanks() << classname << endl;
    fout << blanks() << "{" << endl;
    feroblank++;
    hsageappendix* thisclass = fitch(classname);
    for (int i = 0; i<int(thisclass->type_names.size()); i++)
    {
        string thisname = thisclass->type_names[i];
        int indexoftype = ifbasictype(thisname);
        void* tarloc = (void*)((char*)targetclass
            + thisclass->type_locs[i]);
        if (indexoftype != EOF)
        {
            (*basicsave)[indexoftype](fout, tarloc);
        }
        else
        {
            char* csrc = HCON tarloc;
            void* cbuf;
            for (int i = 0; i<int(sizeof(void*)); i++)
            {
                *(HCON & cbuf + i) = csrc[i];
            }
            // advsaveclass(thisname, fout, cbuf);
            int indexoftype = ifadvtype(thisname);
            // cout << "This name :" <<thisname << endl;
            if (indexoftype != EOF)
            {
                (*advsave)[indexoftype](thisname, fout, cbuf);
            }
        }
    }
    feroblank--;
    fout << blanks() << "}" << endl;

    return;
}

string hsage::getname(fstream& fin)
{
    string name = "";
    char c;
    while (c = char(fin.get()),
        c == ' ' || c == '\n' || c == ' ');
    name += c;
    while (c = char(fin.get()), c != '\n' && c != EOF)
    {
        name += c;
    }

    return name;
}

void hsage::skipbract(fstream& fin)
{
    char c;
    while (c = char(fin.get()), c != '{' && c != '}');
}

void* hsage::advgetclass(string classname, fstream& fin)
{
    string name = getname(fin);
    if (name == "NULL")
        return nullptr;
    skipbract(fin);
    hsageappendix* thisclass = fitch(classname);
    char* buffer = new char[thisclass->size];
    for (int i = 0; i<int(thisclass->type_names.size()); i++)
    {
        string thisname = thisclass->type_names[i];
        int indexoftype = ifbasictype(thisname);
        void* tarloc = HVON(buffer + thisclass->type_locs[i]);
        if (indexoftype != EOF)
        {
            (*basicget)[indexoftype](fin, tarloc);
        }
        else
        {
            indexoftype = ifadvtype(thisname);
            if (indexoftype != EOF)
            {
                void* res = (*advget)[indexoftype](thisname, fin);
                char* csrc = HCON & res;
                char* cbuf = HCON tarloc;
                for (int i = 0; i<int(sizeof(void*)); i++)
                {
                    cbuf[i] = csrc[i];
                }
            }

        }
    }
    skipbract(fin);

    return HVON buffer;
}

void hsage::saveObject(string classname, void* obj)
{
    fstream fout;
    fout.open("OBJ.txt", ios::out);
    advsaveclass(classname, fout, obj);
    fout.close();
    return;
}

void hsage::saveObject(string classname, void* obj, string filename)
{
    fstream fout;
    fout.open(filename.c_str(), ios::out);
    advsaveclass(classname, fout, obj);
    fout.close();
    return;
}

