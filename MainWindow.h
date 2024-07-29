#pragma once

#include <QMainWindow>
#include "TicTacToeController.h"
#include "TicTacToeModel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
