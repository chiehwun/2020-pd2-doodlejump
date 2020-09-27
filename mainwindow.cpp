#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

extern Game *game;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->hide();
    ui->menuBar->hide();
    ui->mainToolBar->hide();
    setWindowTitle("Doodle Jump");

    game = new Game(ui->graphicsView);
    game->reset();

}

MainWindow::~MainWindow()
{
    delete ui;
}
