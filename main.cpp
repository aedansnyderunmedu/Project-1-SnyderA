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
//================================================

const double DT = 1e-10; //delta T. timesteps need to be smaller than circuit's time constant for Euler's method to work. I haven't taken circuits, but that's what the internet says. 
const double end_T = 5e-6; //final time, 5 microseconds
const int nSteps = 50000; //steps between 0 and end_T. useful later as our loop counter. init values are index 0, with 50k steps on top. 
const double R = 1e3; //1000 ohms of resistance
const double iuF = 100e-12; //capacitance given by rubric.
const double I = 1e-2; //.01 amps output
const double vOut = 10.0; //output voltage
//
//================================================

int main()
{
	Cap cc; //constant current circuit//
	cc.uF = iuF; //capacitance in cc Cap struct set to given value
	cc.time = new double[nSteps + 1]; //plus 1 offset for index 1 through 50k, accounts for init values stored at 0.
	cc.volt = new double[nSteps + 1];
	cc.curr = new double[nSteps + 1];
	
	Cap rc; //constant voltage circuit//
	rc.uF = iuF;
	rc.time = new double[nSteps + 1];
	rc.volt = new double[nSteps + 1];
	rc.curr = new double[nSteps + 1];

	//initial conditions
	cc.time[0] = 0.0;
	cc.volt[0] = 0.0;
	cc.curr[0] = I;

	rc.time[0] = 0.0;
	rc.volt[0] = 0.0;
	rc.curr[0] = vOut/R; //voltage divided by resistance = current. Ohm's law. 
	
	//cc time loop. for BOTH we use i - 1 to calculate loop index (i) from the previous values (i - 1). 
	for(int i = 1; i <= nSteps; i++)
	{
		cc.time[i] = i * DT; //basically a timestep check, stores what's happening at each step
		cc.curr[i] = I;
		cc.volt[i] = cc.volt[i - 1] + cc.curr[i - 1] * DT / cc.uF; //same equation in the rubric but shifted by 1 with i - 1. as current decreases, voltage grows less and less until about 10v. 
	}
	//rc time loop
	for(int i = 1; i <=nSteps; i++)
	{
		rc.time[i] = i * DT;
		rc.curr[i] = rc.curr[i - 1] - rc.curr[i - 1] * DT / (R * rc.uF); //exponential decay of current. new current is previous value minus a percentage of that value. as current approaches 0, it does so more and more slowly. 
		rc.volt[i] = rc.volt[i - 1] + rc.curr[i - 1] * DT / rc.uF;
	}
	
	//print loops
	for(int i = 0; i <= nSteps; i+= 200)//intervals of 200 timesteps!!
	{
		cout << scientific << setprecision(4) << "[" << cc.time[i] << "]" << "[" << cc.volt[i] << "]" << "[" << cc.curr[i] << "]" << "\n";//scientific and setprecsiion alter dataflow before printing to screen
	}
	
	for(int i = 0; i <=nSteps; i+= 200)
	{
		cout << scientific << setprecision(4) << "[" << rc.time[i] << "]" << "[" << rc.volt[i] << "]" << "[" << rc.curr[i] << "]" << "\n";//same as above
	}

	//frees
	delete[] cc.time;
	delete[] cc.volt;
	delete[] cc.curr;

	delete[] rc.time;
	delete[] rc.volt;
	delete[] rc.curr;

	return 0;
}








