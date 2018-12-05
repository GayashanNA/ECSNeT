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

#include "CPUEpEnergyConsumer.h"
#include "inet/common/ModuleAccess.h"
#include "../../stask/ISTask.h"

namespace ecsnet_ {

Define_Module(CPUEpEnergyConsumer);

void CPUEpEnergyConsumer::initialize(int stage) {
    cSimpleModule::initialize(stage);
    if (stage == inet::INITSTAGE_LOCAL) {
        cpuBusyUtilisation = par("cpuBusyUtilisation").doubleValue();
        cpuIdleUtilisation = par("cpuIdleUtilisation").doubleValue();
        cpuPowerConsumptionScalar =
                par("cpuPowerConsumptionScalar").doubleValue();
        idlePowerConsumption = W(par("idlePowerConsumption"));

        cModule *host = findContainingNode(this);
//        host->subscribe(ISTask::cpuUtilisationSignal, this);
        host->subscribe(ISTask::cpuStateChangedSignal, this);
        powerConsumption = W(0);
        energySource = inet::getModuleFromPar<IEpEnergySource>(
                par("energySourceModule"), this);
//        std::cout << "Energy source=" << energySource->getNumEnergyConsumers()
//                << endl;
        energySource->addEnergyConsumer(this);
        WATCH(powerConsumption);
    }
}

W CPUEpEnergyConsumer::computeCPUPowerConsumption(double value) const {
    W _powerConsumption = W(0);
    if (value == States::CPU_BUSY) {
        _powerConsumption = W(cpuPowerConsumptionScalar * cpuIdleUtilisation);
//        std::cout << "CPU Idle consumption=" << _powerConsumption << endl;
    } else if (value == States::CPU_IDLE) {
        _powerConsumption = W(cpuPowerConsumptionScalar * cpuBusyUtilisation);
    } else {
        _powerConsumption = W(0);
    }
//    std::cout << "CPU Power consumption=" << _powerConsumption << endl;
    return _powerConsumption;
}

void CPUEpEnergyConsumer::receiveSignal(cComponent *source, simsignal_t signal,
        long value, cObject *details) {
    if (signal == ISTask::cpuStateChangedSignal) {
        powerConsumption = computeCPUPowerConsumption(value);
        emit(powerConsumptionChangedSignal, powerConsumption.get());
    } else
        throw cRuntimeError("Unknown signal");
}

} /* namespace ecsnet_ */
