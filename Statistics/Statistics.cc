
#include "Statistics.h"

// use the ikaros namespace to access the math library
// this is preferred to using <cmath>

using namespace ikaros;


void
Statistics::Init()
{
    //Samlat samtliga outputs viktiga för att kunna se vilka värden som ska och inte ska användas.
    input_voltage = GetInputArray("FEEDBACK_VOLTAGE");
    input_temperature = GetInputArray("FEEDBACK_TEMP");
    input_ampere = GetInputArray("FEEDBACK_CURRENT");
    input_torque = GetInputArray("FEEDBACK_TORQUE_LIMIT");
    input_GoalPosition = GetInputArray("GOAL_POSITION");
    input_servoPosition = GetInputArray("FEEDBACK_POSITION");
    
  //  OUTPUT_servo_id = GetOutputArray("OUTPUT_servo_id");
    output_torque = GetOutputArray("TORQUE_LIMIT");
  //  output_mW = GetOutputArray("mW");


    //FRÅGOR: Är temperaturen i int?
    //Hur kopplar jag samman temp osv för varje servo? SVAR: beror på arrayplats
    // Hur ska jag kunna hantera flera servos samtidigt utan att tråda processen? SVAR: detta görs via att köra tre moduler samtidigt.
    //Hur fungerar indexerandet till servomotorerna när jag inte kan använda mig från ruta 0? SVAR: Hämtar alla i ordning

    }

//Fråga om hur jag vet vilken motor som är ikopplad, borde man ändra värdena här? t.ex ha arrayen från 2-5 SVAR: Det fungerar automatiskt
// Hur kopplar jag temp volt och ampere till en viss motor? SVAR: De är samma struktur på arraysen
void
Statistics::Tick()
{
  //TO DO - Lägga till vinkel för samtliga motorer, se om de har flyttats mycket under en ping, om den inte har det isåfall sänk systemet en del.
  //Om den har rört på sig mycket är det rimligt att inte sänka strömmen.
  //HA en ström från tidigare tick och se om de skiljer, möjligtvis med en push pop lista? där man lagrar värden och om det gått mer än 5 tick
  //sedan mA senast pika kan man börja sänka hastigheten på motorerna.

  //har roboten rört sig mkt sen förra tick? - ström?? - osv
int servoNbr = 0;
int torque_temp;

//Går genom samtliga motorer, mäter upp värdena och om de är över en viss strömnivå går det igång en if-sats som sänker torquen tills det att ström når en
//behaglig nivå igen. Kan i framtiden konfliktera vilket gör att den bara sänker en motor i taget --ATT GÖRA-- se till att sänka temperaturen på flera motorer samtidigt.
// LÖST: Köra flera moduler samtidigt.

    //printar ut alla värden för en servo  - oklart om detta fungerar
    printf("%f\n", input_temperature[servoNbr]);
    printf("%f\n", input_ampere[servoNbr]);
    printf("%f\n", input_voltage[servoNbr]);

    torque_temp = output_torque[servoNbr];
    if(input_ampere[servoNbr] > 300){
      printf("%s\n", "Holy moly time to slow down");
      output_torque[servoNbr] = output_torque[servoNbr] - 0.02;
      printf("%f\n", output_torque[servoNbr]);


        //För att återställa torquen
        if(torque_temp > output_torque[servoNbr]){
          printf("%s\n","Raising back torque to previous value...");
          output_torque[servoNbr] = output_torque[servoNbr] + 0.02;
          printf("%f\n", output_torque[servoNbr]);
        }
      //Detta görs för att starta om loopen och hålla koll på alla servomotorer -
      //ATTGÖRA - lägg till formel så att beroende på motor har man en viss mA som gräns.
      servoNbr ++;
      if(servoNbr == 6){
      servoNbr = 0;
      }
    //  output_mW[0] = output_mW[0] + multiply(input_ampere[servoNbr], input_voltage[servoNbr]);
     // printf("%d\n",output_mW[0]);
    printf("%d\n", servoNbr);

  }

}
// Install the module. This code is executed during start-up.

static InitClass init("Statistics", &Statistics::Create, "/Users/grupp15/Desktop/Interaktion2/Statistics/");
