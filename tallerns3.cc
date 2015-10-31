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

        //Assing the point to point links to the respective nodes

        NetDeviceContainer devices;
        devices.Add (pointToPointHelper.Install (cabledNodes.Get (0), cabledNodes.Get (2)));
        devices.Add (pointToPointHelper.Install (cabledNodes.Get (2), cabledNodes.Get (3)));
        devices.Add (pointToPointHelper.Install (cabledNodes.Get (3), cabledNodes.Get (1)));
        devices.Add (pointToPointHelper.Install (cabledNodes.Get (1), cabledNodes.Get (0)));

        Simulator::Run ();
        Simulator::Destroy ();
        return 0;
}
