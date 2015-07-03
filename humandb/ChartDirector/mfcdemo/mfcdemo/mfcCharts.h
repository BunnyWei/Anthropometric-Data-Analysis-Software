#ifndef MFCCHARTS_HDR
#define MFCCHARTS_HDR

//////////////////////////////////////////////////////////////////////////////////
//
//	This demo program contains a number of demo chart functions. Each function 
//	can produce a number of demo charts. We store all the functions and their
//	descriptions into an array to facilitate processing
//
//////////////////////////////////////////////////////////////////////////////////

//  Forward declaration - represents a ChartDirector chart 
class BaseChart;

//	Structure representing a single demo chart function
struct DemoChart
{
	const char *name;	//name of the demo function
	int noOfCharts;		//the number of charts generated by this demo function
	BaseChart* (*createChart)(int chartNo, const char **imageMap);	//the demo function entry point
};

//	An array storing all demo chart functions. An empty entry signals the end 
//	of the array. 
extern DemoChart demoCharts[];


#endif