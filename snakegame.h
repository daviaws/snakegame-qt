#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>

class SnakeGame : public QWidget
{
    Q_OBJECT

public:
    SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    enum { BoardWidth = 20, BoardHeight = 20, DotSize = 20, AllDots = 400 };
    int timerId;
    int snakeX[AllDots];
    int snakeY[AllDots];
    int snakeLength;
    int foodX;
    int foodY;
    bool inGame;
    enum Direction { Left, Right, Up, Down } dir;

    void initGame();
    void locateFood();
    void checkCollision();
    void move();
    void doDrawing();
    void gameOver(QPainter &qp);
};

#endif // SNAKEGAME_H
