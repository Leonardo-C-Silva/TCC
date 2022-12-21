/**
  ******************************************************************************
  * @file    vr_sample_control_led.ino
  * @author  JiapengLi
  * @brief   This file provides a demostration on 
              how to control led by using VoiceRecognitionModule
  ******************************************************************************
  * @note:
        voice control led
  ******************************************************************************
  * @section  HISTORY
    
    2013/06/13    Initial version.
  */
  
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
#include <Servo.h>


/**        
  Connection
  Arduino    VoiceRecognitionModule
   3   ------->     TX
   2   ------->     RX
*/
VR myVR(3,2);    // 3:RX 2:TX, you can choose your favourite pins.

Servo servoPolegar;
Servo servoIndicador;
Servo servoMedio;
Servo servoAnelar;
Servo servoMindinho;
Servo servoPulso;

uint8_t records[7]; // save record
uint8_t buf[64];

#define PAZ (0)
#define TESTE (1)
#define TRANQUILO (2)
#define ABRIR (3)
#define FECHAR (4)
#define GIRAR (5)
#define VOLTAR (6) 

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf     --> command length
           len     --> number of parameters
*/
void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized. 
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  /** initialize */
  myVR.begin(9600);
  servoPolegar.attach(4);
  servoIndicador.attach(6);
  servoMedio.attach(5);
  servoAnelar.attach(7);
  servoMindinho.attach(8);
  servoPulso.attach(9);

  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");
  
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  if(myVR.load((uint8_t)PAZ) >= 0){
    Serial.println("paz loaded");
  }
  
  if(myVR.load((uint8_t)TESTE) >= 0){
    Serial.println("teste loaded");
  }
  
  if(myVR.load((uint8_t)TRANQUILO) >= 0){
    Serial.println("tranquilo loaded");
  }
  
  if(myVR.load((uint8_t)ABRIR) >= 0){
    Serial.println("abrir loaded");
  }
  
  if(myVR.load((uint8_t)FECHAR) >= 0){
    Serial.println("fechar loaded");
  }
  
  if(myVR.load((uint8_t)GIRAR) >= 0){
    Serial.println("girar loaded");
  }
  
  if(myVR.load((uint8_t)VOLTAR) >= 0){
    Serial.println("voltar loaded");
  }
  
}

void loop()
{
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){
     case PAZ:
      servoPolegar.write(0);
      servoIndicador.write(180);
      servoMedio.write(180);
      servoAnelar.write(0);
      servoMindinho.write(0);
      servoPulso.write(180);        
      delay (2000);
      servoPulso.write(90);
      delay (2000);
      servoPulso.write(180);
      delay (2000);
      servoPulso.write(90);
      delay (2000);
      servoPolegar.write(0);
      servoIndicador.write(180);
      servoMedio.write(180);
      servoAnelar.write(0);
      servoMindinho.write(0);
      servoPulso.write(180);
     break;
    
     case TESTE:
      servoPolegar.write(180);
      servoIndicador.write(180);
      servoMedio.write(180);
      servoAnelar.write(180);
      servoMindinho.write(180);
      servoPulso.write(180);
      delay(4000);
      servoPolegar.write(0);
      servoIndicador.write(0);
      servoMedio.write(0);
      servoAnelar.write(0);
      servoMindinho.write(0);
      servoPulso.write(90);   
     break;
      
     case TRANQUILO:
      servoPolegar.write(180);
      servoIndicador.write(0);
      servoMedio.write(0);
      servoAnelar.write(0);
      servoMindinho.write(180);
      servoPulso.write(180);
      delay(4000);
      servoPulso.write(90);
      delay (2000);
      servoPulso.write(180);
      delay (2000);
      servoPulso.write(90);
      delay (2000);
      servoIndicador.write(180);
      servoMedio.write(180);
      servoAnelar.write(180);
      servoPulso.write(180);   
     break;
     
     case ABRIR:
      servoPolegar.write(180);
      servoIndicador.write(180);
      servoMedio.write(180);
      servoAnelar.write(180);
      servoMindinho.write(180);   
     break;
     
     case FECHAR:
      servoPolegar.write(0);
      servoIndicador.write(0);
      servoMedio.write(0);
      servoAnelar.write(0);
      servoMindinho.write(0);
     break;
     
     case GIRAR:
      servoPulso.write(90); 
     break;
     
     case VOLTAR:
      servoPulso.write(180);
     break;
     
     default:
      Serial.println("Record function undefined");
     break;
    }
    /** voice recognized */
    printVR(buf);
  }
}
