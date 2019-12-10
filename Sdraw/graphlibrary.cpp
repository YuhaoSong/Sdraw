#include "graphlibrary.h"
#include <Qdebug>
#include <QtMath>
#include <gl/glu.h>

GraphLibrary::GraphLibrary(QWidget *parent )
{
    curpid=1;
    curcolor[0]=0;
    curcolor[1]=0;
    curcolor[2]=0;
    ischoosen=false;
    tempP=false;
    setMode(Mode::choose);
    setSize(1);
    setLAlgro(Bresenham);
    setCAlgro(LiangBarsky);
    setCuAlgro(CuAlgro::Bezier);
    myC();
    polygonf=false;
    curvenf=false;
    setK(2);
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

void GraphLibrary::setColor(double r, double g, double b)
{
    curcolor[0]=r/255.0;
    curcolor[1]=g/255.0;
    curcolor[2]=b/255.0;
}

void GraphLibrary::setLAlgro(LAlgro x)
{
    Laflag=x;
}

void GraphLibrary::setCAlgro(CAlgro x)
{
    Caflag=x;
}

void GraphLibrary::setCuAlgro(CuAlgro x)
{
    Cuaflag=x;
}



void GraphLibrary::setAngle(int x)
{
    angle=x;
}

void GraphLibrary::setScale(double x)
{
    scale=x;
}

void GraphLibrary::setK(int x)
{
    K=x;
}


void GraphLibrary::drawPoint(int x, int y,int pid)
{
    Point temp;
    temp.pid=pid;
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

void GraphLibrary::drawTemp(int x, int y)
{
    Point temp;
    temp.pid=0;
    temp.x=x;
    temp.y=y;
    temp.color[0]=curcolor[0];
    temp.color[1]=curcolor[1];
    temp.color[2]=curcolor[2];
    temp.mode=Mode::temp;
    temp.choosen=false;
    temp.size=cursize;
    tempboard.push_back(temp);
}

void GraphLibrary::drawTline(Dictionary temp)
{
    int x1=temp.para[0];
    int y1=temp.para[1];
    int x2=temp.para[2];
    int y2=temp.para[3];
    int tcolor[3];
    tcolor[0]=curcolor[0];
    tcolor[1]=curcolor[1];
    tcolor[2]=curcolor[2];
    curcolor[0]=255;
    curcolor[1]=0;
    curcolor[2]=0;
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
            if(i%2==0)
            {
               drawTemp(x,y);
            }
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
            if(i%2==0)
            {
               drawTemp(x,y);
            }
            if(p>=0)
            {
                x=x+s1;
                p=p-2*dy;
            }
            y=y+s2;
            p=p+2*dx;
        }
    }
    drawTemp(x2,y2);
    curcolor[0]=tcolor[0];
    curcolor[1]=tcolor[1];
    curcolor[2]=tcolor[2];
}


void GraphLibrary::drawLine(Dictionary temp)
{
    int x1=temp.para[0];
    int y1=temp.para[1];
    int x2=temp.para[2];
    int y2=temp.para[3];
    qDebug()<<"drawline"<<endl;
    if(Laflag==DDA)
    {
        double delta_x, delta_y, x, y;
        int dx, dy, dist;
        dx = x2 - x1;
        dy = y2 - y1;
        dist=(abs(dx)>abs(dy))?abs(dx):abs(dy);
        delta_x = (double)dx / (double)dist;
        delta_y = (double)dy / (double)dist;
        x = x1+0.5;
        y = y1+0.5;
        for (int i = 1; i <= dist; i++)
        {
            drawPoint(x,y,temp.pid);
            x += delta_x;
            y += delta_y;
        }
        drawPoint(x2,y2,temp.pid);
    }
    else if(Laflag==Bresenham)
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
                drawPoint(x,y,temp.pid);
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
                drawPoint(x,y,temp.pid);
                if(p>=0)
                {
                    x=x+s1;
                    p=p-2*dy;
                }
                y=y+s2;
                p=p+2*dx;
             }
        }
        drawPoint(x2,y2,temp.pid);
    }
}

