//Definiciones de los Pines 

// ENTRADAS (JOYSTICK ANALÓGICO)
//const int switch_joy  = 35;  // Pin D35 del ESP32 (GPIO25)  (Pin de Señal para controlar el switch del joystick para retomar a la posición seteada)
//const int x_joy = 34;  // Pin D34 del ESP32 (GPIO34)  (Pin de Señal para controlar la dirección en el eje x)
//const int y_joy = 39;  // Pin VN del ESP32  (GPIO39)  (Pin de Señal para controlar la dirección en el eje y)

// SALIDAS (SERVOMOTORES)
//const int servo1_pin = 2;     // Pin D2 del ESP32  (GPIO2)   (Pin de Señal para el servomotor que controla la rotación en x)
//const int servo2_pin = 4;     // Pin D4 del ESP32  (GPIO4)   (Pin de Señal para el servomotor que controla la rotación en y)

//SISTEMA EMBEBIDO: ESP32 DEVKIT V1 de 30 Pines 
//Codigo FINAL

// Libreria para controlar los servos en una ESP32
// https://github.com/jkb-git/ESP32Servo

#include <ESP32Servo.h>
#include <Arduino.h>

//GPIO PARA LAS ENTRADAS Y SALIDAS

const int switch_joy = 35;
const int x_joy = 34;                                               
const int y_joy = 39;
const int servo1_pin = 2;
const int servo2_pin = 4;

// POSICIÓN EN GRADOS DE LOS EJES "X" Y "Y"  

int x_pos;
int y_pos;

// ÁNGULOS INICIALES DE LOS EJES "X" Y "Y"     

int initial_position = 0;     // ángulo Inicial en grados para el eje "X"
int initial_position1 = 100 ; // ángulo Inicial en grados para el eje "Y"

// CREACIÓN DE LOS OBJETOS DESDE LA LIBRERIA <ESP32Servo.h>

Servo servo1; //Un servo para el eje "X" se activa creando una instancia de la clase ESP32Servo 
Servo servo2; //Un servo para el eje "Y" se activa creando una instancia de la clase ESP32Servo 


void setup ( ) {
    // Inicializar la comunicación serie a una velocidad de transmisión de 9600 baudios.
    Serial.begin(115200);
    // Configurar los pines específicos como una entrada
    pinMode (x_joy, INPUT) ;                     
    pinMode (y_joy, INPUT) ;
    pinMode(switch_joy , INPUT_PULLUP);  
    //Un servo se activa creando una instancia de la clase Servo 
    //y pasando el pin GPIO deseado al método attach().
    servo1.attach (servo1_pin); 
    servo2.attach (servo2_pin); 
    // Se fija la frecuencia de los servomotores en 50Hz
    servo1.setPeriodHertz(50);
    servo2.setPeriodHertz(50);
    // Se utiliza la función servo.write() para controlar la posición angular inicial de los servos.
    servo1.write(initial_position);
    servo2.write(initial_position1); 
}


void loop ( ) 
{  
    // Lectura de los valores de los pines analógicos del joystick.
    int x_pos = analogRead(x_joy) ;  
    int y_pos = analogRead(y_joy) ;
    int buttonState = digitalRead(switch_joy);
    // Dado que se utilizará para la lógica del programa 
    // los valores del joystick de 10 bits
    // Se realiza un escalado de valores de 12 bits a 10 bits de la lectura analógica
    // Del ADC para la configuración de "x_pos" y "y_pos"
    x_pos = (x_pos )*(1024)/(4096) ; 
    y_pos = (y_pos )*(1024)/(4096) ; 
    Serial.print("x_pos");
    Serial.println(x_pos);
    Serial.print("y_pos");
    Serial.println(y_pos);

if (buttonState == 0){
  servo1.write(0) ;  // ángulo Inicial en grados para el eje "X"
  servo2.write(100) ; // ángulo Inicial en grados para el eje "Y"
  delay(1000); 
  } else {
   // Mantener la misma posición configurada por el usuario
    }

// Configuración para el Servomotor del Eje "X"
if (x_pos < 300){
   if (initial_position < 10) 
{
  // Mantener la misma posición configurada por el usuario
 } 
else 
{ 
  // Cambiar la posición inicial en -10 grados para girar el servomotor
  initial_position = initial_position -10; 
  Serial.print("Initial");
  Serial.println(initial_position);
  servo1.write ( initial_position ) ; 
  delay (15) ; } 
  } 
  if (x_pos > 700)
  {
    if (initial_position > 180)
    { 
      // Mantener la misma posición configurada por el usuario
    }  
else {
    // Cambiar la posición inicial en +10 grados para girar el servomotor
    initial_position = initial_position + 10;
    servo1.write ( initial_position ) ;
    delay (15) ;
  }
Serial.print(" PosX");
Serial.println(initial_position);
}
// Configuración para el Servomotor del Eje "Y"
if (y_pos < 300){
   if (initial_position1 < 10) 
    {
      // Mantener la misma posición configurada por el usuario
     } 
else 
{ 
   // Cambiar la posición inicial en -10 grados para girar el servomotor
  initial_position1 = initial_position1 - 10; 
  servo2.write ( initial_position1 ) ; 
  delay (15) ; 
  } 
  
  } 
  if (y_pos > 700)
  {
    if (initial_position1 > 180)
    { 
       // Mantener la misma posición configurada por el usuario
    }  
else {
  // Cambiar la posición inicial en +10 grados para girar el servomotor
  initial_position1 = initial_position1 + 10;
  servo2.write ( initial_position1 ) ;
  delay (15);
}
Serial.print(" PosX");
Serial.println(initial_position1);
}
 }

