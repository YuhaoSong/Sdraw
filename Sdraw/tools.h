#ifndef TOOLS_H
#define TOOLS_H
#include <QVector>
enum Mode{temp,choose,polygon, line, circle, rectangle, ellipse,move,clip,rotate,scale,curve};
enum Algro{DDA,Bresenham,CohenSutherland,LiangBarsky,Bezier,Bspline};
struct Point//every pixel
{
    int x;
    int y;
    double color[3];
    bool choosen;
    int pid;
    int size;
    Mode mode;

};
struct dataPoint
{
    int x;
    int y;
};

struct Dictionary
{
    int pid;
    Mode mode;
    double color[3];
    QVector<double> para;
};

#endif // TOOLS_H
