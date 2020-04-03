#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include"systemc.h"
#include <map>

struct point {
    double x;
	  double y;
};

int *indexPath_func(int arr[]);
std::map<int , point> x1y1_func();
std::map<int , point> x2y2_func();
std::map<int , int> NorthGrid_func() ;
std::map<int , int>  SouthGrid_func();
std::map<int , int> EastGrid_func();
std::map<int , int> WestGrid_func();
std::map<int , std::vector<int> > robotPath_func();
std::map<int , int> robotStatus_func() ;
std::map<int , int> robtoCurrentGrid_func();
std::map<int , int> robotNextGrid_func();
std::map<int , int> robotDir_func();
std::map<int , point> robotPointLocation_func();
std::map<int , point> obstaclePointLocation_func();
std::map<int, int> obstacleSpan_func();


extern std::map<int , point> x1y1;
extern std::map<int , point> x2y2;
extern std::map<int , int> NorthGrid;
extern std::map<int , int> SouthGrid;
extern std::map<int , int> EastGrid;
extern std::map<int , int> WestGrid;
extern std::map<int , std::vector<int> > robotPath;
extern std::map<int , int> robotStatus ;
extern std::map<int , int> robotCurrentGrid;
extern std::map<int , int> robotNextGrid;
extern std::map<int , int> robotDir;
extern std::map<int , point> robotPointLocation;
extern std::map<int , point> obstaclePointLocation ;
extern std::map<int, int> obstacleSpan;
extern int iDx[3];
extern int *indexPath;


#endif
