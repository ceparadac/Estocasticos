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


#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/olsr-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/mobility-module.h"
#include "myapp.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("TallerNS3");

int
main (int argc, char *argv[])
{
//Defining constant phymode
std::string phyMode ("DsssRate1Mbps");

Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

        // Create the 4 point to point cable nodes
        NodeContainer cabledNodes;
        cabledNodes.Create(4);

        // Configure the point to point links
        PointToPointHelper pointToPointHelper;
        pointToPointHelper.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
        pointToPointHelper.SetChannelAttribute ("Delay", StringValue ("1ms"));

        //Assing the point to point links to the respective nodes (OSI Layer 1)

        NetDeviceContainer cableDevices;
        cableDevices.Add (pointToPointHelper.Install (cabledNodes.Get (0), cabledNodes.Get (2)));
        cableDevices.Add (pointToPointHelper.Install (cabledNodes.Get (2), cabledNodes.Get (3)));
        cableDevices.Add (pointToPointHelper.Install (cabledNodes.Get (3), cabledNodes.Get (1)));
        cableDevices.Add (pointToPointHelper.Install (cabledNodes.Get (1), cabledNodes.Get (0)));


        // Create the 6 wireless nodes
        NodeContainer wirelessNodes;
        wirelessNodes.Create(6);

        // Creating the WIFI Helper
        WifiHelper wifi;

        //Configuring the helper for 802.11 Protocol
          YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();
          wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11);

          YansWifiChannelHelper wifiChannel ;
          wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
          wifiChannel.AddPropagationLoss ("ns3::TwoRayGroundPropagationLossModel",
	          	  	  	  	  	  	  	    "SystemLoss", DoubleValue(1),
		          	  	  	  	  	  	    "HeightAboveZ", DoubleValue(1.5));

          // Configuring the phisical values related to the Transmission Antenna Power, Gain etc
          wifiPhy.Set ("TxPowerStart", DoubleValue(33));
          wifiPhy.Set ("TxPowerEnd", DoubleValue(33));
          wifiPhy.Set ("TxPowerLevels", UintegerValue(1));
          wifiPhy.Set ("TxGain", DoubleValue(0));
          wifiPhy.Set ("RxGain", DoubleValue(0));
          wifiPhy.Set ("EnergyDetectionThreshold", DoubleValue(-61.8));
          wifiPhy.Set ("CcaMode1Threshold", DoubleValue(-64.8));

           //Configuring the working channel of the wifi interface
          wifiPhy.SetChannel (wifiChannel.Create ());

          // Add a non-QoS upper mac
          NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
          wifiMac.SetType ("ns3::AdhocWifiMac");

          // Set 802.11b standard
          wifi.SetStandard (WIFI_PHY_STANDARD_80211b);

          wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                        "DataMode",StringValue(phyMode),
                                        "ControlMode",StringValue(phyMode));

          //Creating the configured interfaces on the wireless nodes (OSI Layer 1)
          NetDeviceContainer wirelessDevices;
          wirelessDevices = wifi.Install (wifiPhy, wifiMac, wirelessNodes);


        //Installing ipStack for cabled and wireless nodes
        InternetStackHelper ipStack;
        ipStack.Install (cabledNodes);
        ipStack.Install (wirelessNodes);


         // Assing the ip addressed to all nodes
         NS_LOG_INFO ("Assign ip addresses.");
         Ipv4AddressHelper ip;
         ip.SetBase ("192.168.0.0", "255.255.255.0");

        Ipv4InterfaceContainer addresses = ip.Assign (wirelessDevices.Get (0));
         Ipv4InterfaceContainer addresses1 = ip.Assign (wirelessDevices.Get (1));
         Ipv4InterfaceContainer addresses2 = ip.Assign (wirelessDevices.Get (2));
         Ipv4InterfaceContainer addresses3 = ip.Assign (wirelessDevices.Get (3));  
         Ipv4InterfaceContainer addresses4 = ip.Assign (wirelessDevices.Get (4));  
         Ipv4InterfaceContainer addresses5 = ip.Assign (wirelessDevices.Get (5));  


         Ipv4InterfaceContainer addresses6 = ip.Assign (cableDevices.Get (0));
         Ipv4InterfaceContainer addresses7 = ip.Assign (cableDevices.Get (1));
         Ipv4InterfaceContainer addresses8 = ip.Assign (cableDevices.Get (2));
         Ipv4InterfaceContainer addresses9 = ip.Assign (cableDevices.Get (3));

  

        Ipv4GlobalRoutingHelper::PopulateRoutingTables ();


//Configuring the position of the wireless nodes and their mobility
  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject <ListPositionAllocator>();
  positionAlloc ->Add(Vector(0, 0, 0)); // node0
  positionAlloc ->Add(Vector(150, 0, 0)); // node1 -- starting very far away
  positionAlloc ->Add(Vector(0, 150, 0)); // node2
  positionAlloc ->Add(Vector(0, 0, 150)); 
  positionAlloc ->Add(Vector(200, 0, 0)); 
  positionAlloc ->Add(Vector(0, 200, 0)); 
  mobility.SetPositionAllocator(positionAlloc);
  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.Install(wirelessNodes);


   


        Simulator::Run ();
        Simulator::Destroy ();
        return 0;
}
