#ifndef ROBOT_H
#define ROBOT_H

#include<systemc.h>

class robotModule : public sc_module {
	public:
		// Inputs
		sc_in<bool> triggerFromServer , triggerFromProcessing;
		sc_in<int> dataFromServer , dataFromProcessing;

		// Outputs
		sc_out<int> dataToServer , dataToProcessing;
    sc_out<bool> triggerToServer;

		SC_HAS_PROCESS(robotModule);
		robotModule(sc_module_name name , int robotId) : sc_module(name) {
			SC_THREAD(relayToProcessing);
			sensitive<<triggerFromServer.pos();
      SC_THREAD(relayToServer);
			sensitive<<triggerFromProcessing.pos();
      SC_THREAD(robotProcess);
      sensitive<<triggerFromServer.pos()<<triggerFromProcessing.pos();

			id = robotId;
		};

	private:
		int id;

		void relayToServer () {
			dataToServer.write(dataFromProcessing.read());
      triggerToServer.write(1);
      wait(10, SC_NS);
      triggerToServer.write(0);

		}

		void relayToProcessing () {
			dataToProcessing.write(dataFromServer.read());
		}

		void robotProcess () {
			//something for phase 2
		}
};

#endif
