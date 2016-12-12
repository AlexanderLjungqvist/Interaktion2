
#include "Statistics.h"

// use the ikaros namespace to access the math library
// this is preferred to using <cmath>

using namespace ikaros;


void
Statistics::Init()
{
    //Static value for using different measures in the tick function
   // int t=0;
//INPUTS
    input_voltage = GetInputArray("FEEDBACK_VOLTAGE");
    input_temperature = GetInputArray("FEEDBACK_TEMP");
    input_ampere = GetInputArray("FEEDBACK_CURRENT");
    input_torque = GetInputArray("FEEDBACK_TORQUE_LIMIT");
    input_GoalPosition = GetInputArray("GOAL_POSITION");
    input_servoPosition = GetInputArray("FEEDBACK_POSITION");
//OUTPUTS
    output_torque = GetOutputArray("TORQUE_LIMIT");

    }

int * checkServoPositions(float * input_GoalPosition, float * input_servoPosition)
{
   static int returnArray[6];
    for (int i = 0; i < 5; i++)
        if (input_GoalPosition[i] != input_servoPosition[i])
            returnArray[i] = 1;
    else
        returnArray[i] = 0;
    
    return(returnArray);
}

//Sänker tempot på TORQUEN vid varje klick - Sätter min limit på 0
void
Statistics::restingState(int index){
    if(output_torque[index] >= 0.002)

            output_torque[index] = output_torque[index] - 0.002;
    
}

void
Statistics::activeState(int index){
           if(output_torque[index] <= 0.995)
               output_torque[index] = output_torque[index] + 0.005;
    
}

void almostEqual(){
    
}

void
Statistics::Tick()
{
    int * indexArray = checkServoPositions(input_GoalPosition, input_servoPosition);
    for (int i = 0; i < sizeof(indexArray); i++)
        if(indexArray[i] == 1)
            activeState(i);
   else
    restingState(i);
}
// Install the module. This code is executed during start-up.

static InitClass init("Statistics", &Statistics::Create, "/Users/grupp15/Desktop/Interaktion2/Statistics/");
