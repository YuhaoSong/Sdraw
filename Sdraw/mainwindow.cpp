#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools.h"
#include <QDebug>
#include <QVector>
#include <QColorDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QLabel>
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

void MainWindow::on_actionRectangle_triggered()
{
    qDebug()<<"rectangle_chosen";
    ui->openGLWidget->setMode(Mode::rectangle);
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
    QString filename = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("*.bmp;;*.png;;*.jpg;;*.tif;;*.gif")); //选择路径
    qDebug()<<filename<<endl;
    QSize opsize(this->ui->openGLWidget->size());
    QPixmap oppicture(opsize);
    this->ui->openGLWidget->render(&oppicture);
    oppicture.save(filename);
}

void MainWindow::on_action_O_triggered()
{

}

void MainWindow::on_actionReadText_R_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open order in text"), "", tr("Normal text file (*.txt);;All (*.*)"));
    QFile file(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        qDebug()<<str;
        QStringList strList=str.split(" ");
        if(strList[0]=="resetCanvas")
        {
            qDebug()<<"do reset";
            int w=strList[1].toInt();
            int h=strList[2].toInt();
            ui->openGLWidget->clear();
            ui->openGLWidget->setFixedSize(w,h);
            this->setFixedSize(w,h+45);
        }
        else if(strList[0]=="saveCanvas")
        {
                  qDebug()<<"do save";
            QString file=strList[1].trimmed();
            QString filename = "D:/"+file+".bmp";
            QSize opsize(this->ui->openGLWidget->size());
            QPixmap oppicture(opsize);
            this->ui->openGLWidget->render(&oppicture);
            oppicture.save(filename);
        }
        else if(strList[0]=="setColor")
        {
            qDebug()<<"do color";
            int r=strList[1].toInt();
            int g=strList[2].toInt();
            int b=strList[3].toInt();
            ui->openGLWidget->setColor(r,g,b);

        }
        else if(strList[0]=="drawLine")
        {
            qDebug()<<"do line";
            qDebug()<<"color="<<ui->openGLWidget->curcolor[0]<<ui->openGLWidget->curcolor[1]<<ui->openGLWidget->curcolor[2];
            int id=strList[1].toInt();
            int x1=strList[2].toInt();
            int y1=strList[3].toInt();
            int x2=strList[4].toInt();
            int y2=strList[5].toInt();
            QString algro=strList[6].trimmed();
            if(algro=="DDA")
            {
                ui->openGLWidget->aflag=DDA;
            }
            else
            {
                ui->openGLWidget->aflag=Bresenham;
            }
            ui->openGLWidget->ischoosen=true;
            ui->openGLWidget->curpid=id;
            Dictionary x;
            x.pid=id;
            x.mode=Mode::line;
            x.para.push_back(x1);
            x.para.push_back(y1);
            x.para.push_back(x2);
            x.para.push_back(y2);
            x.color[0]=ui->openGLWidget->curcolor[0];
            x.color[1]=ui->openGLWidget->curcolor[1];
            x.color[2]=ui->openGLWidget->curcolor[2];
            ui->openGLWidget->dictionary.push_back(x);
            ui->openGLWidget->drawLine(x);
            ui->openGLWidget->unchoose();
        }
        else if(strList[0]=="drawEllipse")
        {
                  qDebug()<<"do ellipse";
            int id=strList[1].toInt();
            int x1=strList[2].toInt();
            int y1=strList[3].toInt();
            int x2=strList[4].toInt();
            int y2=strList[5].toInt();
            ui->openGLWidget->ischoosen=true;
            ui->openGLWidget->curpid=id;
            Dictionary x;
            x.pid=id;
            x.mode=Mode::ellipse;
            x.para.push_back(x1);
            x.para.push_back(y1);
            x.para.push_back(x2);
            x.para.push_back(y2);
            x.color[0]=ui->openGLWidget->curcolor[0];
            x.color[1]=ui->openGLWidget->curcolor[1];
            x.color[2]=ui->openGLWidget->curcolor[2];
            ui->openGLWidget->dictionary.push_back(x);
            ui->openGLWidget->drawEllipse(x);
            ui->openGLWidget->unchoose();
        }
        else if(strList[0]=="drawPolygon")
        {
            qDebug()<<"do polygon";
            int id=strList[1].toInt();
            int n=strList[2].toInt();
            QString algro=strList[3].trimmed();
            if(algro=="DDA")
            {
                ui->openGLWidget->aflag=DDA;
            }
            else
            {
                ui->openGLWidget->aflag=Bresenham;
            }
            QByteArray tline = file.readLine();
            QString tstr(tline);
            qDebug()<<tstr;
            QStringList tstrList=tstr.split(" ");
            Dictionary x;
            x.pid=id;
            x.mode=Mode::polygon;
            for(int i=0;i<2*n;i++)
            {
                x.para.push_back(tstrList[i].toInt());
            }
            x.color[0]=ui->openGLWidget->curcolor[0];
            x.color[1]=ui->openGLWidget->curcolor[1];
            x.color[2]=ui->openGLWidget->curcolor[2];
            ui->openGLWidget->ischoosen=true;
            ui->openGLWidget->curpid=id;
            ui->openGLWidget->dictionary.push_back(x);
            ui->openGLWidget->drawPolygon(x);
            ui->openGLWidget->unchoose();
        }
        else if(strList[0]=="drawCurve")
        {
            int id=strList[1].toInt();
            int n=strList[2].toInt();
            QString algro=strList[3].trimmed();
            if(algro=="Bezier")
            {
                ui->openGLWidget->aflag=Algro::Bezier;
            }
            else
            {
                ui->openGLWidget->aflag=Algro::Bspline;
            }
            QByteArray tline = file.readLine();
            QString tstr(tline);
            qDebug()<<tstr;
            QStringList tstrList=tstr.split(" ");
            Dictionary x;
            x.pid=id;
            x.mode=Mode::curve;
            for(int i=0;i<2*n;i++)
            {
                x.para.push_back(tstrList[i].toInt());
            }
            x.color[0]=ui->openGLWidget->curcolor[0];
            x.color[1]=ui->openGLWidget->curcolor[1];
            x.color[2]=ui->openGLWidget->curcolor[2];
            ui->openGLWidget->ischoosen=true;
            ui->openGLWidget->curpid=id;
            ui->openGLWidget->dictionary.push_back(x);
            ui->openGLWidget->drawCurve(x);
            ui->openGLWidget->unchoose();
        }
        else if(strList[0]=="translate")
        {
                  qDebug()<<"do trans";
            int id=strList[1].toInt();
            int x=strList[2].toInt();
            int y=strList[3].toInt();
            ui->openGLWidget->ischoosen=true;
            ui->openGLWidget->choosenpid=id;
            ui->openGLWidget->OPT_move(x,y);
            ui->openGLWidget->unchoose();

        }
        else if(strList[0]=="rotate")
        {
           qDebug()<<"do rotate";
           int id=strList[1].toInt();
            int x=strList[2].toInt();
            int y=strList[3].toInt();
            int r=strList[4].toInt();
            ui->openGLWidget->ischoosen=true;
            ui->openGLWidget->choosenpid=id;
            qDebug()<<"show the rotate id"<<id;
            ui->openGLWidget->OPT_rotate(x,y,r);
            ui->openGLWidget->unchoose();
        }
        else if(strList[0]=="scale")
        {
             qDebug()<<"do scale";
            int id=strList[1].toInt();
             int x=strList[2].toInt();
             int y=strList[3].toInt();
             float s=strList[4].toFloat();
             ui->openGLWidget->ischoosen=true;
             ui->openGLWidget->choosenpid=id;
             ui->openGLWidget->OPT_scale(x,y,s);
             ui->openGLWidget->unchoose();
        }
        else if(strList[0]=="clip")
        {
                  qDebug()<<"do clip";
            int id=strList[1].toInt();
            int x1=strList[2].toInt();
            int y1=strList[3].toInt();
            int x2=strList[4].toInt();
            int y2=strList[5].toInt();
             QString algro=strList[6].trimmed();
             qDebug()<<id<<" "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<algro;
             if(algro=="Cohen-Sutherland")
             {
                 qDebug()<<"cohen";
                 ui->openGLWidget->aflag=CohenSutherland;
             }
             else
             {

                 qDebug()<<"liang";
                 ui->openGLWidget->aflag=LiangBarsky;
             }
             ui->openGLWidget->ischoosen=true;
            ui->openGLWidget->choosenpid=id;
            ui->openGLWidget->OPT_clip(x1,y1,x2,y2);
            ui->openGLWidget->unchoose();
        }
        else
        {
            break;
        }

    }
    file.close();
}

