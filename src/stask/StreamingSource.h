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

#ifndef STASK_STREAMINGSOURCE_H_
#define STASK_STREAMINGSOURCE_H_

#include "omnetpp.h"
#include "../msg/StreamingMessage_m.h"
#include "ISTask.h"
#include "../common/SimulationController.h"
#include "../model/source/eventrate/ISourceEventRateDistribution.h"
#include "../model/source/msgsize/IMessageSizeDistribution.h"

using namespace omnetpp;

namespace ecsnet_ {

class StreamingSource: public ISTask {
protected:
    cQueue outgoingQueue;
    cMessage *timerMsg = nullptr;
    double msgSize = 0;
    double eventRate = 0;
    double msgDelay = 0;
    bool isSourceEvRateDistributed = false;
    bool isSourceMsgSizeDistributed = false;
    const char* mySourceEvRateDistributionModuleName;
    const char* mySourceMsgSizeDistributionModuleName;
    SimulationController *commonSimController;
    ISourceEventRateDistribution* mySourceEvRateDistributionModule;
    IMessageSizeDistribution* mySourceMsgSizeDistributionModule;
public:
    virtual ~StreamingSource();
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual double getMessageDelay();
    virtual double getMessageSize();
};

} /* namespace ecsnet_ */

#endif /* STASK_STREAMINGSOURCE_H_ */
