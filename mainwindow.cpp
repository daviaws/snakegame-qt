#include "mainwindow.h"

#include <QVBoxLayout>  // Para layout vertical

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Criar o jogo
    restartButton = new QPushButton("Start Game", this);
    game = nullptr;
    setCentralWidget(game);
    resize(400, 400);

    // Configurar o layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(restartButton);
    layout->addWidget(game);

    // Widget central
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Conectar o botão ao slot restartGame
    connect(restartButton, &QPushButton::clicked, this, &MainWindow::restartGame);

    resize(400, 450);  // Ajuste para acomodar o botão
}

MainWindow::~MainWindow()
{
    // Remove o jogo atual
    delete game;
    // Remove o botão
    delete restartButton;
}

void MainWindow::restartGame()
{
    // Remove o jogo atual
    delete game;
    // Cria um novo jogo
    game = new SnakeGame(this);
    // Adiciona o novo jogo ao layout
    centralWidget()->layout()->addWidget(game);
}
