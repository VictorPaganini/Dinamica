#include "section.h"

Section::Section(){}

void Section::setCenter(double x, double y){
    struct point center;
    center.index = -1; // Center does not needs a index; setting as -1
    center.x = x;
    center.y = y;
    //center.r = r;
    _center_ = center;
}

struct point Section::getCenter(){
    return _center_;
}

void Section::addBoundaryPoint(int index, double x, double y){
    struct point bpoint;
    bpoint.index = index;
    bpoint.x = x;
    bpoint.y = y;
    _bpoints_.push_back(bpoint);
}

void Section::addBoundaryLine(int index, int firstPoint, int lastPoint){
    struct line bline;
    bline.index = index;
    bline.firstPoint = firstPoint;
    bline.lastPoint = lastPoint;
    _blines_.push_back(bline);
}

std::vector<struct point> Section::getBoundaryPoints(){
    return _bpoints_;
}

std::vector<struct line> Section::getBoundaryLines(){
    return _blines_;
}

void Section::readGeometryData(){

    std::string geometry_file = "geometry_test.txt";
    std::string line;

    std::ifstream geometryData(geometry_file.c_str());
  
    getline(geometryData,line),getline(geometryData,line);

    //General aspects
    geometryData >> _numelem_ >> _numnodes_ ;

    getline(geometryData,line),getline(geometryData,line);

    //Nodal coordinates
    for (int i=0; i<_numnodes_;i++){

        double index, x, y;

        geometryData >> index >> x >> y;
        addBoundaryPoint(index,x,y);
        getline(geometryData,line);

    }

    //Conectivity
    for (int i=0; i<_numelem_;i++){

        double index, firstpoint, lastpoint;

        geometryData >> index >> firstpoint >> lastpoint;
        addBoundaryLine(index,firstpoint,lastpoint);
        getline(geometryData,line);

    }
    //Center coordinates
    geometryData >> _center_.x >> _center_.y;

    
}





void Section::printSectionProperties(){
    std::cout << "Section properties" << std::endl;
    std::cout << " - center at x = " << _center_.x;
    std::cout << ", y = " << _center_.y << std::endl;
    if (_bpoints_.size() > 0){
        std::cout << "Number of points in the boundary: " 
                << _bpoints_.size() << std::endl;
        for (std::vector<struct point>::iterator it = _bpoints_.begin();
             it !=_bpoints_.end(); it++){
            std::cout << " - Point #" << it->index << " at x = ";
            std::cout << it->x << ", y = " << it->y << std::endl;
        }
    }else{
        std::cout << " -> No boundary points defined!"
                  << std::endl;
    }
    if (_blines_.size() > 0){
        std::cout << "Number of lines in the boundary: " 
                << _blines_.size() << std::endl;
        for (std::vector<struct line>::iterator it = _blines_.begin();
             it !=_blines_.end(); it++){
            std::cout << " - Line #" << it->index << " from point #";
            std::cout << it->firstPoint << " to point #";
            std::cout << it->lastPoint << std::endl;
        }
    }else{
        std::cout << " -> No boundary lines defined!"
                  << std::endl;
    }

}
