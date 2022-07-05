/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Failure.h
 * Author: rlcancian
 *
 * Created on 20 de Failureembro de 2019, 20:07
 */

#ifndef FAILURE_H
#define FAILURE_H


#include "../../kernel/simulator/ModelDataDefinition.h"
#include "../../kernel/simulator/ModelDataManager.h"
#include "../../kernel/simulator/PluginInformation.h"

class Resource;

/*!
Failure module
DESCRIPTION
The Failure module is designed for use with resources. When a failure occurs, the
entire resource (regardless of its capacity) is failed. Failures are designed to be used
with single-capacity resources or with multiple-capacity resources whose individual
resource units all fail at the same time.
TYPICAL USES
 * Breakdown information for a machine
 * Cash register tape refill every “x” customers
 * Random computer shutdowns or restarts
PROMPTS
Recordset Name of the recordset in the specified file from which to read
values. This field is available only if you specify a File Name
with a file access type, path, and recordset. Arena uses the Rows
and Columns properties to determine the amount of data to read
from the recordset. A recordset is required for all file types
except .xml. The recordset size must be equal to or greater than
the number of rows and columns specified for the expression.
Expression Values Lists the value or values of the expression. This property is not
available if you specify a File Name from which to read
expression values.
Expression Value Expression value associated with the expression name.
Prompt Description
Name The name of the failure associated with one or more resources.
Type Determines if the failure is time-based or count-based.
Count Defines the number of resource releases for count-based failures.
Valid when the Type is Count.
Up Time Defines the time between failures for time-based failures. Valid
when the Type is Time.
Up Time Units Time units for the time between failures (Up Time) for timebased failures.
Down Time Defines the duration of the failure.
Down Time Units Time units for the duration of the failure (Down Time).
Uptime in this State
only
Defines the state that should be considered for the time between
failures (only for time-based failures). If state is not specified,
then all states are considered (that is, the time between failures
does not depend on the time spent in a specific state, but rather
on the total simulation time). For example, you might want to
define a failure to be based only on the state Busy, and therefore,
the time between downtimes would be based on the amount of
time that a resource is busy, not simulated clock time.
 */
class Failure : public ModelDataDefinition {
public:

    enum class FailureType : int {
        COUNT = 1, TIME = 2
    };

	enum class FailureRule : int {
		IGNORE = 1, PREEMPT = 2, WAIT = 3
	};

public:
    Failure(Model* model, std::string name = "");
    virtual ~Failure() = default;
public: // static
    static ModelDataDefinition* LoadInstance(Model* model, std::map<std::string, std::string>* fields);
    static PluginInformation* GetPluginInformation();
    static ModelDataDefinition* NewInstance(Model* model, std::string name = "");
public: 
    virtual std::string show();
    bool isGoingToFailOnCount(Resource* resource);
public: // gets & sets
    void setFailureType(FailureType _failureType);
    Failure::FailureType getFailureType() const;
    void setCountExpression(std::string countExpression);
    std::string getCountExpression() const;
    void setDownTimeTimeUnit(Util::TimeUnit downTimeTimeUnit);
    Util::TimeUnit getDownTimeTimeUnit() const;
    void setDownTimeExpression(std::string downTimeExpression);
    std::string getDownTimeExpression() const;
    void setUpTimeTimeUnit(Util::TimeUnit upTimeTimeUnit);
    Util::TimeUnit getUpTimeTimeUnit() const;
    void setUpTimeExpression(std::string upTimeExpression);
    std::string getUpTimeExpression() const;
    void setFailureRule(FailureRule _failureRule);
    FailureRule getFailureRule() const;

protected: // must be overriden
    virtual bool _loadInstance(std::map<std::string, std::string>* fields);
    virtual std::map<std::string, std::string>* _saveInstance(bool saveDefaultValues);
protected: // could be overriden .
    virtual bool _check(std::string* errorMessage);
    virtual void _initBetweenReplications();
    //virtual void _createInternalAndAttachedData();
    //virtual ParserChangesInformation* _getParserChangesInformation();
private:

    const struct DEFAULT_VALUES {
        FailureType failureType = FailureType::TIME;
        FailureRule failureRule = FailureRule::IGNORE;
        std::string countExpression = "";
        std::string upTimeExpression = "";
        Util::TimeUnit upTimeTimeUnit = Util::TimeUnit::second;
        std::string downTimeExpression = "";
        Util::TimeUnit downTimeTimeUnit = Util::TimeUnit::second;
    } DEFAULT;
    FailureType _failureType = DEFAULT.failureType;
    FailureRule _failureRule = DEFAULT.failureRule;
    std::string countExpression = DEFAULT.countExpression;
    std::string upTimeExpression = DEFAULT.upTimeExpression;
    Util::TimeUnit upTimeTimeUnit = DEFAULT.upTimeTimeUnit;
    std::string downTimeExpression = DEFAULT.downTimeExpression;
    Util::TimeUnit downTimeTimeUnit = DEFAULT.downTimeTimeUnit;
private:
    std::map<Resource*, unsigned int>* _releaseCounts = new std::map<Resource*, unsigned int>();
};

#endif /* FAILURE_H */

