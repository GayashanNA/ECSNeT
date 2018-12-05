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

#ifndef POWER_BASE_EPENERGYSINKBASE_H
#define POWER_BASE_EPENERGYSINKBASE_H

#include "inet/power/base/EnergySinkBase.h"
#include "inet/power/contract/IEpEnergyGenerator.h"
#include "../contract/IEpEnergySink.h"

using namespace inet;
using namespace inet::power;

namespace ecsnet_ {

class EpEnergySinkBase : public EnergySinkBase, public virtual IEpEnergySink, public cListener
{
  protected:
    W totalPowerGeneration = W(NaN);

  protected:
    virtual W computeTotalPowerGeneration() const;
    virtual void updateTotalPowerGeneration();

  public:
    virtual W getTotalPowerGeneration() const override { return totalPowerGeneration; }

    virtual void addEnergyGenerator(const IEnergyGenerator *energyGenerator) override;
    virtual void removeEnergyGenerator(const IEnergyGenerator *energyGenerator) override;
};

}

#endif // ifndef __INET_EPENERGYSINKBASE_H

