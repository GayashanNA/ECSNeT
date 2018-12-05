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

package ecsnet_.power.contract;

import inet.power.contract.IEnergySource;
//
// This interface extends the corresponding energy model interface. It requires
// implementations to describe energy consumption and energy generation with
// power [W] and storage capacity with energy [J]. The Ep is an abbreviation
// that is used for energy and power based interfaces.
//
// @see ~IEpEnergyConsumer, ~IEpEnergyGenerator, ~IEpEnergySink, ~IEpEnergyStorage, ~IEpEnergyManagement
// @author Levente Meszaros
//
moduleinterface IEpEnergySource extends IEnergySource
{
    parameters:
        @display("i=block/plug");
        @signal[powerConsumptionChanged](type=double);
		@signal[CPUPowerConsumptionChanged](type=double);
        @signal[WirelessPowerConsumptionChanged](type=double);
}
