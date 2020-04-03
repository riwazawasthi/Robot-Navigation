#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include"systemc.h"
#include <map>

struct graphPoint {
    double x;
	  double y;
};

std::map<int , point> x1y1;
std::map<int , point> x2y2;
std::map<int , int> NorthGrid ;
std::map<int , int> SouthGrid;
std::map<int , int> EastGrid ;
std::map<int , int> WestGrid ;
std::map<int , std::vector<int> > robotPath;
std::map<int , int> robotStatus ;
std::map<int , int> robotGridLocation ;
std::map<int , int> robotDir;
std::map<int , point> robotPointLocation;
std::map<int , int> obstacleCurrentGrid;
std::map<int , point> obstaclePointLocation;
std::map<int, int> obstacleSpan;



#endif
