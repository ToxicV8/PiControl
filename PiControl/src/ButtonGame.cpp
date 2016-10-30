#include "Includes.h"

ButtonGame::ButtonGame()
{
    //ctor
}

void Player2ButtonDown(bool state)
{
    if(!state)
        g_pButtonGame->OnClick(g_pVariables->vars["player2_pin"]->i);
}

void ButtonGame::OnClick(int pin)
{
    if(m_bLedOn && !m_bWinner)
    {
        if(pin == g_pVariables->vars["player2_pin"]->i)
        {
            g_pLogger->Log("%s won the Round", m_sPlayer2.c_str());
            m_vStats[g_pButtonGame->m_sPlayer2].RoundsWon++;
        }
        else if(pin == g_pVariables->vars["player1_pin"]->i)
        {
            g_pLogger->Log("%s won the Round", m_sPlayer1.c_str());
            m_vStats[g_pButtonGame->m_sPlayer1].RoundsWon++;
        }
        m_bInRound = false;
        m_bWinner = true;
    }else if(m_bInRound && !m_bWinner){

        if(pin == g_pVariables->vars["player2_pin"]->i)
        {
            g_pLogger->Log("%s Pressed before Light was on! %s won the Round", m_sPlayer2.c_str(), m_sPlayer1.c_str());
            m_vStats[g_pButtonGame->m_sPlayer1].RoundsWon++;
        }
        else if(pin == g_pVariables->vars["player1_pin"]->i)
        {
            g_pLogger->Log("%s Pressed before Light was on! %s won the Round", m_sPlayer1.c_str(), m_sPlayer2.c_str());

            m_vStats[g_pButtonGame->m_sPlayer2].RoundsWon++;
        }
        m_bInRound = false;
        m_bWinner = true;
    }
}

void Player1ButtonDown(bool state)
{
    if(!state)
        g_pButtonGame->OnClick(g_pVariables->vars["player1_pin"]->i);
}

void ButtonGame::Setup()
{
    g_pGpioControl->SetPullUpDown(g_pVariables->vars["player1_pin"]->i, PUD_UP);
    g_pGpioControl->SetPullUpDown(g_pVariables->vars["player2_pin"]->i, PUD_UP);

    g_pGpioControl->RegisterToggleHandler(g_pVariables->vars["player1_pin"]->i, &Player1ButtonDown);
    g_pGpioControl->RegisterToggleHandler(g_pVariables->vars["player2_pin"]->i, &Player2ButtonDown);

    this->m_bSetup = true;
}

void ButtonGame::DisplayStats(std::string player)
{

    g_pLogger->Log("%s Stats: %s %s", std::string("-------------").c_str(), player.c_str(), std::string("---------").c_str());
    g_pLogger->Log("RoundsWon: %i", m_vStats[player].RoundsWon);
    g_pLogger->Log("TotalWins: %i", m_vStats[player].TotalWins);
    g_pLogger->Log("Games: %i", m_vStats[player].Games);
}

int RandU(int nMin, int nMax)
{
    std::random_device rd;
    std::mt19937 gn(rd());
    std::uniform_int_distribution<int> gen(nMin, nMax); // uniform, unbiased
    return gen(gn);
    //return nMin + (int)((double)rand() / (RAND_MAX+1) * (nMax-nMin+1));
}

void Wait(int seconds)
{
    std::cout << "Starting new Round in ";

    g_pTelegramManager->SendToAllChats("Starting new Round...");

    for(int i = seconds; i != 0; i--)
    {
        g_pLogger->Log("%i", i);
        g_pGpioControl->TogglePin(g_pVariables->vars["led_pin"]->i);
        delay(500);
        g_pGpioControl->TogglePin(g_pVariables->vars["led_pin"]->i);
        delay(500);
    }
    g_pLogger->Log("Go!");
}

void RunGame()
{
    while(g_pButtonGame->m_bGameRunning == true)
    {
        delay(30);

        if(g_pButtonGame->m_bWinner == true)
        {
            g_pButtonGame->m_bLedOn = false;

            g_pButtonGame->m_bWinner = false;

            if(g_pButtonGame->m_iRound == g_pButtonGame->m_iRounds)
            {
                g_pButtonGame->EndGame();

                break;
            }

            g_pButtonGame->m_iRound++;

            Wait(5);

            g_pButtonGame->m_bInRound = true;
            g_pGpioControl->SetPinValue(g_pVariables->vars["led_pin"]->i, LOW);

            delay(RandU(5, 20)* 1000);

            g_pGpioControl->SetPinValue(g_pVariables->vars["led_pin"]->i, HIGH);

            g_pButtonGame->m_bLedOn = true;
        }
    }
}

void ButtonGame::StartNewGame(int rounds, std::string player1, std::string player2)
{
    if(m_bGameRunning)
        EndGame();

    if(!m_bSetup)
        this->Setup();

    m_sPlayer1 = player1;

    m_iRounds = rounds;

    m_iRound = 0;

    m_sPlayer2 = player2;

    m_bGameRunning = true;

    m_bLedOn = false;

    m_bWinner = true;

    if(m_vStats.find(m_sPlayer1) == m_vStats.end())
        m_vStats[m_sPlayer1] = Stats();

    if(m_vStats.find(m_sPlayer2) == m_vStats.end())
        m_vStats[m_sPlayer2] = Stats();

    for(auto s : m_vStats)
        m_vStats[s.first].RoundsWon = 0;

    m_vStats[m_sPlayer1].Games++;
    m_vStats[m_sPlayer2].Games++;

    g_pGpioControl->SetPinValue(g_pVariables->vars["led_pin"]->i, LOW);

    g_pThreadManager->RegisterThread(&RunGame);
}

void ButtonGame::EndGame()
{
    m_bGameRunning = false;

    std::string winner = "";

    bool Draw = false;

    if(m_vStats[m_sPlayer1].RoundsWon > m_vStats[m_sPlayer2].RoundsWon)
        winner = m_sPlayer1;

    if(m_vStats[m_sPlayer2].RoundsWon > m_vStats[m_sPlayer1].RoundsWon)
        winner = m_sPlayer2;

    if(m_vStats[m_sPlayer2].RoundsWon == m_vStats[m_sPlayer1].RoundsWon)
        Draw = true;

    m_vStats[winner].TotalWins++;

    g_pLogger->Log("The Winner is....");

    delay(1000);

    g_pLogger->Log( "%s", Draw ? "Draw!" : (winner + "!").c_str());

    DisplayStats(m_sPlayer1);
    DisplayStats(m_sPlayer2);
}

ButtonGame::~ButtonGame()
{
    //dtor
}
