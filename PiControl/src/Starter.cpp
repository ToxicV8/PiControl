#include "Includes.h"

Starter::Starter()
{

}


void Starter::Start()
{
    g_pLogger->Log("Booting PiControl v%i.%i.%i", m_pVersion[0], m_pVersion[1], m_pVersion[2]);


}

Starter::~Starter()
{

}