void MainWindow::on_actionSize_triggered()
{
    bool ok;
    int x=QInputDialog::getInt(this,tr("Set size"),tr("Please input the size"),1,0,100,1,&ok);
    if(ok)
    {
        ui->openGLWidget->setSize(x);
    }
}

void MainWindow::on_actionClip_triggered()
{
    ui->openGLWidget->setMode(Mode::clip);
}

void MainWindow::on_actionMove_triggered()
{
    ui->openGLWidget->setMode(Mode::move);
}

void MainWindow::on_actionScale_triggered()
{
    bool ok;
    double x=QInputDialog::getDouble(this,tr("Set angle"),tr("Please input the angle"),1,0,100,1,&ok);
    if(ok)
    {
        ui->openGLWidget->setScale(x);
    }
    ui->openGLWidget->setMode(Mode::scale);
}

void MainWindow::on_actionRotate_triggered()
{
    bool ok;
    int x=QInputDialog::getInt(this,tr("Set angle"),tr("Please input the angle"),1,0,100,1,&ok);
    if(ok)
    {
        ui->openGLWidget->setAngle(x);
    }
    ui->openGLWidget->setMode(Mode::rotate);
}

void MainWindow::on_actionReset_triggered()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("User input:"));
    // Value1
    QString value1 = QString("Width: ");
    QSpinBox *spinbox1 = new QSpinBox(&dialog);
    spinbox1->setMaximum(10000);
    spinbox1->setMinimum(20);
    form.addRow(value1, spinbox1);
    // Value2
    QString value2 = QString("Height: ");
    QSpinBox *spinbox2 = new QSpinBox(&dialog);
    spinbox2->setMinimum(20);
    spinbox2->setMaximum(10000);
    form.addRow(value2, spinbox2);
    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    // Process when OK button is clicked
    if (dialog.exec() == QDialog::Accepted) {
       ui->openGLWidget->setFixedSize(spinbox1->value(),spinbox2->value());
       this->setFixedSize(spinbox1->value(),spinbox2->value()+45);
        qDebug()<<"w is"<<ui->openGLWidget->width()<<"  h is"<<ui->openGLWidget->height()<<endl;
    }
}

void MainWindow::on_actionChoose_by_area_triggered()
{
    ui->openGLWidget->setMode(Mode::choose);
}

void MainWindow::on_actionPolygon_triggered()
{
    ui->openGLWidget->setMode(Mode::polygon);
}

void MainWindow::on_actionClear_triggered()
{
    ui->openGLWidget->clear();
}

void MainWindow::on_actionCurve_triggered()
{
    ui->openGLWidget->setMode(Mode::curve);
}
