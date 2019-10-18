#include "graphlibrary.h"
#include <Qdebug>
GraphLibrary::GraphLibrary(QWidget *parent )
{
    //initializeGL();
   // paintGL();
    qDebug()<<"GraphLibrary"<<endl;
    update();
}

GraphLibrary::~GraphLibrary()
{
    qDebug()<<"~GraphLibrary"<<endl;
}

void GraphLibrary::setMode(int mode)
{
    this->mode=mode;
}

void GraphLibrary::paintGL()
{
    qDebug()<<"printGL"<<endl;
    glClear(GL_COLOR_BUFFER_BIT);
    /*for(QVector<Point>::iterator iter=curboard.begin();iter != curboard.end();iter++)
    {
        glColor3d(iter->color[0],iter->color[1],iter->color[2]);
        glBegin(GL_POINTS);
        glVertex3d(iter->x,iter->y,0);
    }*/
    glBegin(GL_TRIANGLES); // 绘制三角形（逆时针画出来的三角形才是正面朝着我们的）
        glColor3f(1.0,0.0,0.0);     // 设置当前色为红色
        glVertex3f(-1.0,-1.0, 0.0); // 左下顶点（//glVertex 的第一个参数是X坐标，然后依次是Y坐标和Z坐标）
        glColor3f(0.0,1.0,0.0);     // 设置当前色为绿色
        glVertex3f( 1.0,-1.0, 0.0); // 右下顶点
        glColor3f(0.0,0.0,1.0);     // 设置当前色为蓝色
        glVertex3f( 0.0, 1.0, 0.0); // 上顶点
      glEnd();
    update();
}

void GraphLibrary::initializeGL()
{
    qDebug()<<"initializeGL"<<endl;
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,0.0f);

}

void GraphLibrary::resizeGL(int w, int h)
{

    qDebug()<<"resizeGL"<<endl;

}
