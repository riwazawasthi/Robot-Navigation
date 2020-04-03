#include "robot.h"

void robotModule::relayToServer () {
  dataToServer.write(dataFromProcessing.read());
  triggerToServer.write(1);
  wait(2, SC_MS);
  triggerToServer.write(0);

}

void robotModule::relayToProcessing () {
  dataToProcessing.write(dataFromServer.read());
  triggerToProcessing.write(1);
  wait(2, SC_MS);
  triggerToProcessing.write(0);
}

void robotModule::robotProcess () {
  //something for phase 2
}
