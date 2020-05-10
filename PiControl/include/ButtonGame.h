#ifndef BUTTONGAME_H
#define BUTTONGAME_H

class Stats
{
    public:
        Stats()
        {
            RoundsWon = 0;
            TotalWins = 0;
            Games = 0;
        }
        int RoundsWon;
        int TotalWins;
        int Games;
};

class ButtonGame
{
    public:
        ButtonGame();
        void Setup();
        void DisplayStats(std::string player);
        void OnClick(int pin);
        void StartNewGame(int rounds, std::string player1, std::string player2);
        void EndGame();
        bool m_bWinner;
        virtual ~ButtonGame();
        std::string m_sPlayer1, m_sPlayer2;
        std::unordered_map<std::string, Stats> m_vStats;
        bool m_bSetup = false;
        bool m_bLedOn = false;
        bool m_bGameRunning = false;
        int m_iRounds;
        bool m_bInRound = false;
        int m_iRound;
    protected:
    private:
};
extern ButtonGame* g_pButtonGame;
#endif // BUTTONGAME_H
