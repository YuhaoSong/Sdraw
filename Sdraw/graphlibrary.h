#ifndef GRAPHLIBRARY_H
#define GRAPHLIBRARY_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector>
#include <Qdebug>
#include <QMouseEvent>
//#include <GL/glu.h>
enum Mode{choose,freeedit, line, circle, rectangle, ellipse};
enum Algro{DDA,Bresenham};
struct Point//every pixel
{
    int x;
    int y;
    double color[3];
    bool choosen;
    int pid;
    Mode mode;

};
class GraphLibrary : public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GraphLibrary(QWidget *parent = nullptr);
    ~GraphLibrary();
    void setMode(Mode mode);
    void setSize(int size);
    void setColor(int r, int b,int g);
    void setAlgro(Algro x);

    void drawPoint(int x,int y);
    void drawLine(int x1,int y1,int x2,int y2);
    void drawCircle(int x1,int y1,int x2,int y2);
    void drawEllipse(int x1,int y1,int x2,int y2);
    void drawRectangle(int x1,int y1,int x2,int y2);

    void choose(int x,int y);
    void unchoose();
    void OPT_delete();
    void OPT_rotate();
    void OPT_move();
    void OPT_scale();
    void OPT_clip();

protected:
    void paintGL() override;//refresh
    void initializeGL() override;//init
    void resizeGL(int w, int h) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    //QOpenGLContext *m_context;
private:
    QVector<Point> curboard;//all the points which means the mirror of the board
    QVector<Point> oldboard;//TODO: used in redo and undo
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

};

#endif // GRAPHLIBRARY_H
