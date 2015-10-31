/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("TallerNS3");

int
main (int argc, char *argv[])
{

        // Create the 4 point to point cable nodes
        NodeContainer cabledNodes;
        cabledNodes.Create(4);

        // Configure the point to point links
        PointToPointHelper pointToPointHelper;
        pointToPointHelper.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
        pointToPointHelper.SetChannelAttribute ("Delay", StringValue ("1ms"));

        //Assing the point to point links to the respective nodes (OSI Layer 1)

        NetDeviceContainer devices;
        devices.Add (pointToPointHelper.Install (cabledNodes.Get (0), cabledNodes.Get (2)));
        devices.Add (pointToPointHelper.Install (cabledNodes.Get (2), cabledNodes.Get (3)));
        devices.Add (pointToPointHelper.Install (cabledNodes.Get (3), cabledNodes.Get (1)));
        devices.Add (pointToPointHelper.Install (cabledNodes.Get (1), cabledNodes.Get (0)));


        //Creating the ip stack for the connection (OSI Layer 3)

        InternetStackHelper ipStack;
        ipStack.Install (cabledNodes);


         // Assing the ip addressed to each cabled node
         NS_LOG_INFO ("Assign ip addresses.");
         Ipv4AddressHelper ip;
         ip.SetBase ("192.168.0.7", "255.255.255.0");
         Ipv4InterfaceContainer addresses = ip.Assign (devices.Get (0));

         Ipv4AddressHelper ip1;
         ip1.SetBase ("192.168.0.8", "255.255.255.0");
         Ipv4InterfaceContainer addresses1 = ip1.Assign (devices.Get (1));

         Ipv4AddressHelper ip2;
         ip2.SetBase ("192.168.0.9", "255.255.255.0");
         Ipv4InterfaceContainer addresses2 = ip2.Assign (devices.Get (2));

         Ipv4AddressHelper ip3;
         ip3.SetBase ("192.168.0.10", "255.255.255.0");
         Ipv4InterfaceContainer addresses3 = ip3.Assign (devices.Get (3));

        Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

        Simulator::Run ();
        Simulator::Destroy ();
        return 0;
}
