#include <Keypad.h>     // Para manejo del teclado

#include<Wire.h>        // Puerto I2C
#include<RTClib.h>      // Reloj tiempo real
RTC_DS3231 rtc;

#include <Adafruit_GFX.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define LCD_CS A3   // Definimos los pines del LCD
#define LCD_CD A2   // para poder visualizar elementos graficos
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET 1


#define	BLACK     0x0000  // Definimos los colores 
#define	BLUE      0x001F  // que utilizaremos para
#define BLUE2     0x051F 
#define	RED       0xF800  // el texto y los elementos graficos
#define	GREEN     0x07E0
#define CYAN      0x07FF
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define WHITE     0xFFFF
#define DARKGREY  0x7BEF
#define ORANGE    0xFD20

#define tiempo 3000



const byte FILAS = 4;     // define numero de filas
const byte COLUMNAS = 3;    // define numero de columnas
char keys[FILAS][COLUMNAS] = {    // define la distribucion de teclas
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pinesFilas[FILAS] = {22,23,24,25};   // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {26,27,28}; // pines correspondientes a las columnas

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto

char TECLA;       // almacena la tecla presionada
char CLAVE[3];        // almacena en un array 6 digitos ingresados
char CLAVE_VER1[3] = "1*";   // almacena en un array la contraseña maestra
char CLAVE_SALIR1[3] = "1#";

char CLAVE_VER2[3] = "2*";
char CLAVE_SALIR2[3] = "2#";

char CLAVE_VER3[3] = "3*";
char CLAVE_SALIR3[3] = "3#";

char CLAVE_VER4[3] = "4*";
char CLAVE_SALIR4[3] = "4#";

char CLAVE_VER5[3] = "5*";
char CLAVE_SALIR5[3] = "5#";

char CLAVE_LOG[3] = "##";


/*
char CLAVE_VER10[3] = "10*";
char CLAVE_SALIR10[3] = "10#";

char CLAVE_VER15[3] = "15*";
char CLAVE_SALIR15[3] = "15#";

char CLAVE_VER20[3] = "20*";
char CLAVE_SALIR20[3] = "20#";
*/

byte INDICE = 0;      // indice del array

  
void setup(){
 tft.begin(0x9341);
 Serial.begin(9600);      // inicializa comunicacion serie

 if(! rtc.begin()){
     Serial.println("Modulo RTC no encontrado !");
     while (1);
  }

///////////Pantalla de inicio/////////////
  tft.setRotation(3);
  tft.fillScreen(DARKGREY);


//Habitación 1
  tft.drawRoundRect(10,10,48,40,5,BLUE);  tft.drawRoundRect(60,10,162,40,5,BLUE);  tft.drawRoundRect(225,10,90,40,5, BLUE);
  tft.fillRoundRect(11,11,46,38,5,BLACK); tft.fillRoundRect(61,11,160,38,5,WHITE); tft.fillRoundRect(226,11,88,38,5,YELLOW);

  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.setCursor(25,15);                   
  tft.print("1");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(240,23);                   //
  tft.print("LIBRE");

//Habitación 2

  tft.drawRoundRect(10,52,48,40,5,BLUE);  tft.drawRoundRect(60,52,162,40,5,BLUE);  tft.drawRoundRect(225,52,90,40,5, BLUE);
  tft.fillRoundRect(11,53,46,38,5,BLACK); tft.fillRoundRect(61,53,160,38,5,WHITE); tft.fillRoundRect(226,53,88,38,5,YELLOW);

  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.setCursor(25,57);                   //
  tft.print("2");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(243,65);                   //
  tft.print("LIBRE");

//Habitación 3

  tft.drawRoundRect(10,94,48,40,5,BLUE);  tft.drawRoundRect(60,94,162,40,5,BLUE);  tft.drawRoundRect(225,94,90,40,5, BLUE);
  tft.fillRoundRect(11,95,46,38,5,BLACK); tft.fillRoundRect(61,95,160,38,5,WHITE); tft.fillRoundRect(226,95,88,38,5,WHITE);

  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.setCursor(25,100);                   
  tft.print("3");

//Habitación 4

  tft.drawRoundRect(10,136,48,40,5,BLUE);  tft.drawRoundRect(60,136,162,40,5,BLUE);  tft.drawRoundRect(225,136,90,40,5, BLUE);
  tft.fillRoundRect(11,137,46,38,5,BLACK); tft.fillRoundRect(61,137,160,38,5,WHITE); tft.fillRoundRect(226,137,88,38,5,WHITE);

  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.setCursor(25,143);                   
  tft.print("4");


//Habitación 5

  tft.drawRoundRect(10,178,48,40,5,BLUE);  tft.drawRoundRect(60,178,162,40,5,BLUE);  tft.drawRoundRect(225,178,90,40,5, BLUE);
  tft.fillRoundRect(11,179,46,38,5,BLACK); tft.fillRoundRect(61,179,160,38,5,WHITE); tft.fillRoundRect(226,179,88,38,5,WHITE);

  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.setCursor(25,186);                   
  tft.print("5");
}



//////////Habitación 1//////////

void Entrada1(){

  DateTime fecha = rtc.now();

  tft.drawRoundRect(60,10,162,40,5,BLUE);  tft.drawRoundRect(225,10,90,40,5, BLUE);
  tft.fillRoundRect(61,11,160,38,5,BLACK); tft.fillRoundRect(226,11,88,38,5,BLACK);
  
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.setCursor(230,15);                   //
  tft.print("Entrada");
  tft.setCursor(63,15); //
  tft.print(fecha.day());                 
  tft.print("/");
  tft.print(fecha.month());
  tft.print("-");
  tft.print(fecha.hour());
  tft.print(":");
  tft.print(fecha.minute());
  tft.print(":");
  tft.print(fecha.second());
    
  Serial.print(fecha.day());
  Serial.print("/");
  Serial.print(fecha.month());
  Serial.print("-");
  Serial.print(fecha.hour());
  Serial.print(":");
  Serial.print(fecha.minute());
  Serial.print(":");
  Serial.print(fecha.second());
  Serial.println("");

}

void Salida1(){
  DateTime fecha = rtc.now();
  
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(235,32);                   
  tft.print("Salida");
  tft.setCursor(63,32); 
  tft.print(fecha.day());                 
  tft.print("/");
  tft.print(fecha.month());
  tft.print("-");
  tft.print(fecha.hour());
  tft.print(":");
  tft.print(fecha.minute());
  tft.print(":");
  tft.print(fecha.second());
    
  Serial.print(fecha.day());
  Serial.print("/");
  Serial.print(fecha.month());
  Serial.print("-");
  Serial.print(fecha.hour());
  Serial.print(":");
  Serial.print(fecha.minute());
  Serial.print(":");
  Serial.print(fecha.second());
  Serial.println("");

  delay(tiempo);
/////Disponible/////  
  tft.fillRoundRect(61,11,160,38,5,WHITE); tft.fillRoundRect(226,11,88,38,5,YELLOW);
  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(243,23);                   //
  tft.print("LIBRE");

}


//////////Habitación 2//////////

void Entrada2(){

  DateTime fecha = rtc.now();

  tft.drawRoundRect(60,52,162,40,5,BLUE);  tft.drawRoundRect(225,52,90,40,5, BLUE);
  tft.fillRoundRect(61,53,160,38,5,BLACK); tft.fillRoundRect(226,53,88,38,5,BLACK);

   
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.setCursor(230,54);                   //
  tft.print("Entrada");
  tft.setCursor(63,54); //
  tft.print(fecha.day());                 
  tft.print("/");
  tft.print(fecha.month());
  tft.print("-");
  tft.print(fecha.hour());
  tft.print(":");
  tft.print(fecha.minute());
  tft.print(":");
  tft.print(fecha.second());
    
  Serial.print(fecha.day());
  Serial.print("/");
  Serial.print(fecha.month());
  Serial.print("-");
  Serial.print(fecha.hour());
  Serial.print(":");
  Serial.print(fecha.minute());
  Serial.print(":");
  Serial.print(fecha.second());
  Serial.println("");

}



void Salida2(){
  DateTime fecha = rtc.now();
    
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.setCursor(235,74);                   
  tft.print("Salida");
  tft.setCursor(63,74);  //74+42
  tft.print(fecha.day());                 
  tft.print("/");
  tft.print(fecha.month());
  tft.print("-");
  tft.print(fecha.hour());
  tft.print(":");
  tft.print(fecha.minute());
  tft.print(":");
  tft.print(fecha.second());
    
  Serial.print(fecha.day());
  Serial.print("/");
  Serial.print(fecha.month());
  Serial.print("-");
  Serial.print(fecha.hour());
  Serial.print(":");
  Serial.print(fecha.minute());
  Serial.print(":");
  Serial.print(fecha.second());
  Serial.println("");

  delay(tiempo);
/////Disponible/////
  tft.fillRoundRect(61,53,160,38,5,WHITE); tft.fillRoundRect(226,53,88,38,5,YELLOW);
  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(243,65);                   //
  tft.print("LIBRE");

}




void loop(){
   
  DateTime fecha = rtc.now();

  TECLA = teclado.getKey();   // obtiene tecla presionada y asigna a variable
  if (TECLA){        // comprueba que se haya presionado una tecla
    CLAVE[INDICE] = TECLA;    // almacena en array la tecla presionada
    INDICE++;       // incrementa indice en uno
    Serial.print(TECLA);    // envia a monitor serial la tecla presionada
    }

//////////////////Habitación 1//////////////////////
  if(INDICE == 2){       // si ya se almacenaron los 6 digitos
     if(!strcmp(CLAVE, CLAVE_VER1)){   // compara clave ingresada con clave maestra
     Serial.println(" Ingreso");  // imprime en monitor serial que es correcta la clave
     INDICE = 0;
     Entrada1();
     }
     }

     if(INDICE == 2){       // si ya se almacenaron los 6 digitos
     if(!strcmp(CLAVE, CLAVE_SALIR1)){   // compara clave ingresada con clave maestra
     Serial.println(" Egreso");  // imprime en monitor serial que es correcta la clave
     INDICE = 0;
     Salida1();
     }
     }



//////////////////Habitación 2//////////////////////
  if(INDICE == 2){       // si ya se almacenaron los 6 digitos
     if(!strcmp(CLAVE, CLAVE_VER2)){   // compara clave ingresada con clave maestra
     Serial.println(" Ingreso");  // imprime en monitor serial que es correcta la clave
     INDICE = 0;
     Entrada2();
     }
     }


     if(INDICE == 2){       // si ya se almacenaron los 6 digitos
     if(!strcmp(CLAVE, CLAVE_SALIR2)){   // compara clave ingresada con clave maestra
     Serial.println(" Egreso");  // imprime en monitor serial que es correcta la clave
     INDICE = 0;
     Salida2();
     }
    
     else
     Serial.println(" ");  // imprime en monitor serial que es incorrecta la clave
     INDICE = 0;
    
    }
    
    
    }



