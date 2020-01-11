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
    getPointRadius(index);
    getPointSlope(index);
}

std::vector<struct point> Section::getBoundaryPoints(){
    return _bpoints_;
}

std::vector<struct line> Section::getBoundaryLines(){
    return _blines_;
}



/*
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
*/

 double Section::getNumberofPoints(){

     _numnodes_ = _bpoints_.size();
     return _numnodes_;

 }

 double Section::getNumberofElements(){

     _numelem_ = _blines_.size();
     return _numelem_;
     
 }


std::string Section::ParaviewBoundaryLine(int index){

        double firstpoint = _blines_[index].firstPoint;
        double lastpoint = _blines_[index].lastPoint;
        
        std::stringstream line;
        
        line << firstpoint << " " << lastpoint << std::endl;

        return line.str();

}

 std::string Section::ParaviewPointCoordinates(int index){

        double x = _bpoints_[index].x;
        double y = _bpoints_[index].y;
        std::stringstream coordinates;
        coordinates.precision(6);
        coordinates << std::fixed;
        coordinates << x << " " << y << " " << 0 << std::endl;
        return coordinates.str();
 }
 

void Section::getPointCoordinates(int index, double currentX, double currentY,double currentRotation){
    //movement due to center axis rotation
    double radius = _bpoints_[index].radius;
    double slope = _bpoints_[index].slope + currentRotation;
    double x = _center_.x + radius*cos(slope);
    double y = _center_.x + radius*sin(slope);

    //movement due to center axis traslation
    double deltax = currentX - _center_.x;
    double deltay = currentY - _center_.y;

    //new coordinates
    _bpoints_[index].x = x + deltax;
    _bpoints_[index].y = y + deltay;
    _bpoints_[index].slope = slope;

}

void Section::getAllPointsCoordinates(double currentX, double currentY, double currentRotation){

    if (_bpoints_.size() > 0){
        
        for (std::vector<struct point>::iterator it = _bpoints_.begin();
          it !=_bpoints_.end(); it++){
            
            getPointCoordinates(it->index,currentX,currentY,currentRotation);
        }
    }else{
        std::cout << " -> No boundary points defined!"
                  << std::endl;
    }

}



void Section::getPointRadius(int index){

    int x = _bpoints_[index].x; 
    int y = _bpoints_[index].y;
    double deltax = x - _center_.x;
    double deltay = y - _center_.y;
    double radius = sqrt(deltax*deltax+deltay*deltay);
    _bpoints_[index].radius = radius;
}

void Section::getPointSlope(int index){
    int x = _bpoints_[index].x; 
    int y = _bpoints_[index].y;
    double radius = _bpoints_[index].radius;
    double deltax = x - _center_.x;
    double deltay = y - _center_.y;

    if (deltax > 0.){
                if (deltay> 0.){
                    _bpoints_[index].slope = asin(deltay/radius);
                    
                }else{
                    _bpoints_[index].slope =  2.0*PI + asin(deltay/radius);
                    
                }
            }else{  
                if (deltay>0){
                    _bpoints_[index].slope = PI - asin(deltay/radius);
                    
                }else{
                    _bpoints_[index].slope = PI - asin(deltay/radius);
                    
                }
            }
  
}

void Section::printPointProperties(int index){

    std::cout << "Index: "<<_bpoints_[index].index << std::endl;
    std::cout << "X: " <<_bpoints_[index].x << std::endl;
    std::cout << "Y: "<< _bpoints_[index].y << std::endl;
    std::cout << "Radius: "<< _bpoints_[index].radius <<std::endl;
    std::cout << "Slope: "<< (180/PI)*_bpoints_[index].slope <<std::endl;

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
            std::cout << it->x << ", y = " << it->y << " with radius ";
            std::cout << it->radius << " and slope of " << it->slope;
            std::cout << " [rad]" << std::endl;
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
