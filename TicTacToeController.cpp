#include "TicTacToeController.h"

TicTacToeController::TicTacToeController(TicTacToeModel *model, QObject *parent)
    : QObject(parent)
    , m_model(model)
{
}

void TicTacToeController::handleCellClicked(int row, int col)
{
    m_model->attemptToTurn(row, col);
}
