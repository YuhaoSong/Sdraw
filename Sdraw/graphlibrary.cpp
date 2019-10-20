#include "graphlibrary.h"
#include <Qdebug>
GraphLibrary::GraphLibrary(QWidget *parent )
{
    curpid=0;
    curcolor[0]=1;
    curcolor[1]=170/255;
    curcolor[2]=0;
    setMode(line);
    //initializeGL();
   // paintGL();
    qDebug()<<"GraphLibrary"<<endl;
   // qDebug()<<"mode="<<curmode;
    update();
}

GraphLibrary::~GraphLibrary()
{
    qDebug()<<"~GraphLibrary"<<endl;
}

void GraphLibrary::setMode(Mode mode)
{
    this->curmode=mode;
}

void GraphLibrary::drawPoint(int x, int y)
{
    Point temp;
    temp.pid=curpid;
    curpid++;
    temp.x=x;
    temp.y=y;
    temp.color[0]=curcolor[0];
    temp.color[1]=curcolor[1];
    temp.color[2]=curcolor[2];
    temp.mode=curmode;
    curboard.push_back(temp);
}

void GraphLibrary::drawLine(int x1, int y1, int x2, int y2)
{
    qDebug()<<"drawline"<<endl;
    drawPoint(x1, y1);
    drawPoint(x2, y2);
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int flag = (dx >= dy) ? 0 : 1;
    int a = (x2 > x1) ? 1 : -1;
    int b = (y2 > y1) ? 1 : -1;
    int x = x1;
    int y = y1;
    if(flag){
        int temp = dx;
        dx = dy;
        dy = temp;
    }
    int h = 2 * dy - dx;
    for (int i = 1; i <= dx; ++i) {
        drawPoint(x, y);
        if (h >= 0) {
            if (!flag)
                    y += b;
            else
                    x += a;
            h -= 2 * dx;
        }
        if (!flag)
            x += a;
        else
            y += b;
        h += 2 * dy;
    }
}

void GraphLibrary::paintGL()
{
    //qDebug()<<"printGL"<<endl;
    glClear(GL_COLOR_BUFFER_BIT);
    for(QVector<Point>::iterator iter=curboard.begin();iter != curboard.end();iter++)
    {
       // qDebug()<<"x="<<iter->x<<" "<<"y="<<iter->y;
        //glColor3d(iter->color[0],iter->color[1],iter->color[2]);
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_POINTS);
        glVertex3d(1.0f,1.0f,0);
        glEnd();
    }
    /*glBegin(GL_TRIANGLES); // 绘制三角形（逆时针画出来的三角形才是正面朝着我们的）
        glColor3f(1.0,0.0,0.0);     // 设置当前色为红色
        glVertex3f(-1.0,-1.0, 0.0); // 左下顶点（//glVertex 的第一个参数是X坐标，然后依次是Y坐标和Z坐标）
        glColor3f(0.0,1.0,0.0);     // 设置当前色为绿色
        glVertex3f( 1.0,-1.0, 0.0); // 右下顶点
        glColor3f(0.0,0.0,1.0);     // 设置当前色为蓝色
        glVertex3f( 0.0, 1.0, 0.0); // 上顶点
      glEnd();*/
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

void GraphLibrary::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<"mode="<<curmode;
    if(event->button()==Qt::LeftButton)
    {
        switch(curmode)
        {
        case line:
        {
           start_x=event->pos().x();
           start_y=event->pos().y();
           break;
        }
        case circle:
        {

            break;
        }
        default:break;
        }
        qDebug()<<"left_start"<<event->pos();

    }
    else if(event->button()==Qt::RightButton)
    {

         qDebug()<<"right_start"<<event->pos();
    }
    else if(event->button()==Qt::MidButton)
    {
         qDebug()<<"mid_start"<<event->pos();
    }
}

void GraphLibrary::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        switch(curmode)
        {
        case line:
        {   //qDebug()<<"drawline";
           end_x=event->pos().x();
           end_y=event->pos().y();
           drawLine(start_x,start_y,end_x,end_y);
           break;
        }
        case circle:
        {

            break;
        }
        default:break;
        }

          qDebug()<<"left_end"<<event->pos();
    }
    else if(event->button()==Qt::RightButton)
    {

         qDebug()<<"right_end"<<event->pos();
    }
    else if(event->button()==Qt::MidButton)
    {
         qDebug()<<"mid_end"<<event->pos();
    }
}

void GraphLibrary::mouseMoveEvent(QMouseEvent *event)
{

}
