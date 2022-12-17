/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Smart_OverlappingResources.h"

// you have to included need libs

// GEnSyS Simulator
#include "../../../../kernel/simulator/Simulator.h"


// Model Components
#include "../../../../plugins/components/Create.h"
#include "../../../../plugins/components/Dispose.h"
#include "../../../../plugins/components/Enter.h"
#include "../../../../plugins/components/Process.h"
#include "../../../../plugins/components/Seize.h"
#include "../../../../plugins/components/Delay.h"
#include "../../../../plugins/components/Release.h"

#include "../../../../plugins/data/Queue.h"
#include "../../../../plugins/data/Resource.h"

Smart_OverlappingResources::Smart_OverlappingResources() {
}

/**
 * This is the main function of the application. 
 * It instanciates the simulator, builds a simulation model and then simulate that model.
 */
int Smart_OverlappingResources::main(int argc, char** argv) {
	Simulator* genesys = new Simulator();
	this->setDefaultTraceHandlers(genesys->getTracer());
        genesys->getTracer()->setTraceLevel(TraceManager::Level::L2_results);
	this->insertFakePluginsByHand(genesys);
	// crete model
	Model* model = genesys->getModels()->newModel();
	PluginManager* plugins = genesys->getPlugins();

        Resource* resource3 = plugins->newInstance<Resource>(model, "Resource_3");
        Resource* resource4 = plugins->newInstance<Resource>(model, "Resource_4");
        
        Queue* seizeResource3Queue = plugins->newInstance<Queue>(model, "Seize_Resource_3_Queue");
        Queue* seizeResource4Queue = plugins->newInstance<Queue>(model, "Seize_Resource_4_Queue");
        
	Create* create2 = plugins->newInstance<Create>(model, "Create_2");
	create2->setTimeBetweenCreationsExpression("expo(5)");
	create2->setTimeUnit(Util::TimeUnit::minute);
        
        Seize* seizeResource3 = plugins->newInstance<Seize>(model, "Seize_Resource_3");
        seizeResource3->getSeizeRequests()->insert(new SeizableItem(resource3, "1"));
        seizeResource3->setQueue(seizeResource3Queue);
        
        Delay* delay1 = plugins->newInstance<Delay>(model, "Delay_1");
        delay1->setDelayExpression("expo(3)");
        delay1->setDelayTimeUnit(Util::TimeUnit::minute);
        
        Seize* seizeResource4 = plugins->newInstance<Seize>(model, "Seize_Resource_4");
        seizeResource4->getSeizeRequests()->insert(new SeizableItem(resource4, "1"));
        seizeResource4->setQueue(seizeResource4Queue);
        
        Release* releaseResource3 = plugins->newInstance<Release>(model, "Release_Resource_3");
        releaseResource3->getReleaseRequests()->insert(new SeizableItem(resource3, "1"));
        
        Delay* delay2 = plugins->newInstance<Delay>(model, "Delay_2");
        delay2->setDelayExpression("expo(4)");
        delay2->setDelayTimeUnit(Util::TimeUnit::minute);
        
        Release* releaseResource4 = plugins->newInstance<Release>(model, "Release_Resource_4");
        releaseResource4->getReleaseRequests()->insert(new SeizableItem(resource4, "1"));
        
        Dispose* dispose2 = plugins->newInstance<Dispose>(model, "Dispose_2");

        create2->getConnections()->insert(seizeResource3);
        seizeResource3->getConnections()->insert(delay1);
        delay1->getConnections()->insert(seizeResource4);
        seizeResource4->getConnections()->insert(releaseResource3);
        releaseResource3->getConnections()->insert(delay2);
        delay2->getConnections()->insert(releaseResource4);
        releaseResource4->getConnections()->insert(dispose2);
        
	model->getSimulation()->setReplicationLength(59, Util::TimeUnit::hour);
        model->getSimulation()->setWarmUpPeriod(2.95);
        model->getSimulation()->setWarmUpPeriodTimeUnit(Util::TimeUnit::hour);
        model->getSimulation()->setReplicationReportBaseTimeUnit(Util::TimeUnit::minute);
        model->getSimulation()->setNumberOfReplications(300);
	model->save("./models/Smart_OverlappingResources.gen");
	model->getSimulation()->start();
        for(int i = 0; i<1e9; i++); //wait for output
	delete genesys;
	return 0;
};

