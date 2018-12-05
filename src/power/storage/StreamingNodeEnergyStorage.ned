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

package ecsnet_.power.storage;

simple StreamingNodeEnergyStorage
{
    parameters:
        double nominalCapacity @unit(J); // the maximum amount of energy stored
        double initialCapacity @unit(J) = default(nominalCapacity); // the initially stored amount of energy
        		@signal[CPUPowerConsumptionChanged];
//        @signal[WirelessPowerConsumptionChanged];
//        @signal[powerGenerationChanged];
//        @signal[name](type="type");
        @signal[residualEnergyCapacity](type=double);
//        @statistic[CPUPowerConsumption](title="CPU Power consumption"; source=CPUPowerConsumptionChanged; record=vector; interpolationmode=sample-hold);
//        @statistic[WirelessPowerConsumption](title="Wireless Power consumption"; source=WirelessPowerConsumptionChanged; record=vector; interpolationmode=sample-hold);
//        @statistic[powerGeneration](title="Power generation"; source=powerGenerationChanged; record=vector; interpolationmode=sample-hold);
        @statistic[residualEnergyCapacity](title="Residual energy capacity"; source=residualEnergyCapacity; record=vector; interpolationmode=linear);
        @class(StreamingNodeEnergyStorage);
}