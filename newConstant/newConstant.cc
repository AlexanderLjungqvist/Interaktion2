
#include "newConstant.h"

using namespace ikaros;


void
newConstant::Init()
{
//INPUTS
    input_GoalPosition = GetInputArray("GOAL_POSITION");
    input_feedbackPos = GetInputArray("FEEDBACK_POSITION")
//OUTPUTS
    output_GoalPOS = GetOutputArray("GOAL_OUTPUT_POSITION");
}

void
newConstant::Tick()
{}
}
// Install the module. This code is executed during start-up.

static InitClass init("newConstant", &newConstant::Create, "/Users/grupp15/Desktop/Interaktion2/newConstant/");
