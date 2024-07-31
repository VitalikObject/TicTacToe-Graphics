#include "TicTacToeModel.h"

TicTacToeModel::TicTacToeModel(QObject *parent)
    : QObject(parent)
{
    m_playerFighter = X;
    m_botFighter = O;
    m_isPlayerTurn = true;
    m_gameField.assign(3, QVector<PlayerFieldState>(3, PlayerFieldState::Empty));
    m_isGameStarted = true;
}

bool TicTacToeModel::isFieldEmpty(int row, int col) {
    return m_gameField[row][col] == PlayerFieldState::Empty;
}

bool TicTacToeModel::getIsGameStarted() {
    return m_isGameStarted;
}

void TicTacToeModel::setIsGameStarted(bool isGameStarted) {
    m_isGameStarted = isGameStarted;
}

void TicTacToeModel::setisPlayerTurn(bool isPlayerTurn) {
    m_isPlayerTurn = isPlayerTurn;
}

void TicTacToeModel::setPlayerFighter(PlayerFieldState playerFieldState) {
    m_playerFighter = playerFieldState;
}

void TicTacToeModel::setBotFighter(PlayerFieldState playerFieldState) {
    m_botFighter = playerFieldState;
}

void TicTacToeModel::attemptToTurn(int row, int col) {
    if (m_isPlayerTurn && isFieldEmpty(row, col)) {
        makeTurn(row, col, X);
        if (findWinner() == Unfinished) {
            botTurn();
        }
    }
}

void TicTacToeModel::makeTurn(int row, int col, PlayerFieldState state) {
    setCell(row, col, state);

    m_isPlayerTurn = !m_isPlayerTurn;

    GameState result = findWinner();
    if (result != Unfinished) {
        m_isPlayerTurn = false;
        //emit displayResult(result);
    }
}

TicTacToeModel::PlayerFieldState TicTacToeModel::getCell(int row, int col) const
{
    return m_gameField[row][col];
}

void TicTacToeModel::setCell(int row, int col, PlayerFieldState playerFieldState)
{
    if (m_gameField[row][col] == Empty) {
        m_gameField[row][col] = playerFieldState;
        emit dataChanged();
    }
}

void TicTacToeModel::botTurn() {
    auto [bestRow, bestCol] = findBestMove();

    if (bestRow != -1 && bestCol != -1) {
        makeTurn(bestRow, bestCol, m_botFighter);
    }
}


std::pair<int, int> TicTacToeModel::findBestMove() {
    int bestScore = std::numeric_limits<int>::min();
    int bestRow = -1, bestCol = -1;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (isFieldEmpty(row, col)) {
                m_gameField[row][col] = m_botFighter;
                int score = minimax(m_gameField, 0, false);
                m_gameField[row][col] = PlayerFieldState::Empty;

                updateBestMove(score, row, col, bestScore, bestRow, bestCol);
            }
        }
    }

    return {bestRow, bestCol};
}

void TicTacToeModel::updateBestMove(int score, int row, int col, int& bestScore, int& bestRow, int& bestCol) {
    if (score > bestScore) {
        bestScore = score;
        bestRow = row;
        bestCol = col;
    }
}


int TicTacToeModel::evaluateMove(QVector<QVector<PlayerFieldState>> &field, int depth, bool isMaximizing) {
    int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    PlayerFieldState currentPlayer = isMaximizing ? m_botFighter : m_playerFighter;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (field[row][col] == PlayerFieldState::Empty) {
                field[row][col] = currentPlayer;
                int score = minimax(field, depth + 1, !isMaximizing);
                field[row][col] = PlayerFieldState::Empty;
                bestScore = isMaximizing ? std::max(score, bestScore) : std::min(score, bestScore);
            }
        }
    }

    return bestScore;
}

int TicTacToeModel::minimax(QVector<QVector<PlayerFieldState>> &field, int depth, bool isMaximizing) {
    GameState result = findWinner();
    if (result != Unfinished) {
        if (result == BotWin) return 10 - depth;
        if (result == PlayerWin) return depth - 10;
        return 0;
    }

    return evaluateMove(field, depth, isMaximizing);
}

TicTacToeModel::GameState TicTacToeModel::checkLine(PlayerFieldState a, PlayerFieldState b, PlayerFieldState c) {
    if (a == b && b == c && a != PlayerFieldState::Empty) {
        return a == m_playerFighter ? PlayerWin : BotWin;
    }
    return Unfinished;
}

TicTacToeModel::GameState TicTacToeModel::checkRows() {
    for (int i = 0; i < 3; ++i) {
        GameState rowResult = checkLine(m_gameField[i][0], m_gameField[i][1], m_gameField[i][2]);
        if (rowResult != Unfinished) return rowResult;
    }
    return Unfinished;
}

TicTacToeModel::GameState TicTacToeModel::checkCols() {
    for (int i = 0; i < 3; ++i) {
        GameState colResult = checkLine(m_gameField[0][i], m_gameField[1][i], m_gameField[2][i]);
        if (colResult != Unfinished) return colResult;
    }
    return Unfinished;
}

TicTacToeModel::GameState TicTacToeModel::checkDiags() {
    GameState diag1Result = checkLine(m_gameField[0][0], m_gameField[1][1], m_gameField[2][2]);
    GameState diag2Result = checkLine(m_gameField[0][2], m_gameField[1][1], m_gameField[2][0]);
    if (diag1Result != Unfinished) return diag1Result;
    if (diag2Result != Unfinished) return diag2Result;
    return Unfinished;
}

bool TicTacToeModel::isBoardFull() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (m_gameField[row][col] == PlayerFieldState::Empty)
                return false;
        }
    }
    return true;
}

TicTacToeModel::GameState TicTacToeModel::findWinner() {
    GameState rowResult = checkRows();
    if (rowResult != Unfinished) return rowResult;

    GameState colResult = checkCols();
    if (colResult != Unfinished) return colResult;

    GameState diagResult = checkDiags();
    if (diagResult != Unfinished) return diagResult;

    return isBoardFull() ? Draw : Unfinished;
}
