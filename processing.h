#ifndef PROCESSING_H
#define PROCESSING_H

#include"systemc.h"
#include "data_structures.h"

class processingModule:public SC_MODULE{
  public:
    sc_in<bool> clock, triggerFromRobot1, triggerFromRobot2;
    sc_in<int> dataFromRobot1,dataFromRobot2;

    sc_out<bool> triggerToRobot1,triggerToRobot2;
    sc_out<int> dataToRobot1,dataToRobot2;

    void populate_x1y1(std::map<int , point> m);
    void populate_x2y2(std::map<int , point> m);
    void populate_NorthGrid(std::map<int , int> m);
    void populate_SouthGrid(std::map<int , int> m);
    void populate_EastGrid(std::map<int , int> m);
    void populate_WestGrid(std::map<int , int> m);


    SC_HAS_PROCESS(processingModule);
    processingModule(sc_module_name name) : sc_module(name) {
      SC_THREAD(processingProcess);
      sensitive<<clock.pos();
      SC_THREAD(readData);
      sensitive<<triggerFromRobot1.pos()<<triggerFromRobot2.pos();
    };

   private:
     int newRobotStatus[3];

     int crossingFlag[3];
     int obstacleFlag[3];
     int eventFlag[3];
     bool obstacleDir =  false;

     bool wasBlocked[3] = {false, false, false};

     int dataToRobot[3];

     void updateRobotLocation(){
       for(int i = 1; i<=2; i++){
         if(newRobotStatus[i] == 0 || newRobotStatus[i] == 2){ //status ==OK or RESUME
           switch(robotDir[i]){
             case 0: //north
               robotPointLocation[i].y += 0.2;
               break;
             case 1: //south
               robotPointLocation[i].y -= 0.2;
               break;
             case 2: //east
               robotPointLocation[i].x += 0.2;
               break;
             case 3: //west
               robotPointLocation[i].x -= 0.2;
               break;
             deafult:
               break;
           }

         }
       }
     }

     void updateObstacleLocation(){
       if(bool){
         obstaclePointLocation[1].x -= 0.4;
         obstaclePointLocation[2].x -= 0.4;
         bool = ~bool;
       }
       else{
         obstaclePointLocation[1].x += 0.4;
         obstaclePointLocation[2].x += 0.4;
         bool = ~bool;
       }
     }

     void isCrossing(){
       for(int i = 1; i<=2; i++){
         if(robotDir[i]==0){//Going north
           crossingFlag[i] = ((x2y2[robotGridLocation].y - robotPointLocation[i].y)>0.2)?0:1;
           eventFlag[i] = (crossingFlag[i] == 1)?1:0;
         }
         else if  (robotDir[i] == 1){//Going South
           crossingFlag[i] = ((robotPointLocation[i].y - x1y1[robotGridLocation].y )>0.2)?0:1;
           eventFlag[i] = (crossingFlag[i] == 1)?1:0;
         }
         else if  (robotDir[i] == 2){//Going East
           crossingFlag[i] = ((robotPointLocation[i].x - x2y2[robotGridLocation].x )>0.2)?0:1;
           eventFlag[i] = (crossingFlag[i] == 1)?1:0;
         }
         else if  (robotDir[i] == 3){//Going West
           crossingFlag[i] = ((robotPointLocation[i].x - x2y2[robotGridLocation].x )>0.2)?0:1;
           eventFlag[i] = (crossingFlag[i] == 1)?1:0;
         }
         else{
           crossingFlag[i] = 0;
         }
       }
     }

