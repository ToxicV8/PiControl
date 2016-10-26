#ifndef HELPERS_H
#define HELPERS_H


class Helpers
{
    public:
        Helpers();
        void split(const std::string &s, char delim, std::vector<std::string> &elems);
        virtual ~Helpers();
    protected:
    private:
};

extern Helpers* g_pHelpers;

#endif // HELPERS_H
