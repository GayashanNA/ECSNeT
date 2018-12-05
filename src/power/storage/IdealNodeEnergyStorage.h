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

#ifndef POWER_STORAGE_IDEALNODEENERGYSTORAGE_H
#define POWER_STORAGE_IDEALNODEENERGYSTORAGE_H

#include "inet/common/Units.h"
#include "inet/common/Units.h"
#include "inet/common/INETMath.h"
#include "omnetpp.h"

using namespace inet;
using namespace inet::math;
using namespace inet::units::values;
using namespace omnetpp;

namespace ecsnet_ {


class IdealNodeEnergyStorage : public cSimpleModule, public cListener
{
  protected:
    /**
     * The nominal capacity is in the range [0, +infinity).
     */
    W idlePowerConsumption = W(0);
    J nominalCapacity = J(NaN);
    long cores = 1;

    /**
     * The residual capacity is in the range [0, nominalCapacity].
     */
    J residualCapacity = J(NaN);
    J energyBalance = J(NaN);
    J cpuEnergyConsumption = J(NAN);
    J networkEnergyConsumption = J(NAN);
    J totalEnergyConsumption = J(0);
    W totalPowerConsumption = W(0);
    W totalIdlePowerConsumption = W(0);
//    J _energyConsumption = J(0);
    cModule *networkNode = nullptr;
    std::map<long, simtime_t> lastCPUEnergyBalanceUpdateMap;
    simtime_t lastCPUEnergyBalanceUpdate = -1;
    simtime_t lastWirelessEnergyBalanceUpdate = -1;
    simtime_t startTime = -1;

  public:
    static simsignal_t energyConsumptionChangedSignal;
    static simsignal_t idleEnergyConsumptionChangedSignal;
    static simsignal_t powerConsumptionChangedSignal;
//    static simsignal_t idlePowerConsumptionChangedSignal;
    static simsignal_t cpuEnergyConsumptionChangedSignal;
    static simsignal_t networkEnergyConsumptionChangedSignal;
    static simsignal_t residualCapacityChangedSignal;

  protected:
    virtual void initialize(int stage) override;

//    virtual void updateTotalPowerConsumption();
//    virtual void updateTotalPowerGeneration();
//    virtual void updateEnergyBalance();
    virtual void updateCPUEnergyBalance(W totalPowerConsumption, long index);
    virtual void updateWirelessEnergyBalance(W totalPowerConsumption);

  public:
    virtual double getNominalEnergyCapacity() const { return double(INFINITY); }
    virtual double getResidualEnergyCapacity() const { return double(INFINITY); }
    virtual void receiveSignal(cComponent *source, simsignal_t signal, double value, cObject *details) override;

};

}

#endif // ifndef __INET_IDEALEPENERGYSTORAGE_H

