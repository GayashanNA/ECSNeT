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

package ecsnet_.power.consumer;

import inet.power.base.EpEnergyConsumerBase;
//import inet.physicallayer.energyconsumer.StateBasedEpEnergyConsumer;

simple CPUEpEnergyConsumer extends EpEnergyConsumerBase
{
    parameters:
        string energySourceModule;
        double cpuPowerConsumptionScalar = default(0);
        double cpuBusyUtilisation = default(1);
        double cpuIdleUtilisation = default(0);
        double idlePowerConsumption @unit(W) = default(0mW);
		@display("i=block/cogwheel");
        @class(CPUEpEnergyConsumer);
}
