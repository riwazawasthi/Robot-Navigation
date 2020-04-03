#include "processing.h"

void processingModule::updateRobotLocation(){
  for(int i = 1; i<=2; i++){
    if(newRobotStatus[i] == 0 || newRobotStatus[i] == 2){ //status ==OK or RESUME
      //std::cout<<"here"<<endl;
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

void processingModule::updateObstacleLocation(){
  if(obstacleDir){
    obstaclePointLocation[1].x -= 0.4;
    obstaclePointLocation[2].x -= 0.4;
    obstacleDir = ~obstacleDir;
  }
  else{
    obstaclePointLocation[1].x += 0.4;
    obstaclePointLocation[2].x += 0.4;
    obstacleDir = ~obstacleDir;
  }
}

void processingModule::isCrossing(){
  for(int i = 1; i<=2; i++){
    if(robotDir[i]==0){//Going north
      crossingFlag[i] = (((x2y2[robotCurrentGrid[i]]).y - (robotPointLocation[i]).y)>0.2)?0:1;
      eventFlag[i] = (crossingFlag[i] == 1)?1:0;
    }
    else if  (robotDir[i] == 1){//Going South
      crossingFlag[i] = ((robotPointLocation[i].y - x1y1[robotCurrentGrid[i]].y )>0.2)?0:1;
      eventFlag[i] = (crossingFlag[i] == 1)?1:0;
    }
    else if  (robotDir[i] == 2){//Going East
      crossingFlag[i] = ((x2y2[robotCurrentGrid[i]].x - robotPointLocation[i].x )>0.2)?0:1;
      eventFlag[i] = (crossingFlag[i] == 1)?1:0;
    }
    else if  (robotDir[i] == 3){//Going West
      crossingFlag[i] = ((robotPointLocation[i].x - x2y2[robotCurrentGrid[i]].x )>0.2)?0:1;
      eventFlag[i] = (crossingFlag[i] == 1)?1:0;
    }
    else{
      crossingFlag[i] = 0;
    }
  }
}

void processingModule::obstacleProximity(){
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
        int nextGrid_x = x1y1[NorthGrid[robotCurrentGrid[i]]].x;
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
        int nextGrid_x = x1y1[SouthGrid[robotCurrentGrid[i]]].x;
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
        int nextGrid_y = x1y1[EastGrid[robotCurrentGrid[i]]].y;
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
        int nextGrid_y = x1y1[WestGrid[robotCurrentGrid[i]]].y;
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

void processingModule::sendStatus(){
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
    wait(2, SC_MS);
    triggerToRobot1.write(0);
  }
  if(eventFlag[2] == 1){
    dataToRobot2.write(dataToRobot[2]);
    triggerToRobot2.write(1);
    wait(2, SC_MS);
    triggerToRobot2.write(0);
  }
  for(int i = 1; i<=2; i++){ //clear all the flags
    crossingFlag[i] = 0;
    obstacleFlag[i] = 0;
    eventFlag[i] = 0;
  }

}

void processingModule::readData(){
  newRobotStatus[1] = dataFromRobot1.read();

  newRobotStatus[2] =  dataFromRobot2.read();

}
void processingModule::processingProcess(){
  if(!reset){
    init();
  }
  else{
    cout<<"here"<<endl;
    updateRobotLocation();
    isCrossing();
    updateObstacleLocation();
    obstacleProximity();
    sendStatus();
  }

}

void processingModule:: init(){
  dataToRobot1.write(dataToRobot[1]);
  triggerToRobot1.write(1);
  wait(2, SC_MS);
  triggerToRobot1.write(0);
  dataToRobot2.write(dataToRobot[2]);
  triggerToRobot2.write(1);
  wait(2, SC_MS);
  triggerToRobot2.write(0);

}
