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

#include "Server.h"

namespace sensornetworks_simulation_lab1 {

Define_Module(Server);

Server::Server() {
    // TODO Auto-generated constructor stub

}

Server::~Server() {
    // TODO Auto-generated destructor stub
}

void Server::initialize()
{
    numberOfClients = par("numberOfClients");

    lastArrival = simTime();
    arrivalsVector.setName("arrivals");
    arrivalsVector.setInterpolationMode(cOutVector::NONE);

    differenceTimeSendReceive.setName("Time differential between send/receive for ONE client");
    differenceTimeSendReceive.setInterpolationMode(cOutVector::NONE);

    differenceTimeSendReceiveOneClient.setName("Time differential between send/receive");
    differenceTimeSendReceiveOneClient.setInterpolationMode(cOutVector::NONE);

    packetsReceivedFromId.setName("Number of packets received by id");
}

void Server::handleMessage(cMessage *msg)
{
    simtime_t d = simTime() - lastArrival;
    simtime_t diff = simTime().dbl() - msg->par("time").doubleValue();

    EV << "From id: " << msg->par("id") << "Received " << msg->getName() << "\t" << msg->par("counter") << "\t time diff send/receive: " << diff << endl;

    /**
     * If the ID of the incoming message matches Client One's ID, check what was the last SimTime for a packet from Client One, and log the time difference between then and now.
     */
    int id = (int) (msg->par("id").doubleValue() - clientIdOffset);
    if (id)
    {
        simtime_t diffClientOne = simTime().dbl() - msg->par("time").doubleValue();
        differenceTimeSendReceiveOneClient.record(diffClientOne);
    }

    /**
     * Log which client sent the message
     */
    packetsReceivedFromId.collect(msg->par("id"));

    arrivalsVector.record(1);
    differenceTimeSendReceive.record(diff);

    lastArrival = simTime();

    delete msg;
}

void Server::finish()
{
    recordStatistic(&packetsReceivedFromId);
}

} /* namespace sensornetworks_simulation_lab1 */
