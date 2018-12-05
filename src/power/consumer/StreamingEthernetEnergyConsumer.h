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

#ifndef POWER_CONSUMER_STREAMINGETHERNETENERGYCONSUMER_H_
#define POWER_CONSUMER_STREAMINGETHERNETENERGYCONSUMER_H_

#include "inet/power/contract/IEpEnergyConsumer.h"
#include "inet/power/contract/IEpEnergySource.h"
#include "inet/linklayer/ethernet/EtherMACBase.h"

using namespace inet;
using namespace inet::power;

namespace ecsnet_ {

class StreamingEthernetEnergyConsumer: public cSimpleModule, public IEpEnergyConsumer, public cListener  {
protected:
    double cpuPowerConsumptionScalar = NaN;
  // parameters
  W offPowerConsumption = W(NaN);
  W sleepPowerConsumption = W(NaN);
  W switchingPowerConsumption = W(NaN);
  W receiverIdlePowerConsumption = W(NaN);
  W receiverBusyPowerConsumption = W(NaN);
  W receiverReceivingPowerConsumption = W(NaN);
  W transmitterIdlePowerConsumption = W(NaN);
  W transmitterTransmittingPowerConsumption = W(NaN);

  EtherMACBase *MACImpl;
  IEpEnergySource *energySource = nullptr;

  // state
  W powerConsumption = W(NaN);

protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
//    virtual W computePowerConsumption() const;
//    virtual W computeCPUPowerConsumption(double value) const;

public:
    virtual IEnergySource *getEnergySource() const override { return energySource; }
    virtual W getPowerConsumption() const override {return powerConsumption;}

    virtual void receiveSignal(cComponent *source, simsignal_t signal, long value, cObject *details) override;
    virtual void receiveSignal(cComponent *source, simsignal_t signal, double value, cObject *details) override;

};

} /* namespace ecsnet_ */

#endif /* POWER_CONSUMER_STREAMINGETHERNETENERGYCONSUMER_H_ */
