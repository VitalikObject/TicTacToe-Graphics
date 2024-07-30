#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_stage(new Stage())
{
    setFixedSize(300, 300);
    setCentralWidget(m_stage);
}

MainWindow::~MainWindow() {
}
