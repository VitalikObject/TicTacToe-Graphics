#pragma once

#include <QObject>

class TicTacToeModel : public QObject
{
    Q_OBJECT

public:
    explicit TicTacToeModel(QObject *parent = nullptr);
    void attemptToTurn(int row, int col);
    void botTurn();
    bool getIsGameStarted();
    void setIsGameStarted(bool isGameStarted);
    void setisPlayerTurn(bool isPlayerTurn);
    enum PlayerFieldState { Empty, X, O };
    enum GameState { Unfinished, Draw, PlayerWin, BotWin };
    void setPlayerFighter(PlayerFieldState playerFieldState);
    void setBotFighter(PlayerFieldState playerFieldState);
    PlayerFieldState getCell(int row, int col) const;

signals:
    void dataChanged();

private:
    void setCell(int row, int col, PlayerFieldState playerFieldState);
    PlayerFieldState m_playerFighter;
    PlayerFieldState m_botFighter;
    bool m_isGameStarted;
    bool m_isPlayerTurn;
    QVector<QVector<PlayerFieldState>> m_gameField;
    GameState findWinner();
    bool isFieldEmpty(int row, int col);
    void makeTurn(int row, int col, PlayerFieldState state);
    int minimax(QVector<QVector<PlayerFieldState>> &field, int depth, bool isMaximizing);
    int evaluateMove(QVector<QVector<PlayerFieldState>> &field, int depth, bool isMaximizing);
    GameState checkLine(PlayerFieldState a, PlayerFieldState b, PlayerFieldState c);
    GameState checkRows();
    GameState checkCols();
    GameState checkDiags();
    bool isBoardFull();
    std::pair<int, int> findBestMove();
    void updateBestMove(int score, int row, int col, int& bestScore, int& bestRow, int& bestCol);
};
