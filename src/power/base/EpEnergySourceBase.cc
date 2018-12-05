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

#include "EpEnergySourceBase.h"

#include "../consumer/StreamingEnergyConsumer.h"

using namespace inet;
using namespace inet::power;

namespace ecsnet_ {

W EpEnergySourceBase::computeTotalPowerConsumption() const
{
    W totalPowerConsumption = W(0);
    for (auto energyConsumer : energyConsumers)
        totalPowerConsumption += check_and_cast<const IEpEnergyConsumer *>(energyConsumer)->getPowerConsumption();
    return totalPowerConsumption;
}

void EpEnergySourceBase::updateTotalPowerConsumption()
{
    totalPowerConsumption = computeTotalPowerConsumption();
}

void EpEnergySourceBase::addEnergyConsumer(const IEnergyConsumer *energyConsumer)
{
    EnergySourceBase::addEnergyConsumer(energyConsumer);
    auto module = const_cast<cModule *>(check_and_cast<const cModule *>(energyConsumer));
    const char *_clsname =
            "ecsnet_::StreamingEnergyConsumer";
    if (std::strncmp(module->getClassName(), _clsname, strlen(_clsname)) == 0) {
        std::cout << "INSIDE SEC" << endl;
        module->subscribe(
                IEpEnergyConsumer::CPUPowerConsumptionChangedSignal,
                this);
        module->subscribe(
                IEpEnergyConsumer::WirelessPowerConsumptionChangedSignal,
                this);
    } else {
        std::cout << "NOT INSIDE SEC " << module->getClassName() << endl;
        module->subscribe(IEpEnergyConsumer::powerConsumptionChangedSignal,
                this);
    }
    updateTotalPowerConsumption();
}

void EpEnergySourceBase::removeEnergyConsumer(const IEnergyConsumer *energyConsumer)
{
    EnergySourceBase::removeEnergyConsumer(energyConsumer);
    auto module = const_cast<cModule *>(check_and_cast<const cModule *>(energyConsumer));
    const char *_clsname = "ecsnet_::StreamingEnergyConsumer";
    if (std::strncmp(module->getClassName(), _clsname, strlen(_clsname)) == 0) {
        module->unsubscribe(
                IEpEnergyConsumer::CPUPowerConsumptionChangedSignal,
                this);
        module->unsubscribe(
                IEpEnergyConsumer::WirelessPowerConsumptionChangedSignal,
                this);
    } else {
        module->unsubscribe(IEpEnergyConsumer::powerConsumptionChangedSignal,
                this);
    }
    updateTotalPowerConsumption();
}

}

