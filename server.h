#ifndef SERVER_H
#define SERVER_H

#include "systemc.h"
#include "data_structures.h"

class serverModule:public sc_module{
  public:
    sc_in<bool> triggerFromRobot1, triggerFromRobot2;
    sc_in<int> dataFromRobot1, dataFromRobot2;

    sc_out<bool> triggerToRobot1, triggerToRobot2;
    sc_out<int> dataToRobot1, dataToRobot2;



    SC_HAS_PROCESS(serverModule);
    serverModule(sc_module_name name) : sc_module(name) {
      //SC_THREAD(readData);
      //sensitive<<triggerFromRobot1.pos()<<triggerFromRobot2.pos();
    //  SC_THREAD(transmitData);
      //sensitive<<triggerFromRobot1.pos()<<triggerFromRobot2.pos();
      SC_THREAD(update);
      sensitive<<triggerFromRobot1.pos()<<triggerFromRobot2.pos();
    };

    private:
      int newRobotStatus[3]={1,1,1};
      void readData();
      void transmitData();
      void update();






};
#endif
