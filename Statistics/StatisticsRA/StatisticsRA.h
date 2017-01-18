//
//	Kinect     This file is a part of the IKAROS project
//                 A module to grab images from Kinect
//
//    Copyright (C) 2012  Christian Balkenius
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#ifndef StatisticsRA_
#define StatisticsRA_

#include "IKAROS.h"

class StatisticsRA: public Module
{
public:
//INPUTS
    float *         input_temperature;
    float *         input_ampere;
    float *         input_voltage;
    float *         input_torque;
    float *         input_GoalPosition;
    float *         input_servoPosition;

    //OUTPUTS
    float *         output_torque;
    float *         output_mW;
    float *         energyConsumptionValue;

    static Module * Create(Parameter * p) {return new StatisticsRA(p);};

    StatisticsRA(Parameter * p) : Module(p) {};
    virtual ~StatisticsRA() {};

    void    Init();
    void    Tick();

    void    energyConsumption();
    void    restingState(int i);
    void    activeState(int i);
};

#endif