void GraphLibrary::drawCircle(Dictionary temp)
{
    int x1=temp.para[0];
    int y1=temp.para[1];
    int x2=temp.para[2];
    int y2=temp.para[3];
    double circleR=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    int p=5-4*circleR;
    int x=0;int y=circleR;
    drawPoint(x1+x,y1+y,temp.pid);
    drawPoint(x1+x,y1-y,temp.pid);
    drawPoint(x1+y,y1+x,temp.pid);
    drawPoint(x1-y,y1+x,temp.pid);
    while(x<y)
    {

        x++;
        if (p < 0)
            p=p + 8 * x + 12;
        else{
            p = p + 8 * (x - y) + 20;
            y--;
        }
        drawPoint(x1+x,y1+y,temp.pid);
        drawPoint(x1-x,y1+y,temp.pid);
        drawPoint(x1+x,y1-y,temp.pid);
        drawPoint(x1-x,y1-y,temp.pid);
        drawPoint(x1+y,y1+x,temp.pid);
        drawPoint(x1-y,y1+x,temp.pid);
        drawPoint(x1+y,y1-x,temp.pid);
        drawPoint(x1-y,y1-x,temp.pid);
    }
}

void GraphLibrary::drawEllipse(Dictionary temp)
{
    int xc=temp.para[0];
    int yc=temp.para[1];
    int Rx=temp.para[2];
    int Ry=temp.para[3];
  //  int Rx=abs((x1-x2)/2);
  //  int Ry=abs((y1-y2)/2);
  //  int xc=(x1+x2)/2;
  //  int yc=(y1+y2)/2;
    int x=0;int y=Ry;
    int p=Ry*Ry-Rx*Rx*Ry+Rx*Rx/4;
    drawPoint(xc+x,yc+y,temp.pid);
    drawPoint(xc+x,yc-y,temp.pid);
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
        drawPoint(xc+x,yc+y,temp.pid);
        drawPoint(xc-x,yc+y,temp.pid);
        drawPoint(xc+x,yc-y,temp.pid);
        drawPoint(xc-x,yc-y,temp.pid);

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
        drawPoint(xc+x,yc+y,temp.pid);
        drawPoint(xc-x,yc+y,temp.pid);
        drawPoint(xc+x,yc-y,temp.pid);
        drawPoint(xc-x,yc-y,temp.pid);
    }
}

void GraphLibrary::drawRectangle(Dictionary temp)
{
    qDebug()<<temp.para[0]<<" "<<temp.para[0]<<" "<<temp.para[2]<<" "<<temp.para[3];
    Dictionary x1;
    x1.pid=temp.pid;
    qDebug()<<temp.pid;
    x1.para.push_back(temp.para[0]);
    x1.para.push_back(temp.para[1]);
    x1.para.push_back(temp.para[0]);
    x1.para.push_back(temp.para[3]);
    qDebug()<<"drawRectangle";
    drawLine(x1);
    Dictionary x2;
    x2.pid=temp.pid;
    x2.para.push_back(temp.para[2]);
    x2.para.push_back(temp.para[1]);
    x2.para.push_back(temp.para[2]);
    x2.para.push_back(temp.para[3]);
    drawLine(x2);
    Dictionary x3;
    x3.pid=temp.pid;
    x3.para.push_back(temp.para[0]);
    x3.para.push_back(temp.para[1]);
    x3.para.push_back(temp.para[2]);
    x3.para.push_back(temp.para[1]);
    drawLine(x3);
    Dictionary x4;
    x4.pid=temp.pid;
    x4.para.push_back(temp.para[0]);
    x4.para.push_back(temp.para[3]);
    x4.para.push_back(temp.para[2]);
    x4.para.push_back(temp.para[3]);
    drawLine(x4);
}

void GraphLibrary::drawPolygon(Dictionary temp)
{
    qDebug()<<"draw teh fucking polygon";
    qDebug()<<"show the fucking id"<<temp.pid;
    for(int i=0;i<temp.para.size()-3;i=i+2)
    {
        Dictionary x1;
        x1.pid=temp.pid;
        x1.para.push_back(temp.para[i]);
        x1.para.push_back(temp.para[i+1]);
        x1.para.push_back(temp.para[i+2]);
        x1.para.push_back(temp.para[i+3]);
        drawLine(x1);
    }
    Dictionary x2;
    x2.pid=temp.pid;
    x2.para.push_back(temp.para[0]);
    x2.para.push_back(temp.para[1]);
    x2.para.push_back(temp.para[temp.para.size()-2]);
    x2.para.push_back(temp.para[temp.para.size()-1]);
    drawLine(x2);
}

