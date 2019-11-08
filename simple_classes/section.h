#include <iostream>
#include <vector>

#define PI 3.14159265358979323846

struct point{
    /* 
        Point stores the horizontal (x) and vertical (y) coordinates
    in a 2D space. Points are inteded to be used to describe a cross
    section (for instance, for defining its center or boundary 
    vertexes.
    */
    int index;
    double x, y;
};

struct line{
    /*
        Lines stores the indexes of nodes defining a line segment.
    Lines are intended to be used to describe a cross section 
    boundary.
    */
    int index;
    int firstPoint, lastPoint;
};

class Section{
    /*
        Sections are used to describe the solid's cross section,
    storing its center and point/lines defining it's boundaries.

    */
    public:
        Section();
        void setCenter(double x, double y);
        struct point getCenter();
        void addBoundaryPoint(int index, double x, double y);
        void addBoundaryLine(int index, int firstPoint, int lastPoint);
        std::vector<struct point> getBoundaryPoints();
        std::vector<struct line> getBoundaryLines();
        void printSectionProperties();
    private:
        struct point _center_;
        std::vector<struct point> _bpoints_; // b stands for boundary
        std::vector<struct line> _blines_;
        // _bpoints_ -> boundary points; _blines -> boundary lines
};