/* Código que simula un tablerdo de sustitución de jugadores
 *  Realizado por José Luis Bejarano Vásquez (sistemasymicros)
 * Fecha: 12/09/2017

youtube: www.youtube.com/c/sistemasymicros1
Facebook y Twitter: sistemasymicros

 */
#include <Keypad.h>

boolean habilitaSale = false;
boolean habilitaEntra = false;

char cifra_numero[2]; //Almacena las 2 cifras digitadas en el teclado
String cifra_limite = String(); //Almacena las 4 cifras 

String cifra1 = String();  //primera cifra del número presionado
String cifra2 = String(); //segunda cifra del número presionado
String cifra3 = String(); //tercera cifra del número presionado
String cifra4 = String(); //Cuarta cifra del número presionado

// ********* Configuración del teclado ***************************************
const byte ROWS=4;
const byte COLS=4;
char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};
byte rowPins[ROWS] = {13,6,5,4}; //Filas
byte colPins[COLS] = {3,2,1,0}; //Columnas 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//***************************************************************************
// Pines conectados a las entradas A B C D del decodificador 7447
const int A = 7;
const int B = 8;
const int C = 9;
const int D = 10;
//***************************************************************************
const int displayUnidadesSale = 15; //Pin analógico 1 (A1)
const  int displayDecenasSale = 11;
const  int displayUnidadesEntra = 12;
const int displayDecenasEntra = 14; //Pin analógico 0 (A0)


int cuenta =  0;        //Lleva la cuenta de las teclas presionadas
const int tiempo = 5;  //Tiempo en milisegunos del multiplexado

int numero = 0;

int unidades = 0;
int decenas = 0;
int centenas = 0;
int millares=0;
//************************************************************************

void setup() 
{
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT); 

  pinMode(displayUnidadesEntra,OUTPUT);
  pinMode(displayDecenasEntra,OUTPUT);
  pinMode(displayUnidadesSale,OUTPUT);
  pinMode(displayDecenasSale,OUTPUT);
      
  digitalWrite(displayUnidadesEntra,HIGH);
  digitalWrite(displayDecenasEntra,HIGH);
  digitalWrite(displayUnidadesSale,HIGH);
  digitalWrite(displayDecenasSale,HIGH);

   
 }

 void escribirBcd(byte num)
{
  digitalWrite(A, (num&1)==1);
  digitalWrite(B, (num&2)==2);
  digitalWrite(C, (num&4)==4);
  digitalWrite(D, (num&8)==8);
}

void habilitarUnidadesSale()
{
  escribirBcd(unidades);
  digitalWrite(displayUnidadesSale,HIGH);
  digitalWrite(displayDecenasSale,LOW);
  digitalWrite(displayUnidadesEntra,LOW);
  digitalWrite(displayDecenasEntra,LOW);
  delay(tiempo);
}  

void habilitarDecenasSale()
{
  escribirBcd(decenas);
  digitalWrite(displayUnidadesSale,LOW);
  digitalWrite(displayDecenasSale,HIGH);
  digitalWrite(displayUnidadesEntra,LOW);
  digitalWrite(displayDecenasEntra,LOW);
  delay(tiempo);
}  

void habilitarUnidadesEntra()
{
  escribirBcd(centenas);
  digitalWrite(displayUnidadesSale,LOW);
  digitalWrite(displayDecenasSale,LOW);
  digitalWrite(displayUnidadesEntra,HIGH);
  digitalWrite(displayDecenasEntra,LOW);
  delay(tiempo);
}

void habilitarDecenasEntra()
{
  escribirBcd(millares);
  digitalWrite(displayUnidadesSale,LOW);
  digitalWrite(displayDecenasSale,LOW);
  digitalWrite(displayUnidadesEntra,LOW);
  digitalWrite(displayDecenasEntra,HIGH);
  delay(tiempo);
}
 
void loop() 
{


char key = keypad.getKey();
         
if(key) 
  { 
    if(key=='A')
    {
      habilitaSale=true;
      habilitaEntra=false;      
      cuenta=0;
                 
    }

    if(key=='B')
    {
      habilitaEntra=true;
      habilitaSale=false;
      cuenta=0;
    }

    if(key=='C')
    {
      numero=0;
    }
          
     if(key!='A' && key!='B' && key!='C' && key!='D')
    {

     //Se habilitan los displays de los números del jugador que SALE
     if(habilitaSale==true)
     {
          
     cifra_numero[cuenta] = key;
     
     cifra1=String(cifra_numero[0]);
     cifra2=String(cifra_numero[1]);     
     
     cifra_limite = cifra1+cifra2;

     numero = cifra_limite.toInt();
          
     cuenta++; // Incremento el contador   

     if(cuenta>1)
     {
      cuenta=0;
     }
              
     }     

//***********************************************************
     //Se habilitan los displays de los números del jugador que ENTRA
     if(habilitaEntra==true)
     {

     cifra_numero[cuenta] = key;
     
     cifra3=String(cifra_numero[0]);
     cifra4=String(cifra_numero[1]);     
     
     cifra_limite = cifra3+cifra4+cifra1+cifra2;

     numero = cifra_limite.toInt();
     
     cuenta++; // Incremento el contador 

     if(cuenta>1)
     {
      cuenta=0;
     }
     
                
     }
      
    }
  
  } // fin del key
        
         millares=numero/1000;
         centenas=(numero-(millares*1000))/100;
         decenas=(numero- (millares*1000 + centenas*100))/10;
         unidades=numero-(millares*1000 + centenas*100 + decenas*10 );
                       
         habilitarUnidadesSale();
         habilitarDecenasSale();
         habilitarUnidadesEntra();
         habilitarDecenasEntra();

 
}