     void obstacleProximity(){
       for(int i = 1; i<=2; i++){ //for both robots
         for(int j =1; j<=2; j++){ //for both obstacles
           int obstacle_x = obstaclePointLocation[j].x;
           int obstacle_y = obstaclePointLocation[j].y;
           int obstacle_xMax = obstacle_x + obstacleSpan[j]*2;

           if(robotDir[i]==0){//Robot Going north
             if((obstaclePointLocation[j].y - robotPointLocation[i].y)>3 ||
                (obstaclePointLocation[j].y - robotPointLocation[i].y)<0){
               continue;
             }
             int nextGrid_x = x1y1[NorthGrid[robotGridLocation]].x;
             if(((obstacle_x<nextGrid_x)&&(obstacle_xMax < nextGrid_x))
                ||((obstacle_x>nextGrid_x)&&(obstacle_xMax > nextGrid_x))){
                obstacleFlag[i] = 0;
             }
             else{
               obstacleFlag[i] = 1;
               eventFlag[i] = 1;
               wasBlocked[i] = true;
             }

           }

           else if (robotDir[i] == 1){ //Robot going South
             if((robotPointLocation[i].y - obstaclePointLocation[j].y)>3 ||
                (robotPointLocation[i].y - obstaclePointLocation[j].y)<0){
               continue;
             }
             int nextGrid_x = x1y1[SouthGrid[robotGridLocation]].x;
             if(((obstacle_x<nextGrid_x)&&(obstacle_xMax < nextGrid_x))
                ||((obstacle_x>nextGrid_x)&&(obstacle_xMax > nextGrid_x))){
                obstacleFlag[i] = 0;
             }
             else{
               obstacleFlag[i] = 1;
               eventFlag[i] = 1;
               wasBlocked[i] = true;
             }
           }

           else if (robotDir[i] == 2){//going East
             if((obstaclePointLocation[j].x - robotPointLocation[i].x)>3 ||
                (obstaclePointLocation[j].x - robotPointLocation[i].x)<0){
               continue;
             }
             int nextGrid_y = x1y1[EastGrid[robotGridLocation]].y;
             if(nextGrid_y != obstacle_y){
                obstacleFlag[i] = 0;
             }
             else{
               obstacleFlag[i] = 1;
               eventFlag[i] = 1;
               wasBlocked[i] = true;
             }
           }

           else if (robotDir[i] == 3){// going west
             if((robotPointLocation[i].x - obstaclePointLocation[j].x)>3 ||
                (robotPointLocation[i].x - obstaclePointLocation[j].x)<0){
               continue;
             }
             int nextGrid_y = x1y1[WestGrid[robotGridLocation]].y;
             if(nextGrid_y != obstacle_y){
                obstacleFlag[i] = 0;
             }
             else{
               obstacleFlag[i] = 1;
               eventFlag[i] = 1;
               wasBlocked[i] = true;
             }
           }
           else{
             obstacleFlag[i] = 0;
           }


         }

       }

     }

     void sendStatus(){
       for(int i = 1; i<=2; i++){
         if(crossingFlag[i] == 1){
           dataToRobot[i] = 0;
         }
         else if(obstacleFlag[i] == 1){
           dataToRobot[i] = 1;
         }
         else{
           if(wasBlocked[i]){
             dataToRobot[i] = 2;
             wasBlocked[i] = false;
           }
         }
       }
       if(eventFlag[1] == 1){
         dataToRobot1.write(dataToRobot[1]);
         triggerToRobot1.write(1);
         wait(10, SC_NS);
         triggerToRobot1.write(0);
       }
       if(eventFlag[2] == 1){
         dataToRobot2.write(dataToRobot[2]);
         triggerToRobot2.write(1);
         wait(10, SC_NS);
         triggerToRobot2.write(0);
       }
       for(int i = 1; i<=2; i++){ //clear all the flags
         crossingFlag[i] = 0;
         obstacleFlag[i] = 0;
         eventFlag[i] = 0;
       }

     }

     void readData(){
       if(triggerFromRobot1.read()==1){
          newRobotStatus[1] = dataFromRobot1.read();
       }
       else{
         newRobotStatus[2] =  dataFromRobot2.read();
       }
     }
     void processingProcess(){
       updateRobotLocation();
       isCrossing();
       updateObstacleLocation();
       obstacleProximity();
       sendStatus();
     }


};
#endif
