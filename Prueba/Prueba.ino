#include <MatrizLed.h>
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

char text[] = "prueba";
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
      //Serial1.print(dynamicText);
    }    
  }else if(digitalRead(MODTEXT) == 0){
    //memset(text,"",sizeof(text));
    dynamicText = "prueba";
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
    screen.escribirCaracter(text[contador] , 0); // Caracter, posicion en la pantalla
    contador++;
    delay(textDelay);
  }
  // -------------------- MODE 2 -----------------------------
  if(digitalRead(MOD2) == 1 and MOD1 != 1){
    // Desplazar texto manualmente hacia la derecha
    screen.borrar();
    for(int i=0; i<30; i++){
      screen.escribirFrase(text, i); // Texto, posicion en la pantalla
      delay(textDelay);
    }
  }else if(digitalRead(MOD1) != 1){
    screen.borrar();
    screen.escribirFraseScroll(text,textDelay);
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
    textDelay = 1400;
    loadList(one);
  }else if(reading < 409.2){
    textDelay = 900;
    loadList(two);
  }else if(reading < 613.8){
    textDelay = 400;
    loadList(three);
  }else if(reading < 818.4){
    textDelay = 100;
    loadList(four);
  }else if(reading <= 1023){
    textDelay = 10;
    loadList(five);
  }
}
