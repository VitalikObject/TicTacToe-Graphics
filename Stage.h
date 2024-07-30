#pragma once
#include <QtWidgets/qwidget.h>
#include <QPainter>
#include "TicTacToeController.h"
#include "TicTacToeModel.h"
#include <QtGui/qevent.h>

class Stage : public QWidget
{
public:
    Stage(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void drawGrid(QPainter &painter);
    void drawX(QPainter &painter, int row, int col);
    void drawO(QPainter &painter, int row, int col);

    TicTacToeModel* m_model;
    TicTacToeController* m_controller;
};
