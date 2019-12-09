#ifndef GRAPHLIBRARY_H
#define GRAPHLIBRARY_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector>
#include <Qdebug>
#include <QMouseEvent>
#include "tools.h"
//#include <GL/glu.h>

class GraphLibrary : public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GraphLibrary(QWidget *parent = nullptr);
    ~GraphLibrary();
    void setMode(Mode mode);
    void setSize(int size);
    void setColor(double r, double g,double b);
    void setAlgro(Algro x);
    void setAngle(int x);
    void setScale(double x);
    void drawPoint(int x,int y,int pid);
    void drawTemp(int x,int y);
    void drawLine(Dictionary temp);
    void drawCircle(Dictionary temp);
    void drawEllipse(Dictionary temp);
    void drawRectangle(Dictionary temp);
    void drawPolygon(Dictionary temp);
    void drawCurve(Dictionary temp);
    void choose(int x,int y);
    void clear();
    void unchoose();
    void OPT_delete();
    void OPT_rotate(int x,int y,double r);
    void OPT_move(int x,int y);
    void OPT_scale(int x,int y,double s);
    void OPT_clip(int x1,int y1,int x2,int y2);
    void  myC()
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
    int C[MAXXX+1][MAXXX+1];
protected:
    void paintGL() override;//refresh
    void initializeGL() override;//init
    void resizeGL(int w, int h) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    //QOpenGLContext *m_context;
public:
    int CohenSutherlandTools(int x, int y, int x1, int y1, int x2, int y2);
    int getintersection(int x1,int y1,int x2,int y2,int a,bool horizon );
    QVector<Point> curboard;//all the points which means the mirror of the board
    QVector<Point> tempboard;//TODO: used in redo and undo

    QVector<Dictionary> dictionary;
    QVector<dataPoint> polygonp;
    QVector<dataPoint> curvenp;
    double curcolor[3];// change color or something
    Mode curmode;// make a shape
    int curpid;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int cursize;
    bool ischoosen;
    int choosenpid;
    Algro aflag;
    bool dflag;
    bool polygonf;
    bool curvenf;
    int angle;
    double scale;
    bool tempP;

};

#endif // GRAPHLIBRARY_H
