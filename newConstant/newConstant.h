#ifndef newConstant_
#define newConstant_

#include "IKAROS.h"

class newConstant: public Module
{
public:
//INPUTS
    float *         input_GoalPosition;
    float *         input_feedbackPos;

    //OUTPUTS
    float *         output_GoalPOS;


    static Module * Create(Parameter * p) {return new newConstant(p);};

    newConstant(Parameter * p) : Module(p) {};
    virtual ~newConstant() {};

    void    Init();
    void    Tick();
};

#endif
