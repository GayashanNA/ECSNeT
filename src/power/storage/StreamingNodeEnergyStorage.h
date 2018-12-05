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

#ifndef POWER_STORAGE_STREAMINGNODEENERGYSTORAGE_H_
#define POWER_STORAGE_STREAMINGNODEENERGYSTORAGE_H_

#include "inet/common/Units.h"
#include "inet/common/INETMath.h"
#include "omnetpp.h"

using namespace inet;
using namespace inet::math;
using namespace inet::units::values;
using namespace omnetpp;

namespace ecsnet_ {

class StreamingNodeEnergyStorage : public cSimpleModule, public cListener {
protected:
  /**
   * The nominal capacity is in the range [0, +infinity).
   */
  J nominalCapacity = J(NaN);
  W totalPowerConsumption = W(NaN);
  /**
   * The residual capacity is in the range [0, nominalCapacity].
   */
  J residualCapacity = J(NaN);
  J energyBalance = J(NaN);
  cModule *networkNode = nullptr;
  simtime_t lastCPUEnergyBalanceUpdate = -1;
  simtime_t lastWirelessEnergyBalanceUpdate = -1;

public:
  static simsignal_t residualEnergyCapacityChangedSignal;

public:
    virtual J getNominalEnergyCapacity() const { return J(nominalCapacity); }
    virtual J getResidualEnergyCapacity() const { return J(residualCapacity); }
    virtual void receiveSignal(cComponent *source, simsignal_t signal, double value, cObject *details) override;

protected:
    virtual void updateCPUEnergyBalance();
    virtual void updateWirelessEnergyBalance();
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

} /* namespace ecsnet_ */

#endif /* POWER_STORAGE_STREAMINGNODEENERGYSTORAGE_H_ */
