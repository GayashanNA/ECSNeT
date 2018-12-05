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

#ifndef POWER_STORAGE_NODEENERGYSTORAGE_H_
#define POWER_STORAGE_NODEENERGYSTORAGE_H_

#include "inet/common/lifecycle/LifecycleController.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/power/base/EpEnergyStorageBase.h"

using namespace inet;
using namespace inet::power;

namespace ecsnet_ {

class NodeEnergyStorage : public EpEnergyStorageBase{
protected:
  /**
   * The nominal capacity is in the range [0, +infinity).
   */
  J nominalCapacity = J(NaN);

  /**
   * The residual capacity is in the range [0, nominalCapacity].
   */
  J residualCapacity = J(NaN);

  /**
   * Specifies the amount of capacity change which will be reported.
   */
  J printCapacityStep = J(NaN);

  /**
   * The simulation time when the residual capacity was last updated.
   */
  simtime_t lastResidualCapacityUpdate = -1;

  /**
   * The timer that is scheduled to the earliest time when the energy storage
   * will be depleted, the energy storage will be charged.
   */
  cMessage *timer = nullptr;

  /**
   * The capacity that will be set when the timer expires.
   */
  J targetCapacity = J(NaN);

  /**
   * The lifecycle controller used to shutdown and start the node.
   */
  LifecycleController *lifecycleController = nullptr;

  /**
   * The containing node module.
   */
  cModule *networkNode = nullptr;

  /**
   * The status of the node.
   */
  NodeStatus *nodeStatus = nullptr;

protected:
  virtual void initialize(int stage) override;
  virtual void handleMessage(cMessage *message) override;

  virtual void updateTotalPowerConsumption() override;
  virtual void updateTotalPowerGeneration() override;

  virtual void executeNodeOperation(J newResidualCapacity);
  virtual void setResidualCapacity(J newResidualCapacity);
  virtual void updateResidualCapacity();
  virtual void scheduleTimer();

public:
  virtual ~NodeEnergyStorage();
//  virtual void addEnergyConsumer(const IEnergyConsumer *energyConsumer) override;
//  virtual void receiveSignal(cComponent *source, simsignal_t signal, double value, cObject *details) override;

  virtual J getNominalEnergyCapacity() const override { return nominalCapacity; }
  virtual J getResidualEnergyCapacity() const override;
  virtual void receiveSignal(cComponent *source, simsignal_t signal, double value, cObject *details) override;
};

} /* namespace ecsnet_ */

#endif /* POWER_STORAGE_NODEENERGYSTORAGE_H_ */
