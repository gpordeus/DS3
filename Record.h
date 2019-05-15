/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Record.h
 * Author: rafael.luiz.cancian
 *
 * Created on 9 de Maio de 2019, 13:52
 */

#ifndef RECORD_H
#define RECORD_H

#include "ModelComponent.h"
#include <string>

class Record : public ModelComponent {
public:
    Record(Model* model);
    Record(const Record& orig);
    virtual ~Record();
public:
    void setFilename(std::string filename);
    std::string getFilename() const;
    void setExpression(std::string expression);
    std::string getExpression() const;
    void setExpressionName(std::string expressionName);
    std::string getExpressionName() const;
    StatisticsCollector* getCstatExpression() const;
public:
    virtual std::string show();
protected:
    virtual void _execute(Entity* entity);
    virtual void _loadInstance(std::list<std::string> words);
    virtual std::list<std::string>* _saveInstance();
    virtual bool _verifySymbols(std::string* errorMessage);
private:
    std::string _expression = "";
    std::string _expressionName = "";
    std::string _filename = "";
private:
    StatisticsCollector* _cstatExpression;
};

#endif /* RECORD_H */

