#include "graphlibrary.h"
#include <Qdebug>
//#include <gl/glu.h>

GraphLibrary::GraphLibrary(QWidget *parent )
{
    curpid=0;
    curcolor[0]=1;
    curcolor[1]=0;
    curcolor[2]=0;
    ischoosen=false;
    setMode(Mode::choose);
    setSize(4);
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
    qDebug()<<"SetMode"<<mode;
    //unchoose();
    this->curmode=mode;
}

void GraphLibrary::setSize(int size)
{
    qDebug()<<"setsize";
    this->cursize=size;
}

void GraphLibrary::drawPoint(int x, int y)
{
    Point temp;
    temp.pid=curpid;
    temp.x=x;
    temp.y=y;
    temp.color[0]=curcolor[0];
    temp.color[1]=curcolor[1];
    temp.color[2]=curcolor[2];
    temp.mode=curmode;
    temp.choosen=false;
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
    curpid++;
}

void GraphLibrary::choose(int x, int y)
{
    qDebug()<<"choose";
    int temppid=-1;
    for(QVector<Point>::iterator iter=curboard.begin();iter != curboard.end();iter++)
    {
        if((abs(iter->x-x)<cursize)&&(abs(iter->y-y)<cursize))
        {
            temppid=iter->pid;
            iter->choosen=true;
            break;
        }
    }
    if(temppid!=-1)
    {
        ischoosen=true;
        choosenpid=temppid;
        for(QVector<Point>::iterator iter=curboard.begin();iter != curboard.end();iter++)
        {
            if(iter->pid==temppid)
            {
                iter->choosen=true;
            }
        }
    }
    else
    {
        ischoosen=false;
        unchoose();
    }
}

void GraphLibrary::unchoose()
{
    qDebug()<<"unchoose";
    for(QVector<Point>::iterator iter=curboard.begin();iter != curboard.end();iter++)
    {
        if(iter->choosen==true)
        {
            iter->choosen=false;
        }
    }

}

void GraphLibrary::OPT_delete()
{
    if(ischoosen==true)
    {
        for(QVector<Point>::iterator iter=curboard.begin();iter != curboard.end();iter++)
        {
            if(iter->pid==choosenpid)
            {
                 curboard.erase(iter);
                 iter--;
            }
        }
    }
}

void GraphLibrary::OPT_rotate()
{
    if(ischoosen==true)
    {

    }
}

void GraphLibrary::OPT_move()
{
    if(ischoosen==true)
    {

    }
}

void GraphLibrary::OPT_scale()
{
    if(ischoosen==true)
    {

    }
}

void GraphLibrary::OPT_clip()
{
    if(ischoosen==true)
    {

    }
}

void GraphLibrary::paintGL()
{
    //qDebug()<<"printGL"<<endl;
    glClear(GL_COLOR_BUFFER_BIT);
    for(QVector<Point>::iterator iter=curboard.begin();iter != curboard.end();iter++)
    {
       // qDebug()<<"x="<<iter->x<<" "<<"y="<<iter->y;
        if(iter->choosen==false)
        {
           // qDebug()<<"unchoose";
            glColor3d(iter->color[0],iter->color[1],iter->color[2]);
        }
        else
        {
            qDebug()<<"chosen";
            glColor3d(1,1,1);
        }
        glPointSize(cursize);
        glBegin(GL_POINTS);
        glVertex3f(iter->x,this->size().height()-iter->y,0);
      //  glVertex3f(iter->x,iter->y,0);
        glEnd();
    }
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
    qDebug()<<this->size().width();
    qDebug()<<this->size().height();
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, this->size().width(), 0, this->size().height(), -1, 1);
}

void GraphLibrary::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mode="<<curmode;
    if(event->button()==Qt::LeftButton)
    {
        switch(curmode)
        {
        case Mode::line:
        {
           start_x=event->pos().x();
           start_y=event->pos().y();
           break;
        }
        case Mode::circle:
        {

            break;
        }
        case Mode::choose:
        {
            choose(event->pos().x(),event->pos().y());
            break;
        }
        default:break;
        }
        qDebug()<<"left_start"<<event->pos().rx();
        qDebug()<<"left_start"<<event->pos().ry();

    }
    else if(event->button()==Qt::RightButton)
    {

         qDebug()<<"right_start"<<event->pos();
    }
    else if(event->button()==Qt::MidButton)
    {
        setMode(Mode::choose);
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
