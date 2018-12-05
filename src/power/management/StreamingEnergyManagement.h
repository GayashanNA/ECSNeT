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

#ifndef POWER_MANAGEMENT_STREAMINGENERGYMANAGEMENT_H
#define POWER_MANAGEMENT_STREAMINGENERGYMANAGEMENT_H

#include "inet/common/lifecycle/LifecycleController.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/power/contract/IEpEnergyManagement.h"
#include "../contract/IEpEnergyStorage.h"

using namespace inet;
using namespace inet::power;

namespace ecsnet_ {

class StreamingEnergyManagement : public cSimpleModule, public virtual IEpEnergyManagement, public cListener
{
  protected:
    // parameters
    J nodeShutdownCapacity = J(NaN);
    J nodeStartCapacity = J(NaN);
    IEpEnergyStorage *energyStorage = nullptr;

    // state
    LifecycleController *lifecycleController = nullptr;
    cModule *networkNode = nullptr;
    NodeStatus *nodeStatus = nullptr;
    cMessage *lifecycleOperationTimer = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;

    virtual void executeNodeOperation(J estimatedEnergyCapacity);
    virtual void scheduleLifecycleOperationTimer();

  public:
    virtual ~StreamingEnergyManagement();

    virtual IEnergyStorage *getEnergyStorage() const override { return energyStorage; }
    virtual J getEstimatedEnergyCapacity() const override;

    virtual void receiveSignal(cComponent *source, simsignal_t signal, double value, cObject *details) override;
};

}

#endif // ifndef __INET_SIMPLEEPENERGYMANAGEMENT_H

