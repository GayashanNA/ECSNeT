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

#ifndef POWER_CONTRACT_IEPENERGYSINK_H
#define POWER_CONTRACT_IEPENERGYSINK_H

#include "inet/power/contract/IEnergySink.h"

using namespace inet;
using namespace inet::power;

namespace ecsnet_ {

/**
 * TODO
 *
 * See the corresponding NED file for more details.
 *
 * @author Levente Meszaros
 */
class IEpEnergySink : public virtual IEnergySink
{
  public:
    /**
     * The signal that is used to publish power generation changes.
     */
    static simsignal_t powerGenerationChangedSignal;

  public:
    /**
     * Returns the total power generation in the range [0, +infinity).
     */
    virtual W getTotalPowerGeneration() const = 0;
};

}

#endif // ifndef __INET_IEPENERGYSINK_H

