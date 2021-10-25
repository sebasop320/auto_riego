/*
Riego automatico BY:
Sebastian Ocampo
*/
#define LED 13

const int sensor = A0;          //Pin en el que está conectado el sensor
const int Rc = 1000;            //Resistencia de calibración  
const int relay = 2;            //Pin en en que está conectado el Relay
const int relay2 = 3;            //pin del relay 2

int V;
int contador = 0;
long Rsensor;
long Resk;
unsigned long tr = 2;            //Tiempo de regado  en minutos                                   //AJUSTAR
unsigned long tespera = 10;      //Tiempo espera en minutos                                       //AJUSTAR
const int rr = 0;               //Resistencia (en kohmios) a partir de la cual empieza a regar   //AJUSTAR

void setup() {
  Serial.begin(9600);             //inicia comunicación serial
  pinMode (relay,OUTPUT);
  pinMode (relay2,OUTPUT);        //Configurar los relay como salida
  pinMode(LED, OUTPUT);
}

void loop() {
  V =  analogRead(sensor);        //leer sensor
  Rsensor = 1024L * Rc / V - Rc;  //calcular resistencia del sensor
  Resk = Rsensor /1000;           //pasar a kiloohmios

  Serial.print(contador); Serial.println("  riegos.");  //contador para ver en serial cuantas veces se ha regado
Serial.print("Valor resistencia: "); Serial.print(Resk); Serial.println(" mil ohmios ");   //escribir en serial el valor de la resistencia
  delay(1000);

 if (Resk>rr){
  digitalWrite(relay2, HIGH);     // activa el relay2
  digitalWrite(relay,HIGH);       //activar relay
  digitalWrite(LED, HIGH);
  delay(tr*60*1000);              // Espera Tiempo de regado con relay activado
  digitalWrite(relay2, LOW);       // desactiva el relay 2
  digitalWrite(LED, LOW);
  digitalWrite(relay,LOW);        //desactivar relay
  delay(tespera*60*1000);         // Espera Tiempo de espera entre regados con relay desactivado para que el agua se filtre a la tierra y llegue al sensor
  contador = contador + 1 ;   
  }}
