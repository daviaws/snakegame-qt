#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "snakegame.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void restartGame();

private:
    QPushButton *restartButton;
    SnakeGame *game;
};

#endif // MAINWINDOW_H
