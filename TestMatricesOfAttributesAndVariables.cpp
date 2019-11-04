/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestMatricesOfAttributesAndVariables.cpp
 * Author: rlcancian
 * 
 * Created on 1 de Novembro de 2019, 18:10
 */

#include "TestMatricesOfAttributesAndVariables.h"
#include "Simulator.h"
#include "SourceModelComponent.h"
#include "Assign.h"
#include "Attribute.h"
#include "Variable.h"
#include "Create.h"
#include "Dispose.h"
#include "Separate.h"
#include "Formula.h"
#include "Write.h"

TestMatricesOfAttributesAndVariables::TestMatricesOfAttributesAndVariables() {
}

TestMatricesOfAttributesAndVariables::TestMatricesOfAttributesAndVariables(const TestMatricesOfAttributesAndVariables& orig) {
}

TestMatricesOfAttributesAndVariables::~TestMatricesOfAttributesAndVariables() {
}

int TestMatricesOfAttributesAndVariables::main(int argc, char** argv) {
    Simulator* sim = new Simulator();
    setDefaultTraceHandlers(sim->tracer());
    sim->tracer()->setTraceLevel(Util::TraceLevel::mostDetailed);
    insertFakePluginsByHand(sim);
    Model* m = new Model(sim);
    sim->models()->insert(m);
    m->infos()->setProjectTitle("Stochastic Simulation of Chemical Reactions");
    Create* cr1 = new Create(m);
    Write* w1 = new Write(m);
    Assign* as1 = new Assign(m, "Define próxima reação a ocorrer");
    Dispose* di1 = new Dispose(m);
    cr1->nextComponents()->insert(w1);
    w1->nextComponents()->insert(as1);
    as1->nextComponents()->insert(di1);
    cr1->setEntityType(new EntityType(m));
    Variable* s = new Variable(m, "s");
    Variable* k = new Variable(m, "k");
    Variable* N = new Variable(m, "N");
    new Variable(m, "temp");
    Formula* prop = new Formula(m, "prop");
    s->setInitialValue("1,1", -1);
    s->setInitialValue("1,2", -1);
    s->setInitialValue("1,3", 1);
    s->setInitialValue("2,1", 0);
    s->setInitialValue("2,2", 0);
    s->setInitialValue("2,3", -1);
    k->setInitialValue("1", 0.1);
    k->setInitialValue("2", 0.01);
    N->setInitialValue("1", 100);
    N->setInitialValue("2", 100);
    N->setInitialValue("3", 0);
    prop->setExpression("1", "k[1]*N[1]*N[2]");
    prop->setExpression("2", "k[2]*N[3]");
    w1->writeElements()->insert(new WriteElement("N[1]",true, true));
    w1->writeElements()->insert(new WriteElement("N[2]",true, true));
    w1->writeElements()->insert(new WriteElement("N[3]",true, true));
    as1->assignments()->insert(new Assign::Assignment("temp[1]", "k[1]*N[1]*N[2]")); //"prop[1]/(prop[1]+prop[2])"));
    as1->assignments()->insert(new Assign::Assignment("temp[1]", "prop[1]/(prop[1]+prop[2])"));
    //
    m->simulation()->start();
    return 0;

    /*
    Create* create1 = new Create(m);
    Assign* assign1 = new Assign(m);
    //Separate* sep1 = new Separate(m);
    Dispose* dispose1 = new Dispose(m);
    create1->nextComponents()->insert(assign1);
    assign1->nextComponents()->insert(assign1);
    assign1->nextComponents()->insert(dispose1);
    //sep1->nextComponents()->insert(dispose1);
    //sep1>->nextComponents()->insert(assign1);
    create1->setEntityType(new EntityType(m));
    create1->setMaxCreations("1");
    new Attribute(m, "attr1");
    Variable* var1 = new Variable(m, "var1");
    std::string expression, index;
    for (int i = 1; i < 3; i++) {
	for (int j = 1; j < 3; j++) {
	    index = std::to_string(i) + "," + std::to_string(j);
	    var1->setInitialValue(index, 1.0*i + j / 10.0);
	    expression = "attr1[" + index + "] + var1[" + index + "]";
	    assign1->assignments()->insert(new Assign::Assignment("attr1[" + index + "]", expression));
	}
    }
    m->simulation()->start();
    return 0;
     */
}