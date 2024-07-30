#include "Stage.h"

Stage::Stage(QWidget* parent)
    : m_model(new TicTacToeModel(this))
    , m_controller(new TicTacToeController(m_model, this))
{
    connect(m_model, &TicTacToeModel::dataChanged, this, QOverload<>::of(&Stage::update));
}

void Stage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    drawGrid(painter);

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (m_model->getCell(row, col) == TicTacToeModel::X) {
                drawX(painter, row, col);
            } else if (m_model->getCell(row, col) == TicTacToeModel::O) {
                drawO(painter, row, col);
            }
        }
    }
}

void Stage::mousePressEvent(QMouseEvent *event)
{
    int row = event->position().y() / (height() / 3);
    int col = event->position().x() / (width() / 3);
    m_controller->handleCellClicked(row, col);
}

void Stage::drawGrid(QPainter &painter)
{
    int w = width();
    int h = height();

    for (int i = 1; i < 3; ++i) {
        painter.drawLine(i * w / 3, 0, i * w / 3, h);
        painter.drawLine(0, i * h / 3, w, i * h / 3);
    }
}

void Stage::drawX(QPainter &painter, int row, int col)
{
    int w = width() / 3;
    int h = height() / 3;

    painter.drawLine(col * w, row * h, (col + 1) * w, (row + 1) * h);
    painter.drawLine((col + 1) * w, row * h, col * w, (row + 1) * h);
}

void Stage::drawO(QPainter &painter, int row, int col)
{
    int w = width() / 3;
    int h = height() / 3;

    painter.drawEllipse(col * w, row * h, w, h);
}

