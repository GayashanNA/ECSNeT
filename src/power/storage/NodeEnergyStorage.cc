//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "NodeEnergyStorage.h"
#include "inet/common/lifecycle/NodeOperations.h"
#include "inet/common/ModuleAccess.h"

namespace ecsnet_ {

Define_Module(NodeEnergyStorage);

NodeEnergyStorage::~NodeEnergyStorage()
{
    cancelAndDelete(timer);
}

void NodeEnergyStorage::initialize(int stage)
{
    EpEnergyStorageBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        nominalCapacity = J(par("nominalCapacity"));
        printCapacityStep = J(par("printCapacityStep"));
        timer = new cMessage("timer");
        networkNode = findContainingNode(this);
        if (networkNode != nullptr) {
            nodeStatus = dynamic_cast<NodeStatus *>(networkNode->getSubmodule("status"));
            if (!nodeStatus)
                throw cRuntimeError("Cannot find node status");
            lifecycleController = dynamic_cast<LifecycleController *>(getModuleByPath("lifecycleController"));
            if (!lifecycleController)
                throw cRuntimeError("Cannot find lifecycle controller");
        }
        setResidualCapacity(J(par("initialCapacity")));
        scheduleTimer();
        WATCH(residualCapacity);
    }
}

void NodeEnergyStorage::handleMessage(cMessage *message)
{
    if (message == timer) {
        setResidualCapacity(targetCapacity);
        scheduleTimer();
        EV_INFO << "Residual capacity = " << residualCapacity.get() << " (" << (int)round(unit(residualCapacity / nominalCapacity).get() * 100) << "%)" << endl;
    }
    else
        throw cRuntimeError("Unknown message");
}

void NodeEnergyStorage::updateTotalPowerConsumption()
{
    updateResidualCapacity();
    EpEnergyStorageBase::updateTotalPowerConsumption();
    scheduleTimer();
}

void NodeEnergyStorage::updateTotalPowerGeneration()
{
    updateResidualCapacity();
    EpEnergyStorageBase::updateTotalPowerGeneration();
    scheduleTimer();
}

void NodeEnergyStorage::executeNodeOperation(J newResidualCapacity)
{
    if (newResidualCapacity <= J(0) && nodeStatus->getState() == NodeStatus::UP) {
        EV_WARN << "Energy storage failed" << endl;
        LifecycleOperation::StringMap params;
        NodeCrashOperation *operation = new NodeCrashOperation();
        operation->initialize(networkNode, params);
        lifecycleController->initiateOperation(operation);
    }
}

J NodeEnergyStorage::getResidualEnergyCapacity() const
{
    const_cast<NodeEnergyStorage *>(this)->updateResidualCapacity();
    return residualCapacity;
}

void NodeEnergyStorage::setResidualCapacity(J newResidualCapacity)
{
    residualCapacity = newResidualCapacity;
    lastResidualCapacityUpdate = simTime();
    if (residualCapacity == J(0))
        EV_WARN << "Energy storage depleted" << endl;
    else if (residualCapacity == nominalCapacity)
        EV_INFO << "Energy storage charged" << endl;
    if (networkNode != nullptr)
        executeNodeOperation(newResidualCapacity);
    emit(residualEnergyCapacityChangedSignal, residualCapacity.get());
}

void NodeEnergyStorage::updateResidualCapacity()
{
    simtime_t currentSimulationTime = simTime();
    if (currentSimulationTime != lastResidualCapacityUpdate) {
        J newResidualCapacity = residualCapacity + s((currentSimulationTime - lastResidualCapacityUpdate).dbl()) * (totalPowerGeneration - totalPowerConsumption);
        if (newResidualCapacity < J(0))
            newResidualCapacity = J(0);
        else if (newResidualCapacity > nominalCapacity)
            newResidualCapacity = nominalCapacity;
        setResidualCapacity(newResidualCapacity);
    }
}

void NodeEnergyStorage::scheduleTimer()
{
    W totalPower = totalPowerGeneration - totalPowerConsumption;
    targetCapacity = residualCapacity;
    if (totalPower > W(0)) {
        targetCapacity = std::isnan(printCapacityStep.get()) ? nominalCapacity : ceil(unit(residualCapacity / printCapacityStep).get()) * printCapacityStep;
        // NOTE: make sure capacity will change over time despite double arithmetic
        simtime_t remainingTime = unit((targetCapacity - residualCapacity) / totalPower / s(1)).get();
        if (remainingTime == 0)
            targetCapacity += printCapacityStep;
    }
    else if (totalPower < W(0)) {
        targetCapacity = std::isnan(printCapacityStep.get()) ? J(0) : floor(unit(residualCapacity / printCapacityStep).get()) * printCapacityStep;
        // make sure capacity will change over time despite double arithmetic
        simtime_t remainingTime = unit((targetCapacity - residualCapacity) / totalPower / s(1)).get();
        if (remainingTime == 0)
            targetCapacity -= printCapacityStep;
    }
    // enforce target capacity to be in range
    if (targetCapacity < J(0))
        targetCapacity = J(0);
    else if (targetCapacity > nominalCapacity)
        targetCapacity = nominalCapacity;
    simtime_t remainingTime = unit((targetCapacity - residualCapacity) / totalPower / s(1)).get();
    if (timer->isScheduled())
        cancelEvent(timer);
    // don't schedule if there's no progress
    if (remainingTime > 0)
        scheduleAt(simTime() + remainingTime, timer);
}

//void NodeEnergyStorage::addEnergyConsumer(const IEnergyConsumer *energyConsumer)
//{
//    EnergySourceBase::addEnergyConsumer(energyConsumer);
//    auto module = const_cast<cModule *>(check_and_cast<const cModule *>(energyConsumer));
//    module->subscribe(IEpEnergyConsumer::powerConsumptionChangedSignal, this);
//    updateTotalPowerConsumption();
//}
//
void NodeEnergyStorage::receiveSignal(cComponent *source, simsignal_t signal, double value, cObject *details)
{
    Enter_Method("receiveSignal");
    if (signal == IEpEnergyConsumer::powerConsumptionChangedSignal)
        updateTotalPowerConsumption();
    else if (signal == IEpEnergyGenerator::powerGenerationChangedSignal)
        updateTotalPowerGeneration();
}


} /* namespace ecsnet_ */
