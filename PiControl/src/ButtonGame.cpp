#include "Includes.h"

ButtonGame::ButtonGame()
{
    //ctor
}

void Player2ButtonDown(void)
{
    if(g_pButtonGame->m_bLedOn && !g_pButtonGame->m_bWinner)
    {
        g_pButtonGame->m_bWinner = true;
        g_pButtonGame->m_bInRound = false;
        g_pLogger->Log("%s won the Round", g_pButtonGame->m_sPlayer2.c_str());
        g_pButtonGame->m_vStats[g_pButtonGame->m_sPlayer2].RoundsWon++;

    }
    else if(g_pButtonGame->m_bInRound && !g_pButtonGame->m_bWinner)
    {
        g_pButtonGame->m_bWinner = true;
        g_pButtonGame->m_bInRound = false;

        g_pLogger->Log("%s Pressed before Light was on! %s won the Round", g_pButtonGame->m_sPlayer2.c_str(), g_pButtonGame->m_sPlayer1.c_str());
        g_pButtonGame->m_vStats[g_pButtonGame->m_sPlayer1].RoundsWon++;

    }
}


void Player1ButtonDown(void)
{
    if(g_pButtonGame->m_bLedOn && !g_pButtonGame->m_bWinner)
    {
        g_pButtonGame->m_bWinner = true;
        g_pButtonGame->m_bInRound = false;

        g_pLogger->Log("%s won the Round", g_pButtonGame->m_sPlayer1.c_str());
        g_pButtonGame->m_vStats[g_pButtonGame->m_sPlayer1].RoundsWon++;
    }
    else if(g_pButtonGame->m_bInRound && !g_pButtonGame->m_bWinner)
    {
        g_pButtonGame->m_bWinner = true;
        g_pButtonGame->m_bInRound = false;

        g_pLogger->Log("%s Pressed before Light was on! %s won the Round", g_pButtonGame->m_sPlayer1.c_str(), g_pButtonGame->m_sPlayer2.c_str());
        g_pButtonGame->m_vStats[g_pButtonGame->m_sPlayer2].RoundsWon++;
    }
}


void ButtonGame::Setup()
{
    g_pGpioControl->SetPullUpDown(g_pVariables->vars["player1_pin"]->i, PUD_UP);

    g_pGpioControl->SetPullUpDown(g_pVariables->vars["player2_pin"]->i, PUD_UP);

    wiringPiISR(g_pVariables->vars["player1_pin"]->i, INT_EDGE_FALLING, &Player1ButtonDown);

    wiringPiISR(g_pVariables->vars["player2_pin"]->i, INT_EDGE_FALLING, &Player2ButtonDown);

    this->m_bSetup = true;
}

void ButtonGame::DisplayStats(std::string player)
{

    g_pLogger->Log("------------- Stats: %s -------------\nRoundsWon: %i\nTotalWins: %i\nGames: %i", player.c_str(), m_vStats[player].RoundsWon, m_vStats[player].TotalWins, m_vStats[player].Games);
}

int RandU(int nMin, int nMax)
{
    std::random_device rd;
    std::mt19937 gn(rd());
    std::uniform_int_distribution<int> gen(nMin, nMax); // uniform, unbiased
    return gen(gn);
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

PI_THREAD(Run)
{
    while(g_pButtonGame->m_bGameRunning == true)
    {
        delay(0.5);
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

            Wait(3);

            g_pButtonGame->m_bInRound = true;

            g_pGpioControl->SetPinValue(g_pVariables->vars["led_pin"]->i, LOW);

            delay(RandU(1, 6) * 1000);

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
    piThreadCreate(Run);
    //g_pThreadManager->RegisterThread(&RunGame);
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

    if(!Draw)
        m_vStats[winner].TotalWins++;

    g_pLogger->Log("The Winner is....");

    g_pLogger->Log( "%s", Draw ? "Draw!" : (winner + "!").c_str());

    DisplayStats(m_sPlayer1);
    DisplayStats(m_sPlayer2);
}

ButtonGame::~ButtonGame()
{
    //dtor
}
