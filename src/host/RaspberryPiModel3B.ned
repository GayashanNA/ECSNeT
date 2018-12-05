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

package ecsnet_.host;
import ecsnet_.stask.ISTask;
import ecsnet_.stask.StreamingSupervisor;
import ecsnet_.stask.Acker;
import ecsnet_.cpu.CPUCore;
import inet.node.inet.StandardHost;
import inet.node.inet.AdhocHost;
import inet.node.inet.WirelessHost;
import inet.node.inet.NodeBase;
import inet.power.contract.IEnergyConsumer;
import ecsnet_.power.consumer.CPUPowerConsumer;
import ecsnet_.power.consumer.NetworkPowerConsumer;
import ecsnet_.power.storage.IdealNodeEnergyStorage;
import inet.power.contract.IEpEnergyConsumer;

module RaspberryPiModel3B extends WirelessHost
{
    parameters:
        int cores = default(4);
        double perCoreFreq @unit(Hz) = 1200000000Hz;
        int threadsPerCore = 1;
        double totalMemory @unit(Mb) = 1024Mb;
        double fixedSourceEventRate = default(0);
        bool hasAcker = default(false);
        string ackerAddress = default("");
		string energyConsumerType = default(""); // NED type of the energy consumer model
//        string cpuPowerConsumerType = default("CPUPowerConsumer");
//        string networkPowerConsumerType = default("NetworkPowerConsumer");
//        string energyStoreType = default("IdealNodeEnergyStorage");
        @display("bgb=728.91003,656.82");
        @statistic[residualEnergyConsumption](title="Residual energy consumption"; source=residualEnergyCapacityChanged; record=last);
        @statistic[processingLatency](title="processingLatency"; source=processingTime; record=vector);
        @statistic[transmissionLatency](title="Transmission Latency"; source=transmissionTime; record=vector);
        @statistic[totalLatency](title="Total Latency"; source=latency; record=vector);
    gates:
        inout hostport[];
    submodules:
        cpuCore[cores]: CPUCore {
            @display("p=674.52,39.6,c");
        }
        supervisor: StreamingSupervisor;
        acker: Acker if hasAcker;
//        cpuPowerConsumer: <energyConsumerType> like IEpEnergyConsumer if energyConsumerType != "";
        cpuPowerConsumer: CPUPowerConsumer;
        networkPowerConsumer: NetworkPowerConsumer;
        energyStore: IdealNodeEnergyStorage;
    connections allowunconnected:
        supervisor.udpIn <-- udp.appOut++ if hasUdp;
        supervisor.udpOut --> udp.appIn++ if hasUdp;
        supervisor.tcpIn <-- tcp.appOut++ if hasTcp;
        supervisor.tcpOut --> tcp.appIn++ if hasTcp;
        // connect supervisor to acker 
        // only if the acker is placed in this node
        supervisor.ackerOut++ --> acker.ackerIn if hasAcker;
}
