
#include "StatisticsHEAD.h"

// use the ikaros namespace to access the math library
// this is preferred to using <cmath>

using namespace ikaros;


void
StatisticsHEAD::Init()
{
//INPUTS
    input_voltage = GetInputArray("FEEDBACK_VOLTAGE");
    input_temperature = GetInputArray("FEEDBACK_TEMP");
    input_ampere = GetInputArray("FEEDBACK_CURRENT");
    input_torque = GetInputArray("FEEDBACK_TORQUE_LIMIT");
    input_GoalPosition = GetInputArray("GOAL_POSITION");
    input_servoPosition = GetInputArray("FEEDBACK_POSITION");
//OUTPUTS
    output_torque = GetOutputArray("TORQUE_LIMIT");

    float energyConsumptionValue = 0;
    float energyConsumptionRightNowValue = 0;


    }

float * almostEqual(float index, float index2){
      float totDiff = abs(index - index2);
        return totDiff;
    }

int * checkServoPositions(float * input_GoalPosition, float * input_servoPosition)
{
   static int returnArray[6];
    for (int i = 0; i < 5; i++)
    if(almostEqual(input_GoalPosition[i],input_servoPosition[i]) > 2)
            returnArray[i] = 1;
    else
        returnArray[i] = 0;

    return(returnArray);
}

void
StatisticsHEAD::energyConsumption(float * input_ampere, float * input_voltage){
  float temp = 0;
  for(int i=0; i<5; i++){
    temp += (input_ampere[i] * input_voltage);
  }
  temp = temp/50;
  energyConsumptionValue += temp;
}

void
StatisticsHEAD::energyConsumptionRightNow(float * input_ampere, float * input_voltage){
  float temp = 0;
  for(int i=0; i<5; i++){
    temp += (input_ampere[i] * input_voltage);
  }
  energyConsumptionPerSecondValue = temp;
}


//Sänker tempot på TORQUEN vid varje klick - Sätter min limit på 0
void
StatisticsHEAD::restingState(int index){
    if(output_torque[index] >= 0.002)

            output_torque[index] = output_torque[index] - 0.002;

}
//Höjet tempot på TORQUEN vid varje klick - Sätter max limit på 1
void
StatisticsHEAD::activeState(int index){
           if(output_torque[index] <= 0.995)
               output_torque[index] = output_torque[index] + 0.005;

}

void
StatisticsHEAD::Tick()
{
  //Räknar ut totala effekten med tid i aspekt.
   energyConsumption(input_ampere, input_voltage);
   printf("%d\n", energyConsumptionValue);

      //Totala effekten ut exakt just nu
     energyConsumptionRightNow(input_ampere, input_voltage);
     printf("%d\n", energyConsumptionRightNowValue);

    int * indexArray = checkServoPositions(input_GoalPosition, input_servoPosition);
    for (int i = 0; i < sizeof(indexArray); i++)
        if(indexArray[i] == 1)
            activeState(i);
   else
            restingState(i);
    print_array("Torque", output_torque, 6);
    print_array("input_GoalPosition", input_GoalPosition, 6);
    print_array("Torinput_servoPositionque", input_servoPosition, 6);
    t++;
}
// Install the module. This code is executed during start-up.

static InitClass init("StatisticsHEAD", &StatisticsHEAD::Create, "/Users/grupp15/Desktop/Interaktion2/Statistics/StatisticsHEAD");
