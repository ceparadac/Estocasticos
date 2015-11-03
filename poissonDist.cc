#include "poissonDist.h"
    #include "ns3/assert.h"
    #include "ns3/boolean.h"
    #include "ns3/double.h"
    #include "ns3/integer.h"
   #include "ns3/string.h"
    #include "ns3/pointer.h"
    #include "ns3/log.h"
    #include "ns3/rng-stream.h"
    #include "ns3/rng-seed-manager.h"
    #include <cmath>
    #include <iostream>
using namespace ns3; 
NS_OBJECT_ENSURE_REGISTERED(PoissonRandomVariable);
   
   TypeId 
   PoissonRandomVariable::GetTypeId (void)
   {
     static TypeId tid = TypeId ("ns3::PoissonRandomVariable")
       .SetParent<RandomVariableStream>()
       .SetGroupName ("Core")
       .AddConstructor<PoissonRandomVariable> ()
       .AddAttribute("Lambda", "Lambda of poisson dist",
             DoubleValue(1),
             MakeDoubleAccessor(&PoissonRandomVariable::lambda),
             MakeDoubleChecker<double>())
       ;
     return tid;
   }
   PoissonRandomVariable::PoissonRandomVariable ()
   {
     
   }
   
   double 
   PoissonRandomVariable::GetLambda (void) const
   {
     return lambda;
   }

   double 
   PoissonRandomVariable::GetValue (double lambda)
   {
	double L = exp(-double(lambda));
    int k = 0;
    double p = 1;
    do {
        k++;
        p *=  Peek ()->RandU01 ();
    } while( p > L);
    

     int v = k-1;
   
     return static_cast<double>(v);
   }
   uint32_t 
   PoissonRandomVariable::GetInteger (uint32_t lambda)
   {
     return static_cast<uint32_t> ( GetValue ((double) (lambda)));
   }
   
   double 
   PoissonRandomVariable::GetValue (void)
   {
     return GetValue (lambda);
   }
   uint32_t 
   PoissonRandomVariable::GetInteger (void)
   {
     return (uint32_t)GetValue (lambda);
   }
