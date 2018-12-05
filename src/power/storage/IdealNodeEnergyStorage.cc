//
// Copyright (C) OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "IdealNodeEnergyStorage.h"
#include "inet/common/ModuleAccess.h"
#include "../consumer/NetworkPowerConsumer.h"
#include "../consumer/CPUPowerConsumer.h"

using namespace inet;
using namespace inet::power;

namespace ecsnet_ {

simsignal_t IdealNodeEnergyStorage::energyConsumptionChangedSignal = registerSignal("energyConsumptionChanged");
simsignal_t IdealNodeEnergyStorage::powerConsumptionChangedSignal = registerSignal("powerConsumptionChanged");
simsignal_t IdealNodeEnergyStorage::idleEnergyConsumptionChangedSignal = registerSignal("idleEnergyConsumptionChanged");
//simsignal_t IdealNodeEnergyStorage::idlePowerConsumptionChangedSignal = registerSignal("idlePowerConsumptionChanged");
simsignal_t IdealNodeEnergyStorage::cpuEnergyConsumptionChangedSignal = registerSignal("cpuEnergyConsumptionChanged");
simsignal_t IdealNodeEnergyStorage::networkEnergyConsumptionChangedSignal = registerSignal("networkEnergyConsumptionChanged");
simsignal_t IdealNodeEnergyStorage::residualCapacityChangedSignal = registerSignal("residualCapacityChanged");

Define_Module(IdealNodeEnergyStorage);

void IdealNodeEnergyStorage::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        cores = getAncestorPar("cores").longValue();
        idlePowerConsumption = W(par("idlePowerConsumption"));
        nominalCapacity = J(par("nominalCapacity"));
        residualCapacity = J(par("initialCapacity"));
        energyBalance = J(0);
        cpuEnergyConsumption = J(0);
        networkEnergyConsumption = J(0);
        totalEnergyConsumption = J(0);
        totalPowerConsumption = W(0);
        totalIdlePowerConsumption = W(0);
        networkNode = findContainingNode(this);
//        lastCPUEnergyBalanceUpdate = simTime();
        omnetpp::simtime_t _simtime = simTime();
        for (int i = 0; i < cores; i++) {
            lastCPUEnergyBalanceUpdateMap[i] = _simtime;
        }
        lastWirelessEnergyBalanceUpdate = _simtime;
        startTime = _simtime;
        networkNode->subscribe(CPUPowerConsumer::cpuPowerConsumptionChangedSignal, this);
        networkNode->subscribe(NetworkPowerConsumer::networkPowerConsumptionChangedSignal, this);
//        WATCH(energyBalance);
    }
}

//void IdealNodeEnergyStorage::updateTotalPowerConsumption() {
////    updateEnergyBalance();
//    EpEnergyStorageBase::updateTotalPowerConsumption();
//}
//
//void IdealNodeEnergyStorage::updateTotalPowerGeneration() {
////    updateEnergyBalance();
//    EpEnergyStorageBase::updateTotalPowerGeneration();
//}

//void IdealNodeEnergyStorage::updateEnergyBalance() {
//    simtime_t currentSimulationTime = simTime();
//    if (currentSimulationTime != lastEnergyBalanceUpdate) {
//        energyBalance += s(
//                (currentSimulationTime - lastEnergyBalanceUpdate).dbl())
//                * (totalPowerGeneration - totalPowerConsumption);
//        lastEnergyBalanceUpdate = currentSimulationTime;
//        emit(residualEnergyCapacityChangedSignal, energyBalance.get());
//    }
//}

void IdealNodeEnergyStorage::updateCPUEnergyBalance(W _totalPowerConsumption, long index) {
    simtime_t currentSimulationTime = simTime();
    J _energyConsumption = J(0);
    if (currentSimulationTime != lastCPUEnergyBalanceUpdateMap[index]) {
        _energyConsumption = J(s((currentSimulationTime - lastCPUEnergyBalanceUpdateMap[index]).dbl())
                        * (W(_totalPowerConsumption)));
        lastCPUEnergyBalanceUpdateMap[index] = currentSimulationTime;
        residualCapacity -= _energyConsumption;
        cpuEnergyConsumption += _energyConsumption;
        totalEnergyConsumption += _energyConsumption;
//        totalPowerConsumption += (_totalPowerConsumption) + (idlePowerConsumption);
        totalPowerConsumption += (_totalPowerConsumption);

        emit(cpuEnergyConsumptionChangedSignal, cpuEnergyConsumption.get());

//        EV << "CPU Energy consumption=" << _energyConsumption << endl;
//        emit(residualEnergyCapacityChangedSignal, energyBalance.get());
//        std::cout << "CPU POWER res=" << residualCapacity << " ebal="
//                << energyConsumption << " cons=" << totalPowerConsumption
//                << " index=" << index
//                << endl;
    }
}

void IdealNodeEnergyStorage::updateWirelessEnergyBalance(W _totalPowerConsumption) {
    simtime_t currentSimulationTime = simTime();
    J _energyConsumption = J(0);
    if (currentSimulationTime != lastWirelessEnergyBalanceUpdate) {
        _energyConsumption = J(s((currentSimulationTime - lastWirelessEnergyBalanceUpdate).dbl())
                                * (W(_totalPowerConsumption)));
        lastWirelessEnergyBalanceUpdate = currentSimulationTime;
        residualCapacity -= _energyConsumption;
        networkEnergyConsumption += _energyConsumption;
        totalEnergyConsumption += _energyConsumption;
//        totalPowerConsumption += _totalPowerConsumption + idlePowerConsumption;
        totalPowerConsumption += _totalPowerConsumption;

        emit(networkEnergyConsumptionChangedSignal, networkEnergyConsumption.get());

//        EV << "Network Energy consumption=" << _energyConsumption << endl;
//        emit(residualEnergyCapacityChangedSignal, energyBalance.get());
//        std::cout << "WIRELESS POWER res=" << residualCapacity << " ebal="
//                << energyConsumption << " cons=" << totalPowerConsumption
//                << endl;
    }
}

void IdealNodeEnergyStorage::receiveSignal(cComponent *source,
        simsignal_t signal, double value, cObject *details) {
    Enter_Method("receiveSignal");

    if (simTime() >= getSimulation()->getWarmupPeriod()) {
        if(signal == CPUPowerConsumer::cpuPowerConsumptionChangedSignal) {
            updateCPUEnergyBalance(W(value), 0);
        } else if (signal == NetworkPowerConsumer::networkPowerConsumptionChangedSignal) {
            updateWirelessEnergyBalance(W(value));
        }

        J _idleEnergyConsumption = J(s((simTime() - startTime).dbl()) * (W(idlePowerConsumption)));

        emit(idleEnergyConsumptionChangedSignal, _idleEnergyConsumption.get());
        emit(energyConsumptionChangedSignal, totalEnergyConsumption.get());
        emit(energyConsumptionChangedSignal, totalEnergyConsumption.get());
        emit(powerConsumptionChangedSignal, totalPowerConsumption.get());
        emit(residualCapacityChangedSignal, residualCapacity.get());
    }
}

}

