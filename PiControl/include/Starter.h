#ifndef STARTER_H
#define STARTER_H

class Starter
{
    public:
        Starter();
        void Start();
        virtual ~Starter();
    protected:
    private:
    const int m_pVersion[3] = {1, 0, 1};
};

extern Starter* g_pStarter;

#endif // STARTER_H
