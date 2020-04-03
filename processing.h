#ifndef PROCESSING_H
#define PROCESSING_H

#include"systemc.h"
#include "data_structures.h"

class processingModule:public sc_module{
  public:
    sc_in<bool> clock,reset, triggerFromRobot1, triggerFromRobot2;
    sc_in<int> dataFromRobot1,dataFromRobot2;

    sc_out<bool> triggerToRobot1,triggerToRobot2;
    sc_out<int> dataToRobot1,dataToRobot2;




    SC_HAS_PROCESS(processingModule);
    processingModule(sc_module_name name) : sc_module(name) {
      SC_THREAD(processingProcess);
      sensitive<<clock.pos();
      SC_THREAD(readData);
      sensitive<<triggerFromRobot1.pos()<<triggerFromRobot2.pos();

    };

   private:
     int newRobotStatus[3] = {1,1,1};

     int crossingFlag[3] = {};
     int obstacleFlag[3] = {};
     int eventFlag[3]={};
     bool obstacleDir =  false;

     bool wasBlocked[3] = {true, true, true};

     int dataToRobot[3] = {1, 1, 1};

     void updateRobotLocation();
     void updateObstacleLocation();
     void isCrossing();
     void obstacleProximity();
     void sendStatus();
     void readData();
     void processingProcess();
     void init();


};
#endif
