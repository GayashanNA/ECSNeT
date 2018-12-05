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
import inet.node.inet.StandardHost;
import inet.node.inet.WirelessHost;
import inet.node.inet.NodeBase;
import ecsnet_.power.consumer.StreamingEthernetEnergyConsumer;

module RaspberryPiModelA extends StandardHost
{
    parameters:
        int cores = 1;
        double perCoreFreq @unit(Hz) = 700000Hz;
        double totalMemory @unit(Mb) = 512Mb;
        bool hasAcker = default(false);
        string ackerAddress = default("");
        @display("bgb=728.91003,656.82");
    gates:
        inout hostport[];
    submodules:
        supervisor: StreamingSupervisor;
        acker: Acker if hasAcker;
//        energyconsumer: StreamingEthernetEnergyConsumer;
    connections allowunconnected:
        supervisor.udpIn <-- udp.appOut++;
        supervisor.udpOut --> udp.appIn++;
        // connect supervisor to acker 
        // only if the acker is placed in this node
        supervisor.ackerOut++ --> acker.ackerIn if hasAcker;
}
