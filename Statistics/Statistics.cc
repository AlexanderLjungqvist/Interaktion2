
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
