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

#include "StreamingNodeEnergyStorage.h"
#include "../contract/IEpEnergyConsumer.h"
#include "inet/common/ModuleAccess.h"

namespace ecsnet_ {

simsignal_t StreamingNodeEnergyStorage::residualEnergyCapacityChangedSignal = registerSignal("residualEnergyCapacityChanged");

Define_Module(StreamingNodeEnergyStorage);

void StreamingNodeEnergyStorage::initialize() {
//    if (stage == inet::INITSTAGE_LOCAL) {
        nominalCapacity = J(par("nominalCapacity"));
        residualCapacity = J(par("initialCapacity"));
        energyBalance = J(0);
        networkNode = findContainingNode(this);
        lastCPUEnergyBalanceUpdate = simTime();
        lastWirelessEnergyBalanceUpdate = simTime();
        networkNode->subscribe(IEpEnergyConsumer::CPUPowerConsumptionChangedSignal, this);
        networkNode->subscribe(IEpEnergyConsumer::WirelessPowerConsumptionChangedSignal, this);
        WATCH(energyBalance);
//    }
}

void StreamingNodeEnergyStorage::handleMessage(cMessage *msg) {

}

void StreamingNodeEnergyStorage::updateCPUEnergyBalance() {
    simtime_t currentSimulationTime = simTime();
    if (currentSimulationTime != lastCPUEnergyBalanceUpdate) {
        energyBalance = residualCapacity
                - s((currentSimulationTime - lastCPUEnergyBalanceUpdate).dbl())
                        * (totalPowerConsumption);
        lastCPUEnergyBalanceUpdate = currentSimulationTime;
        residualCapacity = energyBalance;
        emit(residualEnergyCapacityChangedSignal, energyBalance.get());
        std::cout << "CPU POWER res=" << residualCapacity.get() << " ebal="
                << energyBalance.get() << " cons=" << totalPowerConsumption
                << endl;
    }
}

void StreamingNodeEnergyStorage::updateWirelessEnergyBalance() {
    simtime_t currentSimulationTime = simTime();
    if (currentSimulationTime != lastWirelessEnergyBalanceUpdate) {
        energyBalance = residualCapacity
                - s((currentSimulationTime - lastWirelessEnergyBalanceUpdate).dbl())
                                * (totalPowerConsumption);
        lastWirelessEnergyBalanceUpdate = currentSimulationTime;
        residualCapacity = energyBalance;
        emit(residualEnergyCapacityChangedSignal, energyBalance.get());
        std::cout << "WIRELESS POWERres=" << residualCapacity.get() << " ebal="
                << energyBalance.get() << " cons=" << totalPowerConsumption
                << endl;
    }
}

void StreamingNodeEnergyStorage::receiveSignal(cComponent *source,
        simsignal_t signal, double value, cObject *details) {
    Enter_Method("receiveSignal");
    if(signal == IEpEnergyConsumer::CPUPowerConsumptionChangedSignal) {
        updateCPUEnergyBalance();
    } else if (signal == IEpEnergyConsumer::WirelessPowerConsumptionChangedSignal ) {
        updateWirelessEnergyBalance();
    }
}

} /* namespace ecsnet_ */
