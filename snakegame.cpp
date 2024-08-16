#include "snakegame.h"
#include <QPainter>
#include <QTime>

SnakeGame::SnakeGame(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color:black;");
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    resize(BoardWidth * DotSize, BoardHeight * DotSize);
    initGame();
}

SnakeGame::~SnakeGame() {}

void SnakeGame::initGame()
{
    snakeLength = 3;
    for (int i = 0; i < snakeLength; ++i) {
        snakeX[i] = 50 - i * DotSize;
        snakeY[i] = 50;
    }

    locateFood();
    dir = Right;
    inGame = true;
    timerId = startTimer(100);
}

void SnakeGame::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    doDrawing();
}

void SnakeGame::doDrawing()
{
    QPainter qp(this);

    if (inGame) {
        // Pinta a comida de vermelho
        qp.setBrush(Qt::red);
        qp.drawRect(foodX, foodY, DotSize, DotSize);

        // Pinta a cabeça de preto
        qp.setBrush(Qt::black);
        qp.drawRect(snakeX[0], snakeY[0], DotSize, DotSize);

        // Pinta o corpo de verde
        qp.setBrush(Qt::green);
        for (int i = 1; i < snakeLength; ++i) {
            qp.drawRect(snakeX[i], snakeY[i], DotSize, DotSize);
        }
    } else {
        gameOver(qp);
    }
}

void SnakeGame::gameOver(QPainter &qp)
{
    QString message = "Game Over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(message);

    qp.setPen(Qt::black);
    qp.setFont(font);
    qp.drawText(rect().center().x() - textWidth / 2, rect().center().y(), message);
}

void SnakeGame::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Left:
            if (dir != Right) dir = Left;
            break;
        case Qt::Key_Right:
            if (dir != Left) dir = Right;
            break;
        case Qt::Key_Up:
            if (dir != Down) dir = Up;
            break;
        case Qt::Key_Down:
            if (dir != Up) dir = Down;
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void SnakeGame::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if (inGame) {
        checkCollision();
        move();
    }

    repaint();
}

void SnakeGame::locateFood()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int r = qrand() % BoardWidth;
    foodX = r * DotSize;

    r = qrand() % BoardHeight;
    foodY = r * DotSize;
}

void SnakeGame::move()
{
    for (int i = snakeLength; i > 0; --i) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    switch (dir) {
        case Left:
            snakeX[0] -= DotSize;
            break;
        case Right:
            snakeX[0] += DotSize;
            break;
        case Up:
            snakeY[0] -= DotSize;
            break;
        case Down:
            snakeY[0] += DotSize;
            break;
    }
}

void SnakeGame::checkCollision()
{
    for (int i = snakeLength; i > 0; --i) {
        if ((i > 3) && (snakeX[0] == snakeX[i]) && (snakeY[0] == snakeY[i])) {
            inGame = false;
        }
    }

    if (snakeX[0] >= BoardWidth * DotSize || snakeX[0] < 0 ||
        snakeY[0] >= BoardHeight * DotSize || snakeY[0] < 0) {
        inGame = false;
    }

    if ((snakeX[0] <= foodX + DotSize) && (snakeX[0] + DotSize >= foodX) &&
        (snakeY[0] <= foodY + DotSize) && (snakeY[0] + DotSize >= foodY)) {
        snakeLength++;
        locateFood();
    }

    if (!inGame) {
        killTimer(timerId);
    }
}
