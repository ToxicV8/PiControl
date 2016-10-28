#ifndef VARIABLES_H
#define VARIABLES_H

class Var
{
    public:

        Var(int v)
        {
            i = v;

            datatype = TYPE_INTEGER;
        }

        Var(float v)
        {
            f = v;
            datatype = TYPE_FLOAT;
        }

        Var(std::string v)
        {
            s = v;
            datatype = TYPE_STRING;
        }

        Var(bool v)
        {
            b = v;
            datatype = TYPE_BOOLEAN;
        }

        int datatype;
        std::string s;
        int i;
        float f;
        bool b;
};

class Variables
{
    public:
        Variables();

        std::unordered_map<std::string, Var*> vars;
        void AddVar(std::string name, int defaultval);
        void AddVar(std::string name, float defaultval);
        void AddVar(std::string name, bool defaultval);
        void AddVar(std::string name, std::string defaultval);
        virtual ~Variables();
    protected:
    private:
};

extern Variables* g_pVariables;

#endif // VARIABLES_H
