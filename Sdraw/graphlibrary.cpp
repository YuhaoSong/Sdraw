#include "graphlibrary.h"
#include <Qdebug>
#include <QtMath>
//#include <gl/glu.h>

GraphLibrary::GraphLibrary(QWidget *parent )
{
    curpid=0;
    curcolor[0]=0;
    curcolor[1]=0;
    curcolor[2]=0;
    ischoosen=false;
    setMode(Mode::choose);
    setSize(1);
    setAlgro(Bresenham);
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

void GraphLibrary::setColor(int r, int g, int b)
{
    curcolor[0]=r/255;
    curcolor[1]=g/255;
    curcolor[2]=b/255;
}

void GraphLibrary::setAlgro(Algro x)
{
    aflag=x;
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
    temp.size=cursize;
    curboard.push_back(temp);
}

void GraphLibrary::drawLine(int x1, int y1, int x2, int y2)
{

    qDebug()<<"drawline"<<endl;
    if(aflag==DDA)
    {
        double delta_x, delta_y, x, y;
        int dx, dy, dist;
        dx = x2 - x1;
        dy = y2 - y1;
        dist=(abs(dx)>abs(dy))?abs(dx):abs(dy);
        delta_x = (double)dx / (double)dist;
        delta_y = (double)dy / (double)dist;
        x = x1;
        y = y1;
        for (int i = 1; i <= dist; i++)
        {
            drawPoint(x,y);
            x += delta_x;
            y += delta_y;
         }
    }
    else if(aflag==Bresenham)
    {
        int x, y, dx, dy, s1, s2, p;
        x=x1; y=y1;
        dx=abs(x2-x1);
        dy=abs(y2-y1);
        s1=(x2>x1)?1:-1;
        s2=(y2>y1)?1:-1;
        if(dy<dx)
        {
            p=2*dy-dx;
            for(int i=1;i<=dx;i++)
            {
                drawPoint(x,y);
                if(p>=0)
                {
                    y=y+s2;
                    p=p-2*dx;
                }
                x=x+s1;
                p=p+2*dy;
             }
        }
        else
        {
            p=2*dx-dy;
            for(int i=1;i<=dy;i++)
            {
                drawPoint(x,y);
                if(p>=0)
                {
                    x=x+s1;
                    p=p-2*dy;
                }
                y=y+s2;
                p=p+2*dx;
             }
        }
    }
}

void GraphLibrary::drawCircle(int x1, int y1, int x2, int y2)
{
    double circleR=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    int p=5-4*circleR;
    int x=0;int y=circleR;
    drawPoint(x1+x,y1+y);
    drawPoint(x1+x,y1-y);
    drawPoint(x1+y,y1+x);
    drawPoint(x1-y,y1+x);
    while(x<y)
    {

        x++;
        if (p < 0)
            p=p + 8 * x + 12;
        else{
            p = p + 8 * (x - y) + 20;
            y--;
        }
        drawPoint(x1+x,y1+y);
        drawPoint(x1-x,y1+y);
        drawPoint(x1+x,y1-y);
        drawPoint(x1-x,y1-y);
        drawPoint(x1+y,y1+x);
        drawPoint(x1-y,y1+x);
        drawPoint(x1+y,y1-x);
        drawPoint(x1-y,y1-x);
    }
}

void GraphLibrary::drawEllipse(int x1, int y1, int x2, int y2)
{
    int Rx=abs((x1-x2)/2);
    int Ry=abs((y1-y2)/2);
    int xc=(x1+x2)/2;
    int yc=(y1+y2)/2;
    int x=0;int y=Ry;
    int p=Ry*Ry-Rx*Rx*Ry+Rx*Rx/4;
    drawPoint(xc+x,yc+y);
    drawPoint(xc+x,yc-y);
    while(Ry*Ry*x<Rx*Rx*y)
    {
        x++;
        if(p<0)
        {
            p=p+2*Ry*Ry*x+Ry*Ry;
        }
        else if(p>=0)
        {
            p=p+2*Ry*Ry*x-2*Rx*Rx*y+2*Rx*Rx+Ry*Ry;
            y--;
        }
        drawPoint(xc+x,yc+y);
        drawPoint(xc-x,yc+y);
        drawPoint(xc+x,yc-y);
        drawPoint(xc-x,yc-y);

    }
   p=Ry*Ry*(x+1/2)*(x+1/2)+Rx*Rx*(y-1)*(y-1)-Rx*Rx*Ry*Ry;
    while(y>0)
    {
        y--;
        if(p>0)
        {
            p=p-2*Rx*Rx*y+Rx*Rx;
        }
        else if(p<=0)
        {
            x++;
            p=p+2*Ry*Ry*x-2*Rx*Rx*y+Rx*Rx;

        }
        drawPoint(xc+x,yc+y);
        drawPoint(xc-x,yc+y);
        drawPoint(xc+x,yc-y);
        drawPoint(xc-x,yc-y);
    }
}

void GraphLibrary::drawRectangle(int x1, int y1, int x2, int y2)
{
    drawLine(x1,y1,x1,y2);
    drawLine(x2,y1,x2,y2);
    drawLine(x1,y1,x2,y1);
    drawLine(x1,y2,x2,y2);
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
                iter->color[0]=iter->color[0]/2;
                iter->color[1]=iter->color[1]/2;
                iter->color[2]=iter->color[2]/2;
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
            iter->color[0]=iter->color[0]*2;
            iter->color[1]=iter->color[1]*2;
            iter->color[2]=iter->color[2]*2;
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

void GraphLibrary::OPT_rotate(int x,int y,double r)
{
    if(ischoosen==true)
    {
        for(QVector<Point>::iterator iter=curboard.begin();iter != curboard.end();iter++)
        {
            if(iter->pid==choosenpid)
            {

                double c=cos(r);
                double s=sin(r);
                iter->x=x+(iter->x-x)*c-(iter->y-y)*s;
                iter->y=y+(iter->x-x)*s+(iter->y-y)*c;
            }
        }
    }
}

void GraphLibrary::OPT_move(int x,int y)
{
    if(ischoosen==true)
    {
        for(QVector<Point>::iterator iter=curboard.begin();iter != curboard.end();iter++)
        {
            if(iter->pid==choosenpid)
            {
                iter->x+=x;
                iter->y+=y;
            }
        }
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

void GraphLibrary::read_text(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        QStringList strList=str.split(" ");
        if(strList[0]=="resetCanvas")
        {
            int w=strList[1].toInt();
            int h=strList[2].toInt();
            qDebug()<<w<<" "<<h<<" "<<strList[2];
            //TODO
        }
        else if(strList[0]=="saveCanvas")
        {
            QString filename=strList[1].trimmed();
            //TODO
        }
        else if(strList[0]=="setColor")
        {
            int r=strList[1].toInt();
            int g=strList[2].toInt();
            int b=strList[3].toInt();
            this->setColor(r,g,b);

        }
        else if(strList[0]=="drawLine")
        {
            int id=strList[1].toInt();
            int x1=strList[2].toInt();
            int y1=strList[3].toInt();
            int x2=strList[4].toInt();
            int y2=strList[5].toInt();
            QString algro=strList[6].trimmed();
            if(algro=="DDA")
            {
                aflag=DDA;
            }
            else
            {
                aflag=Bresenham;
            }
            curpid=id;
            drawLine(x1,y1,x2,y2);
        }
        else if(strList[0]=="drawEllipse")
        {
            int id=strList[1].toInt();
            int x1=strList[2].toInt();
            int y1=strList[3].toInt();
            int x2=strList[4].toInt();
            int y2=strList[5].toInt();
            curpid=id;
            drawEllipse(x1,y1,x2,y2);
        }
        else if(strList[0]=="drawPolygon")
        {

        }
        else if(strList[0]=="drawCurve")
        {

        }
        else if(strList[0]=="translate")
        {

        }
        else if(strList[0]=="rotate")
        {

        }
        else if(strList[0]=="scale")
        {

        }
        else if(strList[0]=="clip")
        {

        }
        for(int i=0;i<strList.size();i++)
        {

        }

    }
    file.close();
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
            glColor3d(0.5,0.5,0.5);
        }
        glPointSize(iter->size);
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
    glClearColor(1.0f,1.0f,1.0f,1.0f);
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
            start_x=event->pos().x();
            start_y=event->pos().y();
            break;
        }
        case Mode::ellipse:
        {
            start_x=event->pos().x();
            start_y=event->pos().y();
            break;
        }
        case Mode::rectangle:
        {
            start_x=event->pos().x();
            start_y=event->pos().y();
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
           curpid++;
           break;
        }
        case circle:
        {
            end_x=event->pos().x();
            end_y=event->pos().y();
            drawCircle(start_x,start_y,end_x,end_y);
            curpid++;
            break;
        }
        case ellipse:
        {
            end_x=event->pos().x();
            end_y=event->pos().y();
            drawEllipse(start_x,start_y,end_x,end_y);
            curpid++;
            break;
        }
        case rectangle:
        {
            end_x=event->pos().x();
            end_y=event->pos().y();
            drawRectangle(start_x,start_y,end_x,end_y);
            curpid++;
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
