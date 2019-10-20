#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Sdraw"));
  /*  s=new GraphLibrary();
    setCentralWidget(s);
    s->setMinimumSize(400,400);*/
    setCentralWidget(ui->openGLWidget);
    //ui->openGLWidget->setMinimumSize(400,400);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionLine_toggled(bool arg1)
{
    qDebug()<<"line_chosen";
    ui->openGLWidget->setMode(Mode::line);
}
