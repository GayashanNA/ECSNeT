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

package ecsnet_.power.base;

import ecsnet_.power.contract.IEpEnergySource;

//
// This is an abstract base module for power based energy source models.
// It defines shared signals and statistics.
//
// @see ~EpEnergyConsumerBase, ~EpEnergyGeneratorBase, ~EpEnergySinkBase, ~EpEnergyStorageBase  
// @author Levente Meszaros
//
simple EpEnergySourceBase like IEpEnergySource
{
    parameters:
        @display("i=block/plug");
        @signal[powerConsumptionChanged];
		@signal[CPUPowerConsumptionChanged];
        @signal[WirelessPowerConsumptionChanged];
//        @statistic[powerConsumption](title="Power consumption"; source=CPUPowerConsumptionChanged; record=vector; interpolationmode=sample-hold);
//        @statistic[powerConsumption](title="Power consumption"; source=WirelessPowerConsumptionChanged; record=vector; interpolationmode=sample-hold);
        @statistic[CPUPowerConsumption](title="CPU Power consumption"; source=CPUPowerConsumptionChanged; record=vector; interpolationmode=sample-hold);
        @statistic[WirelessPowerConsumption](title="Wireless Power consumption"; source=WirelessPowerConsumptionChanged; record=vector; interpolationmode=sample-hold);
}
