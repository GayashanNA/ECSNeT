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

#include "EpEnergyStorageBase.h"

#include "../consumer/StreamingEnergyConsumer.h"

using namespace inet;
using namespace inet::power;

namespace ecsnet_ {

void EpEnergyStorageBase::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        totalPowerConsumption = computeTotalPowerConsumption();
        totalPowerGeneration = computeTotalPowerGeneration();
        WATCH(totalPowerConsumption);
        WATCH(totalPowerGeneration);
    }
}

void EpEnergyStorageBase::updateTotalPowerConsumption() {
    EpEnergySourceBase::updateTotalPowerConsumption();
    emit(IEpEnergyConsumer::powerConsumptionChangedSignal,
            totalPowerConsumption.get());
}

void EpEnergyStorageBase::updateTotalPowerConsumption(simsignal_t signal) {
    EpEnergySourceBase::updateTotalPowerConsumption();
    emit(signal, totalPowerConsumption.get());
}

void EpEnergyStorageBase::updateTotalPowerGeneration() {
    EpEnergySinkBase::updateTotalPowerGeneration();
    emit(powerGenerationChangedSignal, totalPowerGeneration.get());
}

void EpEnergyStorageBase::addEnergyConsumer(
        const IEnergyConsumer *energyConsumer) {
    Enter_Method("addEnergyConsumer");
    EpEnergySourceBase::addEnergyConsumer(energyConsumer);
}

void EpEnergyStorageBase::removeEnergyConsumer(
        const IEnergyConsumer *energyConsumer) {
    Enter_Method("removeEnergyConsumer");
    EpEnergySourceBase::removeEnergyConsumer(energyConsumer);
}

void EpEnergyStorageBase::addEnergyGenerator(
        const IEnergyGenerator *energyGenerator) {
    Enter_Method("addEnergyGenerator");
    EpEnergySinkBase::addEnergyGenerator(energyGenerator);
}

void EpEnergyStorageBase::removeEnergyGenerator(
        const IEnergyGenerator *energyGenerator) {
    Enter_Method("removeEnergyGenerator");
    EpEnergySinkBase::removeEnergyGenerator(energyGenerator);
}

void EpEnergyStorageBase::receiveSignal(cComponent *source, simsignal_t signal,
        double value, cObject *details) {
    Enter_Method("receiveSignal");
    if (signal == IEpEnergyConsumer::CPUPowerConsumptionChangedSignal) {
        updateTotalPowerConsumption(IEpEnergySource::CPUPowerConsumptionChangedSignal);
    } else if (signal == IEpEnergyConsumer::WirelessPowerConsumptionChangedSignal) {
        updateTotalPowerConsumption(IEpEnergySource::WirelessPowerConsumptionChangedSignal);
    } else if (signal == IEpEnergyConsumer::powerConsumptionChangedSignal) {
        updateTotalPowerConsumption();
    } else if (signal == IEpEnergyGenerator::powerGenerationChangedSignal) {
        updateTotalPowerGeneration();
    }
}

}

