#include <iostream>
#include "section.h"

void initial_tests(){
    
    std::cout << "Testing Section class" << std::endl;
    Section sec;
    sec.setCenter(0.0,0.0);
    sec.printSectionProperties();
    std::cout << std::endl <<std::endl;
    std::cout <<"Adding four nodes" << std::endl;
    std::cout << std::endl <<std::endl;
    sec.addBoundaryPoint(0,2.0,-0.5);
    sec.addBoundaryPoint(1,2.5,0.5);
    sec.addBoundaryPoint(2,-2.5,0.5);
    sec.addBoundaryPoint(3,-2.0,-0.5);
    sec.printSectionProperties();
    std::cout << std::endl <<std::endl;
    std::cout << "Adding four lines" << std::endl;
    std::cout << std::endl <<std::endl;
    sec.addBoundaryLine(0,0,1);
    sec.addBoundaryLine(1,1,2);
    sec.addBoundaryLine(2,2,3);
    sec.addBoundaryLine(3,3,0);
    sec.printSectionProperties();
}


int main(){
    initial_tests();
    return 0;
}
