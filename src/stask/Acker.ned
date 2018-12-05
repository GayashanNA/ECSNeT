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

package ecsnet_.stask;

simple Acker
{
    parameters:
        string name = default("Acker");

        @signal[rcvdAck](type=cPacket);
//        @statistic[rcvdAck](title="packets received"; source=rcvdAck; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
//        @statistic[throughput](title="throughput"; unit=bps; source="throughput(rcvdAck)"; record=vector);
//        @statistic[endToEndDelay](title="end-to-end delay"; source="messageAge(rcvdAck)"; unit=s; record=histogram,vector; interpolationmode=none);
//        @statistic[rcvdAckSeqNo](title="received packet sequence number"; source="appPkSeqNo(rcvdAck)"; record=vector; interpolationmode=none);
    gates:
        input ackerIn;
}