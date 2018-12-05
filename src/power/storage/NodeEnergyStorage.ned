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

import ecsnet_.power.base.EpEnergyStorageBase;

simple NodeEnergyStorage extends EpEnergyStorageBase
{
    parameters:
        double nominalCapacity @unit(J); // the maximum amount of energy stored
        double initialCapacity @unit(J) = default(nominalCapacity); // the initially stored amount of energy
        double printCapacityStep @unit(J) = default(0.01 * nominalCapacity); // displays residual capacity changes in the log
        @class(NodeEnergyStorage);
}
