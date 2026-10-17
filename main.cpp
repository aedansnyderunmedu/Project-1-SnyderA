#include <iostream> //input-output stream
#include <iomanip> //same as last assignment, things like setprecision, scientific
using namespace std; //for executing cout and other std:: functions without std::

struct _capacitor //every simulated cap lives in a separate _capacitor
{
	double *time; //pointer to double
	double *volt;
	double *curr;
	double uF; //one value, capacitance
};
typedef struct _capacitor Cap; //typedef shorthand


