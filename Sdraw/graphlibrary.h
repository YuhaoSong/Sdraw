#ifndef GRAPHLIBRARY_H
#define GRAPHLIBRARY_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector>
#include <Qdebug>
enum State{freeedit, line, circle, rectangle, ellipse};
struct Point//every pixel
{
    int x;
    int y;
    int color[3];
    bool choosen;
    int pid;

};
class GraphLibrary : public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GraphLibrary(QWidget *parent = nullptr);
    ~GraphLibrary();
    void setMode(int mode);
protected:
    void paintGL() override;//refresh
    void initializeGL() override;//init
    void resizeGL(int w, int h) override;
    //QOpenGLContext *m_context;
private:
    QVector<Point> curboard;//all the points which means the mirror of the board
    QVector<Point> oldboard;//TODO: used in redo and undo
    int curcolor[3];// change color or something
    State curstate;// make a shape
    int mode;

};

#endif // GRAPHLIBRARY_H
