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

import ecsnet_.power.contract.IEpEnergyStorage;

//
// This is an abstract base module for power based energy storage models.
// It defines shared signals and statistics.
//
// @see ~EpEnergyConsumerBase, ~EpEnergySourceBase, ~EpEnergyGeneratorBase, ~EpEnergySinkBase  
// @author Levente Meszaros
//
simple EpEnergyStorageBase like IEpEnergyStorage
{
    parameters:
        @display("i=block/plug");
        @class(EpEnergyStorageBase);
        @signal[powerConsumptionChanged];
		@signal[CPUPowerConsumptionChanged];
        @signal[WirelessPowerConsumptionChanged];
        @signal[powerGenerationChanged];
        @signal[residualEnergyCapacityChanged];
//		@statistic[powerConsumption](title="Power consumption"; source=CPUPowerConsumptionChanged; record=vector; interpolationmode=sample-hold);
//        @statistic[powerConsumption](title="Power consumption"; source=WirelessPowerConsumptionChanged; record=vector; interpolationmode=sample-hold);
        @statistic[CPUPowerConsumption](title="CPU Power consumption"; source=CPUPowerConsumptionChanged; record=vector; interpolationmode=sample-hold);
        @statistic[WirelessPowerConsumption](title="Wireless Power consumption"; source=WirelessPowerConsumptionChanged; record=vector; interpolationmode=sample-hold);
        @statistic[powerGeneration](title="Power generation"; source=powerGenerationChanged; record=vector; interpolationmode=sample-hold);
        @statistic[residualEnergyCapacity](title="Residual energy capacity"; source=residualEnergyCapacityChanged; record=vector; interpolationmode=linear);
}
