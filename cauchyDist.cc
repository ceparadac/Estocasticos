#include "cauchyDist.h"
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
# define M_PI 3.14159265358979323846  /* pi */
using namespace ns3; 
NS_OBJECT_ENSURE_REGISTERED(CauchyRandomVariable);
   
   TypeId 
   CauchyRandomVariable::GetTypeId (void)
   {
     static TypeId tid = TypeId ("ns3::CauchyRandomVariable")
       .SetParent<RandomVariableStream>()
       .SetGroupName ("Core")
       .AddConstructor<CauchyRandomVariable> ()
       .AddAttribute("alpha", "alpha of cauchy dist",
             DoubleValue(0),
             MakeDoubleAccessor(&CauchyRandomVariable::alpha),
             MakeDoubleChecker<double>())
.AddAttribute("beta", "beta of cauchy dist",
             DoubleValue(1),
             MakeDoubleAccessor(&CauchyRandomVariable::beta),
             MakeDoubleChecker<double>())
.AddAttribute("min", "min value of cauchy dist",
             DoubleValue(-5),
             MakeDoubleAccessor(&CauchyRandomVariable::min),
             MakeDoubleChecker<double>())
.AddAttribute("max", "alpha of cauchy dist",
             DoubleValue(5),
             MakeDoubleAccessor(&CauchyRandomVariable::max),
             MakeDoubleChecker<double>())
       ;
     return tid;
   }
   CauchyRandomVariable::CauchyRandomVariable ()
   {
     
   }
   
   double 
   CauchyRandomVariable::GetAlpha (void) const
   {
     return alpha;
   }

double 
   CauchyRandomVariable::GetBeta (void) const
   {
     return beta;
   }

double 
   CauchyRandomVariable::GetMin (void) const
   {
     return min;
   }

double 
   CauchyRandomVariable::GetMax (void) const
   {
     return max;
   }


double CauchyRandomVariable::inversecummulativeDistributionFunctionCauchy(double alfa, double beta, double Fx) {
        double inverseDistribution = alfa + beta * (tan(M_PI * (Fx - 0.5)));
        return inverseDistribution;

    }
double CauchyRandomVariable::cummulativeDistributionFunctionCauchy(double alfa, double beta, double x) {
        double distribution = ((1 / M_PI) * atan(((x - alfa) / beta))) + (0.5);
        return distribution;
    }


   double 
   CauchyRandomVariable::GetValue (double alpha,double beta,double min, double max)
   {
	double uniformRandom = Peek ()->RandU01 ();
   double aux = ((cummulativeDistributionFunctionCauchy(alpha, beta, max) - cummulativeDistributionFunctionCauchy(alpha, beta, min)) * uniformRandom) + cummulativeDistributionFunctionCauchy(alpha, beta, min);
        double result = inversecummulativeDistributionFunctionCauchy(alpha, beta, aux);
        return abs(result);
   
   }
   uint32_t 
   CauchyRandomVariable::GetInteger (double alpha,double beta,double min, double max)
   {
     return static_cast<uint32_t> ( GetValue (alpha,beta,min,max));
   }
   
   double 
   CauchyRandomVariable::GetValue (void)
   {
     return GetValue (alpha,beta,min,max);
   }
   uint32_t 
   CauchyRandomVariable::GetInteger (void)
   {
     return (uint32_t)GetValue (alpha,beta,min,max);
   }
