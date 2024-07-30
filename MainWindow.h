#pragma once

#include <QMainWindow>
#include "Stage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Stage* m_stage;
};
