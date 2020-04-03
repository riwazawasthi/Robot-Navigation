#ifndef ROBOT_H
#define ROBOT_H

#include"systemc.h"

class robotModule : public sc_module {
	public:
		// Inputs
		sc_in<bool> triggerFromServer , triggerFromProcessing;
		sc_in<int> dataFromServer , dataFromProcessing;

		// Outputs
		sc_out<int> dataToServer , dataToProcessing;
    sc_out<bool> triggerToServer, triggerToProcessing;

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

		void relayToServer ();
		void relayToProcessing ();
		void robotProcess ();
};

#endif