void GraphLibrary::drawCurve(Dictionary temp)
{
    qDebug()<<"drawCurve";
    int num=temp.para.size();
    num=num/2;
    qDebug()<<num;
    int *x=new int[num];
    int *y=new int[num];
    for(int i=0;i<num;i++)
    {
        x[i]=temp.para[2*i];
        y[i]=temp.para[2*i+1];
        qDebug()<<"x"<<i<<"="<<x[i]<<"y"<<i<<"="<<y[i];
    }
    if(Cuaflag==CuAlgro::Bezier)
    {
        for(double t=0;t<=1;t=t+0.0005)
        {
            double tx=0;double ty=0;
            for(int k=0;k<num;k++)
            {
               // qDebug()<<"C"<<num<<" "<<k+1<<"="<<C[num][k+1];
                tx+=(double)x[k]*(double)C[num-1][k]*(double)pow(t,k)*(double)pow(1-t,num-k-1);
                ty+=(double)y[k]*(double)C[num-1][k]*(double)pow(t,k)*(double)pow(1-t,num-k-1);
            }
            qDebug()<<"tx="<<tx<<"ty="<<ty;
            drawPoint(tx,ty,temp.pid);
        }
    }
    else if(Cuaflag==CuAlgro::Bspline)
    {
        U.clear();
        for(double i=0.0;i<=num+K+1;i=i+1.0)
        {
            U.push_back(i/(num+K+1));
            qDebug()<<U[i];
        }
        qDebug()<<"U is size of"<<U.size();
        for (double u = U[K]; u <=U[num]; u=u+0.0005)
        {
           double tx = 0.0;
           double ty = 0.0;
           for (int i = 0; i <num; i++)
           {
                double Nik = deBoor_Cox(i, K, u); // 基函数
                tx += Nik*x[i];
                ty += Nik*y[i];
                qDebug()<<"i="<<i<<"xi="<<x[i]<<"yi="<<y[i]<<"Nik="<<Nik<<"tx="<<tx<<"ty="<<ty;
           }
           drawPoint(tx,ty,temp.pid);
        }
        U.clear();
    }
    delete []x;
    delete []y;
}

double GraphLibrary::deBoor_Cox(int i, int k, double u)
{
    if (k == 0)
    {
        if (u >= U[i] && u < U[i + 1])
            return 1.0;
        else
            return 0.0;
    }
    double den1 = U[i + k] - U[i];
    double den2 = U[i + k + 1] - U[i + 1];
    double a = 0, b = 0;
    if (den1 == 0 && den2 == 0)
    {
        a = 1;
        b = 1;
    }
    else if (den1 != 0 && den2 == 0)
    {
        a = (double)(u - U[i]) / den1;
        b = 1;
    }
    else if (den1 == 0 && den2 != 0)
    {
        a = 1;
        b = (double)(U[i + k + 1] - u) / den2;
    }
    else
    {
        a = (double)(u - U[i]) / den1;
        b = (double)(U[i + k + 1] - u) / den2;
    }

    return a*deBoor_Cox(i, k - 1, u) + b*deBoor_Cox(i + 1, k - 1, u);
}

