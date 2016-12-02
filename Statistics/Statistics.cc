
<<<<<<< HEAD
#include "Statistics.h"

// use the ikaros namespace to access the math library
// this is preferred to using <cmath>

using namespace ikaros;


void
Statistics::Init()
{
    //Samlat samtliga outputs viktiga för att kunna se vilka värden som ska och inte ska användas.
    OUTPUT_servo_id = GetOutputArray("OUTPUT_servo_id");
    output_voltage = GetOutputArray("FEEDBACK_PRESENT_VOLTAGE");
    output_temperature = GetOutputArray("FEEDBACK_PRESENT_TEMPERATURE");
    output_ampere = GetOutputArray("FEEDBACK_PRESENT_CURRENT");
    output_torque = GetInputArray("TORQUE_LIMIT", false);
  //  output_torque = GetOutputArray("FEEDBACK_TORQUE_LIMIT");

  //FRÅGOR: Är temperaturen i int?
    //Hur kopplar jag samman temp osv för varje servo?
    // Hur ska jag kunna hantera flera servos samtidigt utan att tråda processen?
    //Hur fungerar indexerandet till servomotorerna när jag inte kan använda mig från ruta 0? Har gjort en fullösning tills vidare.


    t = 0;

    }

//Fråga om hur jag vet vilken motor som är ikopplad, borde man ändra värdena här? t.ex ha arrayen från 2-5
// Hur kopplar jag temp volt och ampere till en viss motor?
void
Statistics::Tick()
{
int servoNbr = 2;
int torque_temp;

//Går genom samtliga motorer, mäter upp värdena och om de är över en viss temperatur går det igång en while-sats som sänker torquen tills det att temperatur nått en
//behaglig nivå igen. Kan i framtiden konfliktera vilket gör att den bara sänker en motor i taget --ATT GÖRA-- se till att sänka temperaturen på flera motorer samtidigt.
while(servobr < 5){


    //printar ut alla värden för en servo  - oklart om detta fungerar
    printf("%d\n",output_temperature[servoNbr]+ " " +  output_voltage[servoNbr] + " " + output_ampere[servoNbr]);
    torque_temp = output_torque[servoNbr];
    if(output_temperature[servoNbr] > 30){
      printf("%s\n", "Holy moly time to slow down");

        while(output_temperature[servoNbr] > 28){
          printf("Slowing down the torque due to heat..." );
          output_torque[servoNbr] = output_torque[servoNbr] - 0.01;
        }

        prinf("Raising back torque to previous value");
        output_torque[servoNbr] = torque_temp;
    }

      //Detta görs för att starta om loopen och hålla koll på alla servomotorer - ATTGÖRA - lägg till formel så att beroende på motor har man en viss värme som gräns.
      check ++;
      if(check === 5){
      check = 2;
      }

    printf("%d\n", check);
    t++;
  }
}


// Install the module. This code is executed during start-up.

static InitClass init("Statistics", &Statistics::Create, "Source/UserModules/Statistics/");
=======
     	//
     	//    Sum.cc  This file is a part of the IKAROS project
      //    Pointless example module summing its inputs.
     	//
     	//    Copyright (C) 2001-2011 Jan Morén
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
    	// Created: 2001-12-01
    	//
    	// 2003-01-14 and 2007-01-01 Updated for the new simulator

    	#include "Statistics.h"



    	void Statistics::Init()
    	{
    	    size = GetInputSize("INPUT1");
    	    input1  = GetInputArray("INPUT1");
    	    input2  = GetInputArray("INPUT2");
    	    output  = GetOutputArray("OUTPUT");
    	}

    	void Statistics::Tick()
    	{
    	    int i;

    	    // Sum in action. input1 and input2 are pointers to the current input
    	    // vectors and output points to the output vector that will be sent
    	    // along to whatever modules it is connected to.

    	    for(i=0; i<size; i++) {
    	     output[i] = input1[i] + input2[i];
    	    }
    	}

      // Install the module. This code is executed during start-up.

      static InitClass init("Statistics", &Statistics::Create, "Source/UserModules/Statistics/");
<<<<<<< Updated upstream
=======
>>>>>>> origin/master
>>>>>>> Stashed changes
