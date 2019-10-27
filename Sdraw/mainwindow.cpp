#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
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
    qDebug()<<"line_chosen_dead";
   // ui->openGLWidget->setMode(Mode::line);
}

void MainWindow::on_actionLine_triggered()
{
    qDebug()<<"line_chosen";
    ui->openGLWidget->setMode(Mode::line);
}

void MainWindow::on_actionCircle_triggered()
{
    qDebug()<<"circle_chosen";
    ui->openGLWidget->setMode(Mode::circle);
}

void MainWindow::on_actionEllipse_triggered()
{
    qDebug()<<"ellipse_chosen";
    ui->openGLWidget->setMode(Mode::ellipse);
}

void MainWindow::on_actionDelete_triggered()
{
    qDebug()<<"delete";
    ui->openGLWidget->OPT_delete();
}

void MainWindow::on_actionColor_triggered()
{
    qDebug()<<this->size();
    QColor color=QColorDialog::getColor(Qt::red,this);
    int r;
    int b;
    int g;
    color.getRgb(&r, &g, &b);
    ui->openGLWidget->setColor(r,g,b);
}

void MainWindow::on_action_S_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
    QSize opsize(this->size());
    QPixmap oppicture(opsize);
    this->render(&oppicture);
    oppicture.save(filename);
}

void MainWindow::on_action_O_triggered()
{

}

void MainWindow::on_actionReadText_R_triggered()
{

}

void MainWindow::on_actionSize_triggered()
{
    ui->openGLWidget->setSize(5);
}


