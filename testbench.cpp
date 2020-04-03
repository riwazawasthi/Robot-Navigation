#include "systemc.h"
#include "processing.h"
#include "server.h"
#include "robot.h"

int sc_main(int argc , char* argv[]){

  sc_signal<bool> clock,reset, triggerToRobot1P, triggerToRobot2P, triggerToRobot1S, triggerToRobot2S;
  sc_signal<int> dataToRobot1P, dataToRobot2P, dataToRobot1S, dataToRobot2S;
  sc_signal<bool> triggerToServer1, triggerToProcessing1, triggerToServer2, triggerToProcessing2;
  sc_signal<int> dataToProcessing1, dataToServer1,dataToProcessing2, dataToServer2;

  robotModule *r1, *r2;
  serverModule *s;
  processingModule *p;

  r1 = new robotModule("r1", 1);
  r2 = new robotModule("r2", 2);
  s = new serverModule("s");
  p = new processingModule("p");

  r1->triggerFromServer(triggerToRobot1S);
  r1->triggerFromProcessing(triggerToRobot1P);
  r1->dataFromServer(dataToRobot1S);
  r1->dataFromProcessing(dataToRobot1P);
  r1->dataToServer(dataToServer1);
  r1->dataToProcessing(dataToProcessing1);
  r1->triggerToServer(triggerToServer1);
  r1->triggerToProcessing(triggerToProcessing1);

  r2->triggerFromServer(triggerToRobot2S);
  r2->triggerFromProcessing(triggerToRobot2P);
  r2->dataFromServer(dataToRobot2S);
  r2->dataFromProcessing(dataToRobot2P);
  r2->dataToServer(dataToServer2);
  r2->dataToProcessing(dataToProcessing2);
  r2->triggerToServer(triggerToServer2);
  r2->triggerToProcessing(triggerToProcessing2);

  s->triggerFromRobot1(triggerToServer1);
  s->triggerFromRobot2(triggerToServer2);
  s->dataFromRobot1(dataToServer1);
  s->dataFromRobot2(dataToServer2);
  s->triggerToRobot1(triggerToRobot1S);
  s->triggerToRobot2(triggerToRobot2S);
  s->dataToRobot1(dataToRobot1S);
  s->dataToRobot2(dataToRobot2S);

  p->clock(clock);
  p->reset(reset);
  p->triggerFromRobot1(triggerToProcessing1);
  p->triggerFromRobot2(triggerToProcessing2);
  p->dataFromRobot1(dataToProcessing1);
  p->dataFromRobot2(dataToProcessing2);
  p->triggerToRobot1(triggerToRobot1P);
  p->triggerToRobot2(triggerToRobot2P);
  p->dataToRobot1(dataToRobot1P);
  p->dataToRobot2(dataToRobot2P);

  //-----------------for VCD files---------------------------------------------

  sc_trace_file *fp =sc_create_vcd_trace_file("Navigation");

  sc_trace(fp, clock, "CLK");
  sc_trace(fp,triggerToRobot1P,"P_trigger_R1");
  sc_trace(fp,triggerToRobot2P,"P_trigger_R2");
  sc_trace(fp,triggerToRobot1S,"S_trigger_R1");
  sc_trace(fp,triggerToRobot2S,"S_trigger_R2");
  sc_trace(fp,dataToRobot1P,"PdataToRobot1");
  sc_trace(fp,dataToRobot2P,"PdataToRobot2");
  sc_trace(fp,dataToRobot1S,"SdataToRobot1");
  sc_trace(fp,dataToRobot2S,"SdataToRobot2");
  sc_trace(fp,triggerToServer1,"triggerFromR1ToServer");
  sc_trace(fp,triggerToProcessing1,"triggerFromR1ToProcessing");
  sc_trace(fp,triggerToServer2,"triggerFromR2ToServer");
  sc_trace(fp,triggerToProcessing2,"triggerFromR2ToProcessing");
  sc_trace(fp,dataToProcessing1,"dataFromR1ToProcessing");
  sc_trace(fp,dataToServer1,"dataFromR1ToServer");
  sc_trace(fp,dataToProcessing2,"dataFromR2ToProcessing");
  sc_trace(fp,dataToServer2,"dataFromR2ToServer");

  sc_start(0, SC_MS); //Initialize simulation;
  reset = 0;
  for(int i = 0; i<2; i++){
    clock = 0;
    sc_start(5, SC_MS);
    clock = 1;
    sc_start(5, SC_MS);
  }
  reset = 1;
  for(int i = 0; i<2; i++){
    clock = 0;
    sc_start(5, SC_MS);
    clock = 1;
    sc_start(5, SC_MS);
  }
  sc_close_vcd_trace_file(fp);


  return 0;
}
