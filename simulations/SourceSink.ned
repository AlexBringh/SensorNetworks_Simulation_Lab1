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

package sensornetworks_simulation_lab1.simulations;

import sensornetworks_simulation_lab1.server.Server;
import sensornetworks_simulation_lab1.client.Client;

//
// Sample network, consisting of a source and a sink.
//
network SourceSink
{
	parameters:
		int num = 15;
		
    submodules:
        server: Server;
        client[num]: Client;
        
    connections:
    	for i=0..num-1
    	{
    		client[i].out --> server.in[i];
    	}
}
