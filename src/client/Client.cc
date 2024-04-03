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

#include "Client.h"

namespace sensornetworks_simulation_lab1 {

Define_Module(Client);

Client::Client()
{
    timerMessage = NULL;
}

Client::~Client()
{
    cancelAndDelete(timerMessage);
}

void Client::initialize()
{
    counter = 0;
    id = getId();
    timerMessage = new cMessage("timer");
    scheduleAt(simTime(), timerMessage);
}

void Client::handleMessage(cMessage *msg)
{
    ASSERT(msg == timerMessage);

    cMessage *job = new cMessage("job");

    job->addPar("counter");
    job->par("counter") = counter;
    counter++;

    job->addPar("time");
    job->par("time") = simTime().dbl();

    job->addPar("id");
    job->par("id") = id;

    send(job, "out");

    scheduleAt(simTime()+par("sendInterval").doubleValue(), timerMessage);
}

} /* namespace sensornetworks_simulation_lab1 */
