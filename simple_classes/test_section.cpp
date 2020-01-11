#include <iostream>
#include "section.h"

void initial_tests(){
    
    std::cout << "Testing Section class" << std::endl;
    Section sec;
    sec.setCenter(0.0,0.0);
    //sec.printSectionProperties();
    //std::cout << std::endl <<std::endl;
    //std::cout <<"Adding four nodes" << std::endl;
    //std::cout << std::endl <<std::endl;
    sec.addBoundaryPoint(0,1.0,1.0);
    sec.addBoundaryPoint(1,-1.0,1.0);
    sec.addBoundaryPoint(2,-1.0,-1.0);
    sec.addBoundaryPoint(3,1.0,-1.0);
    //sec.printSectionProperties();
    //std::cout << std::endl <<std::endl;
    //std::cout << "Adding four lines" << std::endl;
    //std::cout << std::endl <<std::endl;
    sec.addBoundaryLine(0,0,1);
    sec.addBoundaryLine(1,1,2);
    sec.addBoundaryLine(2,2,3);
    sec.addBoundaryLine(3,3,0);
    sec.printSectionProperties();
    /*
    
    std::cout << std::endl <<std::endl;
    std::cout << "Testing movement auxiliar functions" << std::endl;
    sec.printPointProperties(0);
    sec.getPointCoordinates(0,0,0,PI/2);
    sec.printPointProperties(0);
    sec.getPointCoordinates(0,3,3,0);
    sec.printPointProperties(0);
    

    sec.getAllPointsCoordinates(3,3,PI/2);
    sec.setCenter(3,3);
    sec.printSectionProperties();
    

    std::cout << sec.getNumberofPoints();
    std::cout << sec.getNumberofElements();
    */

    std::cout << std::endl <<std::endl;
    std::cout << "Testing paraview auxiliar functions" << std::endl;
    std::cout << std::endl <<std::endl;
    std::cout << "Considering 1 line and 1 point" << std::endl;
    std::cout << "Point 0: " << sec.ParaviewPointCoordinates(0) << std::endl;
    std::cout << "Line 0: " << sec.ParaviewBoundaryLine(0) << std::endl;
    std::cout << "_Points Loop_" << std::endl;

    double numnodes = sec.getNumberofPoints();

    for (int i=0; i<numnodes; i++){
            std::cout << sec.ParaviewPointCoordinates(i);

    }
    std::cout << "Lines Loop_" << std::endl;

    double numelem = sec.getNumberofElements();

    for (int i=0; i<numelem; i++){
            std::cout << sec.ParaviewBoundaryLine(i);

    }
    
} 


int main(){
    initial_tests();
    return 0;
}
