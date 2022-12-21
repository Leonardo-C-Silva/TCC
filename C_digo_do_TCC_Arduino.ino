#include <Servo.h>
#include <VoiceRecognitionV3.h>


#define numOfValsRec 6
#define digitsPerValRec 1
Servo servoPolegar;
Servo servoIndicador;
Servo servoMedio;
Servo servoAnelar;
Servo servoMindinho;
Servo servoPulso;

int valsRec [numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1;  //$000000
int counter = 0;
bool counterStart = false;
String receivedString;


void setup() {
Serial.begin(9600);
servoPolegar.attach(4);
servoIndicador.attach(6);
servoMedio.attach(5);
servoAnelar.attach(9);
servoMindinho.attach(8);
servoPulso.attach(8);
}

void receiveData () {
while(Serial.available())
{char c = Serial.read();
if (c=='$'){
counterStart = true;
}
if (counterStart){
if (counter < stringLength){
receivedString = String(receivedString+c);
counter++;
}
if (counter >=stringLength){
//$000000
for(int i = 0; i<numOfValsRec; i++)
{
int num = (i*digitsPerValRec)+1;
valsRec[i] = receivedString.substring(num,num + digitsPerValRec) . toInt();
}
receivedString = "";
counter = 0;
counterStart = false;
}
}
}
}

void loop () {
receiveData();
if (valsRec[0] == 1) {servoPolegar.write(180);}else{servoPolegar.write(0);}
if (valsRec[1] == 1) {servoIndicador.write(180);}else{servoIndicador.write(0);}
if (valsRec[2] == 1) {servoMedio.write(180);}else{servoMedio.write(0);}
if (valsRec[3] == 1) {servoAnelar.write(180);}else{servoAnelar.write(0);}
if (valsRec[4] == 1) {servoMindinho.write(180);}else{servoMindinho.write(0);}
if (valsRec[5] == 1) {servoPulso.write(180);}else{servoPulso.write(90);}
}