void GraphLibrary:: choose(int x, int y)
{
    qDebug()<<"choose";
    int temppid=-1;
    for(QVector<Point>::iterator iter=curboard.begin();iter != curboard.end();iter++)
    {
        if((abs(iter->x-x)<5)&&(abs(iter->y-y)<5))
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

void GraphLibrary::clear()
{
    curboard.clear();
}

void GraphLibrary::unchoose()
{
    qDebug()<<"unchoose";
    if(ischoosen==true)
    {
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
    ischoosen=false;
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
        QVector<Dictionary>::iterator iter;
        for(iter=dictionary.begin();iter!=dictionary.end();iter++)
        {
            if(iter->pid==choosenpid)
            {
                qDebug()<<iter->mode;
                break;
            }
        }

        OPT_delete();
        double c=cos((r*M_PI)/180);
        double s=sin((r*M_PI)/180);
        qDebug()<<"c="<<c<<"s="<<s;
        qDebug()<<"size="<<iter->para.size();
        qDebug()<<"centerx="<<x<<"centery="<<y;
      //  qDebug()<<"length="<<sqrt((iter->para[0]-iter->para[2])*(iter->para[0]-iter->para[2])+(iter->para[1]-iter->para[3])*(iter->para[1]-iter->para[3]))<<endl;
        for(int i=0;i<iter->para.size();i=i+2)
        {
            double temp=iter->para[i];
            qDebug()<<"oldx="<<iter->para[i]<<"oldy="<<iter->para[i+1];
            iter->para[i]=x+(iter->para[i]-x)*c-(iter->para[i+1]-y)*s;
             qDebug()<<"y="<<y<<"iter->para[i]-x*s="<<(iter->para[i]-x)*s<<"(iter->para[i+1]-y)*c="<<(iter->para[i+1]-y)*c;
            iter->para[i+1]=y+(temp-x)*s+(iter->para[i+1]-y)*c;
            qDebug()<<"newx="<<iter->para[i]<<"newy="<<iter->para[i+1];
        }
        //qDebug()<<"length="<<sqrt((iter->para[0]-iter->para[2])*(iter->para[0]-iter->para[2])+(iter->para[1]-iter->para[3])*(iter->para[1]-iter->para[3]))<<endl;
        qDebug()<<"here";
        switch(iter->mode)
        {
        case Mode::circle:
        {
            double tcolor[3];
            tcolor[0]=curcolor[0];
            tcolor[1]=curcolor[1];
            tcolor[2]=curcolor[2];
            curcolor[0]=iter->color[0];
            curcolor[1]=iter->color[1];
            curcolor[2]=iter->color[2];
            drawCircle(*iter);
            curcolor[0]=tcolor[0];
            curcolor[1]=tcolor[1];
            curcolor[2]=tcolor[2];
            break;
        }
        case Mode::line:
        {
            double tcolor[3];
            tcolor[0]=curcolor[0];
            tcolor[1]=curcolor[1];
            tcolor[2]=curcolor[2];
            curcolor[0]=iter->color[0];
            curcolor[1]=iter->color[1];
            curcolor[2]=iter->color[2];
            drawLine(*iter);
            curcolor[0]=tcolor[0];
            curcolor[1]=tcolor[1];
            curcolor[2]=tcolor[2];
            break;
        }
        case Mode::ellipse:
        {
            double tcolor[3];
            tcolor[0]=curcolor[0];
            tcolor[1]=curcolor[1];
            tcolor[2]=curcolor[2];
            curcolor[0]=iter->color[0];
            curcolor[1]=iter->color[1];
            curcolor[2]=iter->color[2];
            drawEllipse(*iter);
            curcolor[0]=tcolor[0];
            curcolor[1]=tcolor[1];
            curcolor[2]=tcolor[2];
            break;
        }
        case Mode::rectangle:
        {
            double tcolor[3];
            tcolor[0]=curcolor[0];
            tcolor[1]=curcolor[1];
            tcolor[2]=curcolor[2];
            curcolor[0]=iter->color[0];
            curcolor[1]=iter->color[1];
            curcolor[2]=iter->color[2];
            drawRectangle(*iter);
            curcolor[0]=tcolor[0];
            curcolor[1]=tcolor[1];
            curcolor[2]=tcolor[2];
            break;
        }
        case Mode::polygon:
        {
            double tcolor[3];
            tcolor[0]=curcolor[0];
            tcolor[1]=curcolor[1];
            tcolor[2]=curcolor[2];
            curcolor[0]=iter->color[0];
            curcolor[1]=iter->color[1];
            curcolor[2]=iter->color[2];
            drawPolygon(*iter);
            curcolor[0]=tcolor[0];
            curcolor[1]=tcolor[1];
            curcolor[2]=tcolor[2];
            break;
        }
        default:break;
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
 //   ischoosen=false;
}

void GraphLibrary::OPT_scale(int x,int y,double s)
{
    qDebug()<<"scale";
    if(ischoosen==true)
    {
        QVector<Dictionary>::iterator iter;
        for(iter=dictionary.begin();iter!=dictionary.end();iter++)
        {
            if(iter->pid==choosenpid)
            {
                qDebug()<<iter->mode;
                break;
            }
        }

        OPT_delete();
        qDebug()<<"delete complete";
        qDebug()<<"delete complete";
        qDebug()<<"delete complete";
        qDebug()<<"delete complete";
        qDebug()<<iter->para.size();
        for(int i=0;i<iter->para.size();i++)
        {
            qDebug()<<"old"<<iter->para[i];
            iter->para[i]=((double)iter->para[i])*s+((double)x)*(1-s);
        }
        qDebug()<<"here";
        switch(iter->mode)
        {
        case Mode::circle:
        {
            double tcolor[3];
            tcolor[0]=curcolor[0];
            tcolor[1]=curcolor[1];
            tcolor[2]=curcolor[2];
            curcolor[0]=iter->color[0];
            curcolor[1]=iter->color[1];
            curcolor[2]=iter->color[2];
            drawCircle(*iter);
            curcolor[0]=tcolor[0];
            curcolor[1]=tcolor[1];
            curcolor[2]=tcolor[2];
            break;
        }
        case Mode::line:
        {
            double tcolor[3];
            tcolor[0]=curcolor[0];
            tcolor[1]=curcolor[1];
            tcolor[2]=curcolor[2];
            curcolor[0]=iter->color[0];
            curcolor[1]=iter->color[1];
            curcolor[2]=iter->color[2];
            drawLine(*iter);
            curcolor[0]=tcolor[0];
            curcolor[1]=tcolor[1];
            curcolor[2]=tcolor[2];
            break;
        }
        case Mode::ellipse:
        {
            double tcolor[3];
            tcolor[0]=curcolor[0];
            tcolor[1]=curcolor[1];
            tcolor[2]=curcolor[2];
            curcolor[0]=iter->color[0];
            curcolor[1]=iter->color[1];
            curcolor[2]=iter->color[2];
            drawEllipse(*iter);
            curcolor[0]=tcolor[0];
            curcolor[1]=tcolor[1];
            curcolor[2]=tcolor[2];
            break;
        }
        case Mode::rectangle:
        {
            double tcolor[3];
            tcolor[0]=curcolor[0];
            tcolor[1]=curcolor[1];
            tcolor[2]=curcolor[2];
            curcolor[0]=iter->color[0];
            curcolor[1]=iter->color[1];
            curcolor[2]=iter->color[2];
            drawRectangle(*iter);
            curcolor[0]=tcolor[0];
            curcolor[1]=tcolor[1];
            curcolor[2]=tcolor[2];
            break;
        }
        case Mode::polygon:
        {
            double tcolor[3];
            tcolor[0]=curcolor[0];
            tcolor[1]=curcolor[1];
            tcolor[2]=curcolor[2];
            curcolor[0]=iter->color[0];
            curcolor[1]=iter->color[1];
            curcolor[2]=iter->color[2];
            drawPolygon(*iter);
            curcolor[0]=tcolor[0];
            curcolor[1]=tcolor[1];
            curcolor[2]=tcolor[2];
            break;
        }
        default:break;
        }
      /*  for(QVector<Point>::iterator iter=curboard.begin();iter != curboard.end();iter++)
        {
            if(iter->pid==choosenpid)
            {
                //qDebug()<<"ox="<<iter->x<<"oy="<<iter->y;
                iter->x=((double)iter->x)*s+((double)x)*(1-s);
                iter->y=((double)iter->y)*s+((double)y)*(1-s);
                //qDebug()<<"x="<<iter->x<<"y="<<iter->y;
            }
        }*/
    }
     //   ischoosen=false;
}

void GraphLibrary::OPT_clip(int x1,int y1,int x2,int y2)
{
    qDebug()<<"clip";
    QVector<Dictionary>::iterator iter;
    for(iter=dictionary.begin();iter!=dictionary.end();iter++)
    {
        if(iter->pid==choosenpid)
        {
            qDebug()<<"who is choosed"<<iter->pid;
            break;
        }
    }
    if(x1>x2)
    {
        int temp=x2;
        x2=x1;
        x1=temp;
    }
    if(y1>y2)
    {
        int temp=y2;
        y2=y1;
        y1=temp;
    }
    if(ischoosen==true&&iter->mode==line)
    {
        qDebug()<<"success";
        int xs=iter->para[0];
        int ys=iter->para[1];
        int xe=iter->para[2];
        int ye=iter->para[3];
        if(Caflag==CohenSutherland)
        {
            qDebug()<<"cohenSutherland";
            bool accept=false;
            int x,y;
            //qDebug()<<"xs"<<xs<<" "<<"ys"<<ys<<" "<<"xe"<<xe<<" "<<"ye"<<ye<<" "<<"x1"<<x1<<" "<<"y1"<<y1<<" "<<"x2"<<x2<<" "<<"y2"<<y2<<endl;
            int s=CohenSutherlandTools(xs,ys,x1,y1,x2,y2);
         //   qDebug()<<"s="<<s;
            int e=CohenSutherlandTools(xe,ye,x1,y1,x2,y2);
          //  qDebug()<<"e="<<e;
            while(true)
            {
               // qDebug()<<"xs"<<xs<<" "<<"ys"<<ys<<" "<<"xe"<<xe<<" "<<"ye"<<ye<<" "<<"x1"<<x1<<" "<<"y1"<<y1<<" "<<"x2"<<x2<<" "<<"y2"<<y2<<endl;
              //  qDebug()<<"s="<<s<<"e="<<e;
               // qDebug()<<"in";
                if((s==e)&&(s==0))
                {
                   accept=true;
                   break;
                }
                else if((s&e)!=0)
                {
                  break;
                }
                else
                {
                  int out;
                  bool flag=false;
                  if(s==0)
                  {
                      flag=false;
                      out=e;
                  }
                  else
                  {
                      flag=true;
                      out=s;
                  }
                  if((out&1)!=0)
                  {
                   //   qDebug()<<"左";
                      x=x1;
                      y=getintersection(xs,ys,xe,ye,x1,0);
                    //  qDebug()<<"x="<<x<<"y="<<y;
                  }
                  else if((out&2)!=0)
                  {  // qDebug()<<"右";
                      x=x2;
                      y=getintersection(xs,ys,xe,ye,x2,0);
                     //  qDebug()<<"x="<<x<<"y="<<y;
                  }
                  else if((out&4)!=0)
                  {
                    //  qDebug()<<"下";
                      x=getintersection(xs,ys,xe,ye,y2,1);
                      y=y2;
                    //   qDebug()<<"x="<<x<<"y="<<y;
                  }
                  else if((out&8)!=0)
                  {
                     // qDebug()<<"上";
                      x=getintersection(xs,ys,xe,ye,y1,1);
                      y=y1;
                    //   qDebug()<<"x="<<x<<"y="<<y;
                  }
                  else
                  {
                      qDebug()<<"wtf";
                  }

                  if(flag==true)
                  {
                      xs=x;
                      ys=y;
                      s=CohenSutherlandTools(xs,ys,x1,y1,x2,y2);
                    //  qDebug()<<"update s as"<<s<<endl;
                  }
                  else
                  {
                      xe=x;
                      ye=y;
                      e=CohenSutherlandTools(xe,ye,x1,y1,x2,y2);
                      //  qDebug()<<"update e as"<<e<<endl;
                  }
                }

            }
            if(accept==true)
            {
                OPT_delete();
               // qDebug()<<"delete complete";
                setLAlgro(DDA);
                iter->para[0]=xs;
                iter->para[1]=ys;
                iter->para[2]=xe;
                iter->para[3]=ye;
                double tcolor[3];
                tcolor[0]=curcolor[0];
                tcolor[1]=curcolor[1];
                tcolor[2]=curcolor[2];
                curcolor[0]=iter->color[0];
                curcolor[1]=iter->color[1];
                curcolor[2]=iter->color[2];
                drawLine(*iter);
                curcolor[0]=tcolor[0];
                curcolor[1]=tcolor[1];
                curcolor[2]=tcolor[2];
            }
            else
            {
                 OPT_delete();
            }

        }
        else if(Caflag==LiangBarsky)
        {

               bool flag = false;
               double u1 = 0, u2 =1;
               double p[4], q[4];
               double r;
               p[0] = xs-xe;
               p[1] = xe-xs;
               p[2] = ys-ye;
               p[3] = ye-ys;

               q[0] = xs-x1;
               q[1] = x2-xs;
               q[2] = ys-y1;
               q[3] = y2-ys;

               for(int i = 0; i < 4; i++)
               {
                   r = q[i] / p[i];
                   if(p[i] < 0)
                   {
                       u1 =(u1>r)?u1:r;
                       if(u1 > u2)
                       {
                           flag = true;
                       }
                   }
                   if(p[i] > 0)
                   {
                       u2 = (u2> r)?r:u2;
                       if(u1 > u2)
                       {
                           flag = true;
                       }
                   }
                   if(p[i] == 0 && p[i] < 0)
                   {
                       flag = true;
                   }
               }

               if ( flag )
               {
                   return;
               }
               //int nx1,nx2,ny1,ny2;
               iter->para[0] = xs - u1 *(xs - xe);
               iter->para[1] = ys - u1 *(ys - ye);
               iter->para[2] = xs - u2 *(xs - xe);
               iter->para[3] = ys - u2 *(ys - ye);
               OPT_delete();
               setLAlgro(DDA);
               double tcolor[3];
               tcolor[0]=curcolor[0];
               tcolor[1]=curcolor[1];
               tcolor[2]=curcolor[2];
               curcolor[0]=iter->color[0];
               curcolor[1]=iter->color[1];
               curcolor[2]=iter->color[2];
               drawLine(*iter);
               curcolor[0]=tcolor[0];
               curcolor[1]=tcolor[1];
               curcolor[2]=tcolor[2];
        }
    }
    else
    {
        qDebug()<<iter->mode;
        qDebug()<<ischoosen;
        qDebug()<<"fail";
    }
    // ischoosen=false;
}

void GraphLibrary::myC()
{

    int i,j;
       for(i=0; i<=MAXXX; ++i)
       {
           C[0][i] = 0;
           C[i][0] = 1;
       }
       for(i=1; i<=MAXXX; ++i)
       {
           for(j=1; j<=MAXXX; ++j)
           C[i][j] = (C[i-1][j] + C[i-1][j-1]);
       }

}


int GraphLibrary::CohenSutherlandTools(int x, int y, int x1, int y1, int x2, int y2)
{
    int s;
    int s1=(y<y1)?1:0;
    s1=s1*8;
    int s2=(y>y2)?1:0;
    s2=s2*4;
    int s3=(x>x2)?1:0;
    s3=s3*2;
    int s4=(x<x1)?1:0;
    s=s1+s2+s3+s4;
  //  qDebug()<<"s="<<s;
    return s;
}

int GraphLibrary::getintersection(int x1, int y1, int x2, int y2, int a, bool horizon)
{
   // qDebug()<<"x1"<<x1<<endl<<"y1"<<y1<<endl<<"x2"<<x2<<endl<<"y2"<<y2<<endl;
    double k=(double)(y1-y2)/(double)(x1-x2);
    double b=y1-k*x1;
  //  qDebug()<<"k"<<k<<endl<<"b"<<b<<endl;
    if(horizon)
    {
        if(x1==x2)
        {
            return x1;
        }
        else
        {
            return (a-b)/k;
        }
    }
    else
    {
        if(y1==y2)
        {
            return y1;
        }
        else
        {
         //   qDebug()<<"this?";
            return k*a+b;
        }
    }
}


void GraphLibrary::paintGL()
{
    //qDebug()<<"printGL"<<endl;
    glClear(GL_COLOR_BUFFER_BIT);
    if(tempP==false)
    {
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
                   // qDebug()<<"chosen";
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
    else
    {
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
                   // qDebug()<<"chosen";
                    glColor3d(0.5,0.5,0.5);
                }
                glPointSize(iter->size);
                glBegin(GL_POINTS);
                glVertex3f(iter->x,this->size().height()-iter->y,0);
              //  glVertex3f(iter->x,iter->y,0);
                glEnd();
        }

        for(QVector<Point>::iterator iter=tempboard.begin();iter != tempboard.end();iter++)
        {
           // qDebug()<<"x="<<iter->x<<" "<<"y="<<iter->y;

                   // qDebug()<<"unchoose";
                glColor3d(iter->color[0],iter->color[1],iter->color[2]);
                glPointSize(iter->size);
                glBegin(GL_POINTS);
                glVertex3f(iter->x,this->size().height()-iter->y,0);
              //  glVertex3f(iter->x,iter->y,0);
                glEnd();
        }
        update();
    }
}

void GraphLibrary::initializeGL()
{
    qDebug()<<"initializeGL"<<endl;
    initializeOpenGLFunctions();
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}

void GraphLibrary::resizeGL(int w, int h)
{
   // qDebug()<<"resize";
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
        case Mode::polygon:
        {
            break;
        }
        case Mode::choose:
        {
            choose(event->pos().x(),event->pos().y());
            break;
        }
        case Mode::clip:
        {
            start_x=event->pos().x();
            start_y=event->pos().y();
            break;
        }
        case Mode::move:
        {
            start_x=event->pos().x();
            start_y=event->pos().y();
            break;
        }
        case Mode::scale:
        {
            start_x=event->pos().x();
            start_y=event->pos().y();
            break;
        }
        case Mode::rotate:
        {
            start_x=event->pos().x();
            start_y=event->pos().y();
            break;
        }
        default:break;
        }
        qDebug()<<"left_start"<<event->pos().rx();
        qDebug()<<"left_start"<<event->pos().ry();

    }
    else if(event->button()==Qt::RightButton)
    {

        if(curmode==Mode::curve)
        {
            Dictionary x;
            x.pid=curpid;
            x.mode=curmode;
            for(int i=0;i<curvenp.size();i++)
            {
                x.para.push_back(curvenp[i].x);
                x.para.push_back(curvenp[i].y);
            }
            x.color[0]=curcolor[0];
            x.color[1]=curcolor[1];
            x.color[2]=curcolor[2];
            //setCuAlgro(CuAlgro::Bspline);
            drawCurve(x);
            dictionary.push_back(x);
            curvenp.clear();
            tempboard.clear();
            tempP=false;
            curvenf=false;
            curpid++;
        }
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
           Dictionary x;
           x.pid=curpid;
           x.mode=curmode;
           x.para.push_back(start_x);
           x.para.push_back(start_y);
           x.para.push_back(end_x);
           x.para.push_back(end_y);
           x.color[0]=curcolor[0];
           x.color[1]=curcolor[1];
           x.color[2]=curcolor[2];
           dictionary.push_back(x);
           drawLine(x);
           curpid++;
           break;
        }
        case circle:
        {
            end_x=event->pos().x();
            end_y=event->pos().y();
           // drawCircle(start_x,start_y,end_x,end_y);
            Dictionary x;
            x.pid=curpid;
            x.mode=curmode;
            x.para.push_back(start_x);
            x.para.push_back(start_y);
            x.para.push_back(end_x);
            x.para.push_back(end_y);
            x.color[0]=curcolor[0];
            x.color[1]=curcolor[1];
            x.color[2]=curcolor[2];
            dictionary.push_back(x);
            drawCircle(x);
            curpid++;
            break;
        }
        case ellipse:
        {
            end_x=event->pos().x();
            end_y=event->pos().y();
            //drawEllipse(start_x,start_y,end_x,end_y);
            Dictionary x;
            x.pid=curpid;
            x.mode=curmode;
            x.para.push_back(start_x);
            x.para.push_back(start_y);
            x.para.push_back(abs(end_x-start_x));
            x.para.push_back(abs(end_y-start_y));
            x.color[0]=curcolor[0];
            x.color[1]=curcolor[1];
            x.color[2]=curcolor[2];
            dictionary.push_back(x);
            drawEllipse(x);
            curpid++;
            break;
        }
        case polygon:
        {
            qDebug()<<"drawpolygon";
            dataPoint t;
            t.x=event->pos().x();
            t.y=event->pos().y();
            if(polygonf==false)
            {
                polygonf=true;
                start_x=t.x;
                start_y=t.y;
                drawTemp(t.x,t.y);
                polygonp.push_back(t);
                tempP=true;
            }
            else
            {
                if(abs(t.x-start_x)+abs(t.y-start_y)<=10)
                {
                    Dictionary x;
                    x.pid=curpid;
                    x.mode=curmode;
                    for(int i=0;i<polygonp.size();i++)
                    {
                        x.para.push_back(polygonp[i].x);
                        x.para.push_back(polygonp[i].y);
                    }
                    x.color[0]=curcolor[0];
                    x.color[1]=curcolor[1];
                    x.color[2]=curcolor[2];
                    drawPolygon(x);
                    dictionary.push_back(x);
                    polygonp.clear();
                    tempboard.clear();
                    tempP=false;
                    polygonf=false;
                    curpid++;
                }
                else
                {
                    drawTemp(t.x,t.y);
                    polygonp.push_back(t);
                    Dictionary z;
                    z.para.push_back(polygonp[polygonp.size()-2].x);
                    z.para.push_back(polygonp[polygonp.size()-2].y);
                    z.para.push_back(polygonp[polygonp.size()-1].x);
                    z.para.push_back(polygonp[polygonp.size()-1].y);
                    drawTline(z);

                }
            }
             break;

        }
        case rectangle:
        {
            end_x=event->pos().x();
            end_y=event->pos().y();
           // drawRectangle(start_x,start_y,end_x,end_y);
            Dictionary x;
            x.pid=curpid;
            x.mode=curmode;
            x.para.push_back(start_x);
            x.para.push_back(start_y);
            x.para.push_back(end_x);
            x.para.push_back(end_y);
            x.color[0]=curcolor[0];
            x.color[1]=curcolor[1];
            x.color[2]=curcolor[2];
            dictionary.push_back(x);
            qDebug()<<"release rectangle";
            drawRectangle(x);
            curpid++;
            break;
        }
        case Mode::curve:
        {
            qDebug()<<"drawCurve";
            dataPoint t;
            t.x=event->pos().x();
            t.y=event->pos().y();
            if(curvenf==false)
            {
                curvenf=true;
                start_x=t.x;
                start_y=t.y;
                drawTemp(t.x,t.y);
                curvenp.push_back(t);
                tempP=true;
            }
            else
            {
                drawTemp(t.x,t.y);
                curvenp.push_back(t);
                Dictionary z;
                z.para.push_back(curvenp[curvenp.size()-2].x);
                z.para.push_back(curvenp[curvenp.size()-2].y);
                z.para.push_back(curvenp[curvenp.size()-1].x);
                z.para.push_back(curvenp[curvenp.size()-1].y);
                drawTline(z);
            }
             break;
        }
        case Mode::move:
        {
            end_x=event->pos().x();
            end_y=event->pos().y();
            OPT_move(end_x-start_x,end_y-start_y);
            break;
        }
        case Mode::clip:
        {
            end_x=event->pos().x();
            end_y=event->pos().y();
            setCAlgro(LiangBarsky);
            OPT_clip(start_x,start_y,end_x,end_y);
            unchoose();
            break;
        }
        case Mode::scale:
        {
            end_x=event->pos().x();
            end_y=event->pos().y();
            OPT_scale(start_x,start_y,scale);
            unchoose();
            break;
        }
        case Mode::rotate:
        {
            end_x=event->pos().x();
            end_y=event->pos().y();
            OPT_rotate(start_x,start_y,angle);
            unchoose();
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
