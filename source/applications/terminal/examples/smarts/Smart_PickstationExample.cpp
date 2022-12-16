/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Smart_PickstationExample.h"

// you have to included need libs

// GEnSyS Simulator
#include "../../../../kernel/simulator/Simulator.h"


// Model Components
#include "../../../../plugins/components/Create.h"
#include "../../../../plugins/components/Dispose.h"
#include "../../../../plugins/components/Enter.h"
#include "../../../../plugins/components/PickStation.h"
#include "../../../../plugins/components/Process.h"
#include "../../../../plugins/components/Route.h"

#include "../../../../plugins/data/Queue.h"
#include "../../../../plugins/data/Resource.h"
#include "../../../../plugins/data/Station.h"

Smart_PickstationExample::Smart_PickstationExample() {
}

/**
 * This is the main function of the application. 
 * It instanciates the simulator, builds a simulation model and then simulate that model.
 */
int Smart_PickstationExample::main(int argc, char** argv) {
	Simulator* genesys = new Simulator();
	this->setDefaultTraceHandlers(genesys->getTracer());
	this->insertFakePluginsByHand(genesys);
	// crete model
	Model* model = genesys->getModels()->newModel();
	PluginManager* plugins = genesys->getPlugins();

//        Resource* resource1 = plugins->newInstance<Resource>(model, "Resource1");
//        Resource* resource2 = plugins->newInstance<Resource>(model, "Resource2");
        
	Create* create1 = plugins->newInstance<Create>(model, "Create_1");
	create1->setTimeBetweenCreationsExpression("expo(1)");
	create1->setTimeUnit(Util::TimeUnit::minute);

	Station* entry = plugins->newInstance<Station>(model, "Station_Entry");
	Enter* enterEntry = plugins->newInstance<Enter>(model, "Enter_Entry");
        enterEntry->setStation(entry);
        PickStation* pickStation1 = plugins->newInstance<PickStation>(model, "PickStation_1");
        //pickStation1->setTestCondition(PickStation::TestCondition::MINIMUM);
        //pickStation1->setPickCondition(PickStation::PickCondition::NUMBER_IN_QUEUE);
        //pickStation1->set
//
//        Station* station1 = plugins->newInstance<Station>(model, "Station_1");
//	Enter* enterStation1 = plugins->newInstance<Enter>(model, "Enter_Station_1");
//        enterStation1->setStation(station1);
//        Process* process1 = plugins->newInstance<Process>(model, "Process_1");
//	process1->getSeizeRequests()->insert(new SeizableItem(resource1, "1"));
//	process1->setQueueableItem(new QueueableItem(plugins->newInstance<Queue>(model)));
//        process1->setDelayTimeUnit(Util::TimeUnit::minute);
//        process1->setDelayExpression("tria(1,2,3)");
//        Route* route1 = plugins->newInstance<Route>(model, "Route_1");
//        route1->setRouteTimeTimeUnit(Util::TimeUnit::minute);
//        route1->setRouteTimeExpression("3");
//
//        Station* station2 = plugins->newInstance<Station>(model, "Station_2");
//	Enter* enterStation2 = plugins->newInstance<Enter>(model, "Enter_Station_2");
//        enterStation2->setStation(station2);
//        Process* process2 = plugins->newInstance<Process>(model, "Process_2");
//	process2->getSeizeRequests()->insert(new SeizableItem(resource2, "1"));
//	process2->setQueueableItem(new QueueableItem(plugins->newInstance<Queue>(model)));
//        process2->setDelayTimeUnit(Util::TimeUnit::minute);
//        process2->setDelayExpression("tria(1,2,3)");
//        Route* route2 = plugins->newInstance<Route>(model, "Route_2");
//        route2->setRouteTimeTimeUnit(Util::TimeUnit::minute);
//        route2->setRouteTimeExpression("3");
//        
//        Station* goodbye = plugins->newInstance<Station>(model, "Station_Goodbye");
//	Enter* enterGoodbye = plugins->newInstance<Enter>(model, "Enter_Goodbye");
//        enterGoodbye->setStation(goodbye);
	Dispose* dispose1 = plugins->newInstance<Dispose>(model, "Dispose_1");
        
        
	// connect model components to create a "workflow"
	create1->getConnections()->insert(enterEntry);
        enterEntry->getConnections()->insert(pickStation1);
        pickStation1->getConnections()->insert(dispose1);
        //pickStation1->getConnections()->insert(dispose1);
//        
//        enterStation1->getConnections()->insert(process1);
//        process1->getConnections()->insert(route1);
//        route1->setStation(goodbye);
//        
//        enterStation2->getConnections()->insert(process2);
//        process2->getConnections()->insert(route2);
//        route2->setStation(goodbye);
//        
//        enterGoodbye->getConnections()->insert(dispose1);
        
	// set options, save and simulate
        pickStation1->setReportStatistics(false);
	model->getSimulation()->setReplicationLength(1, Util::TimeUnit::minute);
	//model->getSimulation()->setTerminatingCondition("count(Dispose_1.CountNumberIn)>30");
	model->save("./models/Smart_PickstationExample.gen");
	model->getSimulation()->start();
	delete genesys;
	return 0;
};

