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

#ifndef POWER_BASE_EPENERGYSTORAGEBASE_H
#define POWER_BASE_EPENERGYSTORAGEBASE_H

#include "EpEnergySinkBase.h"
#include "EpEnergySourceBase.h"
#include "../contract/IEpEnergyStorage.h"

using namespace inet;
using namespace inet::power;

namespace ecsnet_ {

class EpEnergyStorageBase : public cSimpleModule, public EpEnergySourceBase, public EpEnergySinkBase, public virtual IEpEnergyStorage
{
  protected:
    void initialize(int stage) override;

    virtual void updateTotalPowerConsumption() override;
    virtual void updateTotalPowerConsumption(simsignal_t signal);
    virtual void updateTotalPowerGeneration() override;

  public:
    virtual void addEnergyConsumer(const IEnergyConsumer *energyConsumer) override;
    virtual void removeEnergyConsumer(const IEnergyConsumer *energyConsumer) override;

    virtual void addEnergyGenerator(const IEnergyGenerator *energyGenerator) override;
    virtual void removeEnergyGenerator(const IEnergyGenerator *energyGenerator) override;

    virtual void receiveSignal(cComponent *source, simsignal_t signal, double value, cObject *details) override;
};

}

#endif // ifndef __INET_EPENERGYSTORAGEBASE_H

