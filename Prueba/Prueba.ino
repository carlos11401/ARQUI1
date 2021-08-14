#include <MatrizLed.h>
#include "simbolos.h"
// where we'll change the mode to show the text
#define MOD1 23
#define MOD2 25
#define MODTEXT 27
// for the rate
int input;
int list[7] = {2,3,4,5,6,7,8};
boolean one[7] = {false,false,false,false,true,true,false};
boolean two[7] = {true,false,true,true,false,true,true};
boolean three[7] = {true,false,false,true,true,true,true};
boolean four[7] = {true,true,false,false,true,true,false};
boolean five[7] = {true,true,false,true,true,false,true};
// init library
MatrizLed screen;

void setup() {
  
 
  
  
  
  pinMode(MOD1,INPUT);
  pinMode(MOD2,INPUT);
  screen.begin(13,11,12,2);
  screen.rotar(false);
  Serial1.begin(9600);
  // init displays

   
  for(int i=0;i<8;i++){
    pinMode(list[i],OUTPUT);
    digitalWrite(list[i],LOW);
  }
}
char text[] = "*P1-GRUPO#2-SECCION_A";
int textDelay = 10;
String dynamicText;
int counter = 0;
int contador=0;

void loop() {
  
  
  // -------------------- READ TEXT -----------------------------
  if(Serial1.available()>0 and digitalRead(MODTEXT) == 1){
    counter++;
    char val = Serial1.read();
    if(counter == 1){ // to delete some text that have dynamicText
      dynamicText = "";
    }
    if(val == 13){
      Serial1.print(dynamicText);
      memset(text,"",sizeof(text));
      for(int i=0; i<dynamicText.length(); i++){
        text[i] = dynamicText[i];
      }
      dynamicText = "";
      counter = 0;
      
    }else{
      dynamicText = dynamicText + val;
      Serial1.print(dynamicText);
    }    
  }else if(digitalRead(MODTEXT) == 0){
    //memset(text,"",sizeof(text));
    dynamicText = "*P1-GRUPO#2-SECCION_A";
    for(int i=0; i<dynamicText.length(); i++){
        text[i] = dynamicText[i];
      }
  }
  // -------------------- rate -----------------------------
  verifyRate();
  // -------------------- MODE 1 -----------------------------
  if(digitalRead(MOD1) == 1){
     // Escribir texto estatico
    screen.borrar();
    if(contador==sizeof(text)-1){
      contador=0;
    }
    switch (text[contador]){
      case '*':
        for(int i=0; i<8; i++){
          screen.setRow(0, i, Asterisco[i]);
        }
        delay(textDelay*5);
        break;
      case '-':
        for(int i=0; i<8; i++){
          screen.setRow(0, i, Guion[i]);
          }
        delay(textDelay*5);
        break;
      case '_':
        for(int i=0; i<8; i++){
          screen.setRow(0, i, GuionB[i]);
          }
        delay(textDelay*5);
        break;
      case '#':
        for(int i=0; i<8; i++){
          screen.setRow(0, i, Numeral[i]);
        }
        delay(textDelay*5);
        break;
      default:
        screen.escribirCaracter(text[contador] , 0); // Caracter, posicion en la pantalla
        delay(textDelay*5);
        break;
        }
      contador++;

  }
  // -------------------- MODE 2 -----------------------------
  if(digitalRead(MOD2) == 1 and MOD1 != 1){
    // Desplazar texto manualmente hacia la derecha
    screen.borrar();  
    int temp1=0;
    for (int i=0; i < sizeof(text)*8; i++){
         
        
        for(int j=0; j<sizeof(text);j++){
          
            if(text[j]=='*'){
              for(int k=0; k<8; k++){
                if(i-(8*(j+1))<=8 ){
                    screen.setRow(0,i-(8*(j+1)-k), Asterisco[k]);
                }
                if(i>=j*8){
                 screen.setRow(1, i-(8*(j+1)-k)-8, Asterisco[k]);

                }
                else if(i>=(j*16)){
                     screen.setRow(1, i-(8*(j+1)-k), Asterisco[k]);
                }
              }
              delay(textDelay-(textDelay*0.8));
            }
            else if(text[j]=='-'){   
              for(int k=0; k<8; k++){
                if(i-(8*(j+1))<=8 ){
                    screen.setRow(0,i-(8*(j+1)-k), Guion[k]);
                }
                if(i>=j*8){
                 screen.setRow(1, i-(8*(j+1)-k)-8, Guion[k]);

                }
                else if(i>=(j*16)){
                     screen.setRow(1, i-(8*(j+1)-k), Guion[k]);
                }
              }
              delay(textDelay-(textDelay*0.8));
            }else if(text[j]=='_'){
              for(int k=0; k<8; k++){
                if(i-(8*(j+1))<=8 ){
                    screen.setRow(0,i-(8*(j+1)-k), GuionB[k]);
                }
                if(i>=j*8){
                 screen.setRow(1, i-(8*(j+1)-k)-8, GuionB[k]);

                }
                else if(i>=(j*16)){
                     screen.setRow(1, i-(8*(j+1)-k), GuionB[k]);
                }
              }
              delay(textDelay-(textDelay*0.8));
            }else if(text[j]=='#'){
              for(int k=0; k<8; k++){
                if(i-(8*(j+1))<=8 ){
                    screen.setRow(0,i-(8*(j+1)-k), Numeral[k]);
                }
                if(i>=j*8){
                 screen.setRow(1, i-(8*(j+1)-k)-8, Numeral[k]);

                }
                else if(i>=(j*16)){
                     screen.setRow(1, i-(8*(j+1)-k), Numeral[k]);
                }
              }
              delay(textDelay-(textDelay*0.80));
            }else{  
               screen.escribirCaracter(text[j], i-(8*(j+1)));
              delay(textDelay-(textDelay*0.80));
            }
            
          
          }
        
    }
    
  }else if(digitalRead(MOD1) != 1){
    screen.borrar();
    int temp=0;
    for (int i=sizeof(text)*8; i >=0 ; i--){
        for(int j=0; j<sizeof(text);j++){
              temp=sizeof(text)-j-1;
              if(text[temp]=='*'){
              for(int k=0; k<8; k++){
                if(i-(8*(j+1))<=8 ){
                    screen.setRow(0,i-(8*(j)-k), Asterisco[k]);
                }
                if(i>=j*8){
                 screen.setRow(1, i-(8*(j)-k)-8, Asterisco[k]);

                }
                else if(i>=(j*16)){
                     screen.setRow(1, i-(8*(j)-k), Asterisco[k]);
                }
              }
              delay(textDelay-(textDelay*0.8));
            }
            else if(text[temp]=='-'){   
              for(int k=0; k<8; k++){
                if(i-(8*(j+1))<=8 ){
                    screen.setRow(0,i-(8*(j)-k), Guion[k]);
                }
                if(i>=j*8){
                 screen.setRow(1, i-(8*(j)-k)-8, Guion[k]);

                }
                else if(i>=(j*16)){
                     screen.setRow(1, i-(8*(j)-k), Guion[k]);
                }
              }
              delay(textDelay-(textDelay*0.8));
            }else if(text[temp]=='_'){
              for(int k=0; k<8; k++){
                if(i-(8*(j+1))<=8 ){
                    screen.setRow(0,i-(8*(j)-k), GuionB[k]);
                }
                if(i>=j*8){
                 screen.setRow(1, i-(8*(j)-k)-8, GuionB[k]);

                }
                else if(i>=(j*16)){
                     screen.setRow(1, i-(8*(j)-k), GuionB[k]);
                }
              }
              delay(textDelay-(textDelay*0.8));
            }else if(text[temp]=='#'){
              for(int k=0; k<8; k++){
                if(i-(8*(j+1))<=8 ){
                    screen.setRow(0,i-(8*(j)-k), Numeral[k]);
                }
                if(i>=j*8){
                 screen.setRow(1, i-(8*(j)-k)-8, Numeral[k]);

                }
                else if(i>=(j*16)){
                     screen.setRow(1, i-(8*(j)-k), Numeral[k]);
                }
              }
              delay(textDelay-(textDelay*0.80));
              }
              else{screen.escribirCaracter(text[temp], i-(8*(j)));
              delay(textDelay-(textDelay*0.80));  
              }
              }
              
        }
              
   }
}



// methods to show numbers
void turnOn_pin(int pos,boolean value){
    if(value){
      digitalWrite(list[pos],HIGH);
    }else{
      digitalWrite(list[pos],LOW);
    }
}
void loadList(boolean arreglo[]){
  for(int i=0;i<8;i++){
    turnOn_pin(i,arreglo[i]);
  }
}


void verifyRate(){
  int reading = analogRead(input);
  if(reading < 204.6){
    textDelay = 700;
    loadList(one);
  }else if(reading < 409.2){
    textDelay = 450;
    loadList(two);
  }else if(reading < 613.8){
    textDelay = 200;
    loadList(three);
  }else if(reading < 818.4){
    textDelay = 50;
    loadList(four);
  }else if(reading <= 1023){
    textDelay = 5;
    loadList(five);
  }
}
