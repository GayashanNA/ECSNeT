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

//        enum MACTransmitState {
//            TX_IDLE_STATE = 1,
//            WAIT_IFG_STATE,
//            SEND_IFG_STATE,
//            TRANSMITTING_STATE,
//            JAMMING_STATE,
//            BACKOFF_STATE,
//            PAUSE_STATE
//        };
//
//        enum MACReceiveState {
//            RX_IDLE_STATE = 1,
//            RECEIVING_STATE,
//            RX_COLLISION_STATE,
//            RX_RECONNECT_STATE
//        };


simple StreamingEthernetEnergyConsumer extends EpEnergyConsumerBase
{
    parameters:
        double cpuPowerConsumptionScalar = default(0);
        string energySourceModule;
        double offPowerConsumption @unit(W) = default(0mW);
        double sleepPowerConsumption @unit(W) = default(1mW);
        double switchingPowerConsumption @unit(W) = default(1mW);
        double receiverIdlePowerConsumption @unit(W) = default(2mW);
        double receiverBusyPowerConsumption @unit(W) = default(5mW);
        double receiverReceivingPowerConsumption @unit(W) = default(10mW);
        double transmitterIdlePowerConsumption @unit(W) = default(2mW);
        double transmitterTransmittingPowerConsumption @unit(W) = default(100mW);
        @display("i=block/cogwheel");
        @class(StreamingEthernetEnergyConsumer);
}