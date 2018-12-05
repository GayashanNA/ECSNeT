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

#include "StreamingEthernetEnergyConsumer.h"

#include "../../stask/ISTask.h"

namespace ecsnet_ {

Define_Module(StreamingEthernetEnergyConsumer);

void StreamingEthernetEnergyConsumer::initialize(int stage) {
    cSimpleModule::initialize(stage);
    if (stage == inet::INITSTAGE_LOCAL) {
        offPowerConsumption = W(par("offPowerConsumption"));
        sleepPowerConsumption = W(par("sleepPowerConsumption"));
        switchingPowerConsumption = W(par("switchingPowerConsumption"));
        receiverIdlePowerConsumption = W(par("receiverIdlePowerConsumption"));
        receiverBusyPowerConsumption = W(par("receiverBusyPowerConsumption"));
        receiverReceivingPowerConsumption = W(
                par("receiverReceivingPowerConsumption"));
        transmitterIdlePowerConsumption = W(
                par("transmitterIdlePowerConsumption"));
        transmitterTransmittingPowerConsumption = W(
                par("transmitterTransmittingPowerConsumption"));
        cpuPowerConsumptionScalar =
                par("cpuPowerConsumptionScalar").doubleValue();

        cModule* parent = getParentModule();
        std::cout << "TEST1 " << parent->getFullPath() << endl;
        parent->subscribe("receiveState", this);
        parent->subscribe("transmitState", this);

        parent->subscribe(ISTask::cpuUtilisationSignal, this);

        // TODO handle multiple ethernet interfaces
        //EdgeCloud.piAs[0].eth[0].mac
        cModule *module = parent->getSubmodule("eth", 0)->getSubmodule("mac");

        MACImpl = check_and_cast<EtherMACBase *>(module);
        powerConsumption = W(0);
//        energySource = getModuleFromPar<IEpEnergySource>(
//                par("energySourceModule"), this);
//        energySource->addEnergyConsumer(this);
//        WATCH(powerConsumption);

//        std::cout << "ES " << energySource->getNumEnergyConsumers() << endl;
    }
}

void StreamingEthernetEnergyConsumer::receiveSignal(cComponent *source,
        simsignal_t signal, long value, cObject *details) {
    // TODO: use the MAC states to calculate differen power consumptions w.r.t. the states
//    if (signal == IRadio::radioModeChangedSignal
//            || signal == IRadio::receptionStateChangedSignal
//            || signal == IRadio::transmissionStateChangedSignal
//            || signal == IRadio::receivedSignalPartChangedSignal
//            || signal == IRadio::transmittedSignalPartChangedSignal) {
//    if (signal == ) {
//        powerConsumption = computePowerConsumption();
        emit(powerConsumptionChangedSignal, powerConsumption.get());
//    } else
//        throw cRuntimeError("Unknown signal");
}

void StreamingEthernetEnergyConsumer::receiveSignal(cComponent *source,
        simsignal_t signal, double value, cObject *details) {
    if (signal == ISTask::cpuUtilisationSignal) {
//        powerConsumption = computeCPUPowerConsumption(value);
        emit(powerConsumptionChangedSignal, powerConsumption.get());
    } else
        throw cRuntimeError("Unknown signal");
}

} /* namespace ecsnet_ */
