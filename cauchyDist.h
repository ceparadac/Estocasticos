#include "ns3/random-variable-stream.h"

using namespace ns3;

 class CauchyRandomVariable : public RandomVariableStream
   {
   public:
     static TypeId GetTypeId (void);
   
     CauchyRandomVariable ();
   
     double GetAlpha (void) const;

double GetBeta (void) const;

double GetMin (void) const;

double GetMax (void) const;

      double GetValue (double alpha,double beta,double min, double max);
   
     uint32_t GetInteger (double alpha,double beta,double min, double max);

double cummulativeDistributionFunctionCauchy(double alfa, double beta, double x);
double inversecummulativeDistributionFunctionCauchy(double alfa, double beta, double Fx);

   
     // Inherited from RandomVariableStream
     virtual double GetValue (void);
     virtual uint32_t GetInteger (void);
     
   private:
   double alpha;
double beta;
double min;
double max;

 
 }; 
