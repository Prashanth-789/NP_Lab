#include <fstream>
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main (int argc, char *argv[])
{
  //Address serverAddress;

  NodeContainer nodes;
  nodes.Create (4);
 
  CsmaHelper csma;
   //csma.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  //csma.SetChannelAttribute ("Delay", StringValue ("2ms"));
 csma.SetChannelAttribute ("DataRate", DataRateValue (DataRate (5000000)));
  csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
  csma.SetDeviceAttribute ("Mtu", UintegerValue (1400));
  //mtu->maximun transmission unit 
  NetDeviceContainer device = csma.Install (nodes);
  
   InternetStackHelper stack;
    stack.Install (nodes);
  
  Ipv4AddressHelper address;
      address.SetBase ("10.1.1.0", "255.255.255.0");
      
  Ipv4InterfaceContainer interface = address.Assign (device);
      //serverAddress = Address(i.GetAddress (1));
   
 
  UdpEchoServerHelper server (9);
  ApplicationContainer apps = server.Install (nodes.Get (1));
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (10.0));


  
  UdpEchoClientHelper client (interface.GetAddress(1),9);
  client.SetAttribute ("MaxPackets", UintegerValue (1));
  client.SetAttribute ("Interval", TimeValue (Seconds(1.0)));
  client.SetAttribute ("PacketSize", UintegerValue (1024));

  apps = client.Install (nodes.Get (0));
  apps.Start (Seconds (2.0));
  apps.Stop (Seconds (10.0));


AnimationInterface anim ("second.xml");
  Simulator::Run ();
  Simulator::Destroy ();
  
}
