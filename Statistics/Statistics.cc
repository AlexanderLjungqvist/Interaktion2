
#include "Statistics.h"

// use the ikaros namespace to access the math library
// this is preferred to using <cmath>

using namespace ikaros;


void
Statistics::Init()
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

    }

void
Statistics::Tick()
{
  //TO-DO sänka samtliga torques ner till så lågt som möjligt - kommer dikteras av resultat från experiment. - ha en metod som gör detta.
  if(CheckServoPositions){
  activeState();
  }
  restingState();
  //
  private bool CheckServoPositions(){
    if (input_servoPosition[0] != input_GoalPosition[0] || input_servoPosition[1] != input_GoalPosition[1] || input_servoPosition[2] != input_GoalPosition[2] || input_servoPosition[3] != input_GoalPosition[3] || input_servoPosition[4] != input_GoalPosition[4] || input_servoPosition[5] != input_GoalPosition[5]){
        return true;
    }

    return false;
  }
  //Sänker tempot på TORQUEN vid varje klick - Sätter min limit på 0
  public void restingState(){
          if(output_torque[0] => 0.001){ output_torque[0] = output_torque[0] - 0.001;}
          if(output_torque[1] => 0.001){ output_torque[1] = output_torque[1] - 0.001;}
          if(output_torque[2] => 0.001){ output_torque[2] = output_torque[2] - 0.001;}
          if(output_torque[3] => 0.001){ output_torque[3] = output_torque[3] - 0.001;}
          if(output_torque[4] => 0.001){ output_torque[4] = output_torque[4] - 0.001;}
          if(output_torque[5] => 0.001){ output_torque[5] = output_torque[5] - 0.001;}
      }
//Höjer tempot på TORQUE - limit satt till 1
  public void activeState(){
          if(output_torque[0] <= 0.995){ output_torque[0] = output_torque[0] + 0.005;}
          if(output_torque[1] <= 0.995){ output_torque[1] = output_torque[1] + 0.005;}
          if(output_torque[2] <= 0.995){ output_torque[2] = output_torque[2] + 0.005;}
          if(output_torque[3] <= 0.995){ output_torque[3] = output_torque[3] + 0.005;}
          if(output_torque[4] <= 0.995){ output_torque[4] = output_torque[4] + 0.005;}
          if(output_torque[5] <= 0.995){ output_torque[5] = output_torque[5] + 0.005;}
      }

//Gjort ett värde för att sänka stora skillnader i ticket.
  public void almostEqual(){

      }
}
// Install the module. This code is executed during start-up.

static InitClass init("Statistics", &Statistics::Create, "/Users/grupp15/Desktop/Interaktion2/Statistics/");
