#pragma once

#include <QObject>
#include "TicTacToeModel.h"

class TicTacToeController : public QObject
{
    Q_OBJECT

public:
    explicit TicTacToeController(TicTacToeModel *model, QObject *parent = nullptr);

    void handleCellClicked(int row, int col);

private:
    TicTacToeModel* m_model;
};
