#ifndef TOOLS_H
#define TOOLS_H
#include <QVector>
enum Mode{choose,polygon, line, circle, rectangle, ellipse,move,clip,rotate,scale};
enum Algro{DDA,Bresenham,CohenSutherland,LiangBarsky};
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
    QVector<double> para;
};

#endif // TOOLS_H
