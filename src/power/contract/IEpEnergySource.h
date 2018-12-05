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

#ifndef POWER_CONTRACT_IEPENERGYSOURCE_H
#define POWER_CONTRACT_IEPENERGYSOURCE_H

#include "inet/power/contract/IEnergySource.h"

using namespace inet;
using namespace inet::power;

namespace ecsnet_ {

/**
 * This class is an interface that should be implemented by power based energy
 * source models to integrate with other parts of the power based model. Such
 * an energy source model describes its total energy consumption in terms of
 * power consumption
 *
 * See the corresponding NED file for more details.
 *
 * @author Levente Meszaros
 */
class IEpEnergySource : public virtual IEnergySource
{
  public:
    /**
     * The signal that is used to publish power consumption changes.
     */
    static simsignal_t powerConsumptionChangedSignal;
    static simsignal_t CPUPowerConsumptionChangedSignal;
    static simsignal_t WirelessPowerConsumptionChangedSignal;

  public:
    /**
     * Returns the total power consumption in the range [0, +infinity).
     */
    virtual W getTotalPowerConsumption() const = 0;
};

}

#endif // ifndef __INET_IEPENERGYSOURCE_H

