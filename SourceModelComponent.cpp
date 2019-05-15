/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SourceModelCOmponent.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 21 de Junho de 2018, 19:50
 */

#include "SourceModelComponent.h"

SourceModelComponent::SourceModelComponent(Model* model, std::string componentTypename) : ModelComponent(model, componentTypename) {
}

SourceModelComponent::SourceModelComponent(const SourceModelComponent& orig) : ModelComponent(orig) {
}

SourceModelComponent::~SourceModelComponent() {
}

std::string SourceModelComponent::show() {
    std::string text = ModelComponent::show() +
            ",entityType=\"" + _entityType->getName() + "\"" +
            ",firstCreation=" + std::to_string(_firstCreation);
    return text;
}

void SourceModelComponent::setFirstCreation(double _firstCreation) {
    this->_firstCreation = _firstCreation;
}

double SourceModelComponent::getFirstCreation() const {
    return _firstCreation;
}

void SourceModelComponent::setCollectStatistics(bool _collectStatistics) {
    this->_collectStatistics = _collectStatistics;
}

bool SourceModelComponent::isCollectStatistics() const {
    return _collectStatistics;
}

void SourceModelComponent::setEntityType(EntityType* entityType) {
    _entityType = entityType;
}

EntityType* SourceModelComponent::getEntityType() const {
    return _entityType;
}

void SourceModelComponent::setTimeUnit(Util::TimeUnit _timeUnit) {
    this->_timeBetweenCreationsTimeUnit = _timeUnit;
}

Util::TimeUnit SourceModelComponent::getTimeUnit() const {
    return this->_timeBetweenCreationsTimeUnit;
}

void SourceModelComponent::setTimeBetweenCreationsExpression(std::string _timeBetweenCreations) {
    this->_timeBetweenCreationsExpression = _timeBetweenCreations;
}

std::string SourceModelComponent::getTimeBetweenCreationsExpression() const {
    return _timeBetweenCreationsExpression;
}

void SourceModelComponent::setMaxCreations(unsigned int _maxCreations) {
    this->_maxCreations = _maxCreations;
}

unsigned int SourceModelComponent::getMaxCreations() const {
    return _maxCreations;
}

unsigned int SourceModelComponent::getEntitiesCreated() const {
    return _entitiesCreatedSoFar;
}

void SourceModelComponent::setEntitiesCreated(unsigned int _entitiesCreated) {
    this->_entitiesCreatedSoFar = _entitiesCreated;
}

void SourceModelComponent::setEntitiesPerCreation(unsigned int _entitiesPerCreation) {
    this->_entitiesPerCreation = _entitiesPerCreation;
}

unsigned int SourceModelComponent::getEntitiesPerCreation() const {
    return _entitiesPerCreation;
}

