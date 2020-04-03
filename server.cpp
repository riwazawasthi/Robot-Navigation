#include "server.h"

void serverModule::readData(){
  if(triggerFromRobot1.read()==1){
    newRobotStatus[1] = dataFromRobot1.read();
  }
  else{
    newRobotStatus[2] = dataFromRobot2.read();
  }
}

void serverModule::transmitData(){
  if(triggerFromRobot1.read()==1){
    dataToRobot1.write(robotStatus[1]);
    triggerToRobot1.write(1);
    wait(2, SC_MS);
    triggerToRobot1.write(0);
  }
  else{
    dataToRobot2.write(robotStatus[2]);
    triggerToRobot2.write(1);
    wait(2, SC_MS);
    triggerToRobot2.write(0);
  }
}

void serverModule:: update(){
  readData();
  for(int i = 1; i<=2; i++){
    if(newRobotStatus[i]==0){ //crossing
      for(int j = 1; j<=2; j++){
        if((robotNextGrid[i]==robotCurrentGrid[j])&&(i!=j)){
          robotStatus[i] = 1;
          break;
        }
      }
      if(indexPath[i]>=0){
        robotCurrentGrid[i] = robotNextGrid[i];
        robotNextGrid[i] = robotPath[i].at(indexPath[i]);
        indexPath[i] = indexPath[i] - 1;
        if(robotNextGrid[i] == NorthGrid[robotCurrentGrid[i]]){
          robotDir[i] = 0;
        }
        else if(robotNextGrid[i] == SouthGrid[robotCurrentGrid[i]]){
          robotDir[i] = 1;
        }
        else if(robotNextGrid[i] == EastGrid[robotCurrentGrid[i]]){
          robotDir[i] = 2;
        }
        else{
          robotDir[i] = 3;
        }
      }
      else{
        robotDir[i] = -1;
      }
      robotStatus[i] = 0;

    }
    else if(newRobotStatus[i] == 1){//stopped due to obstacle
      robotStatus[i] = 1;
    }
    else{ //resuming
      robotStatus[i] = 2;
    }
    transmitData();

  }

}
