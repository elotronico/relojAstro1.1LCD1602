//#include "menus.h"

//#define debug		//habilita comandos serie

#include <Keypad.h>
#include <Key.h>
volatile bool stateled= false;
volatile bool stateinterrupt = false;


#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <DS1337RTC.h>
#include <Time.h>
#include <Wire.h>
#include <TimeLord.h>

#include "Header.h"



//---------------------------------------------------------------
//                        teclado
//---------------------------------------------------------------
const byte ROWS = 1; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {  {'u','d','o','c'}};

byte rowPins[ROWS] = {pincommbtn}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {pinbtnUp, pinbtnDown, pinbtnOk, pinbtnCancel}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//---------------------------------------------------------------
//---------------------------------------------------------------




void siHayInterrupcion(void){
	

	Serial.println();
	lineas();
	Serial.println("-------cambio de minuto--------");
	lineas();
	

	//1  actualizamos la hora marcada por el RTC --> micro
	leerHora();
		
	//2  apaga alarma RTC
	RTC.resetAlarms();


	//revisa si hay que actuar sobre alguna salida
	revisaProgramaciones();

	
	//programamos la siguiente interrupcion
	RTCrenuevaInterrupcion();
	
	
	
	ponerEnHora(diaActual,mesActual,anoActual,horaActual,minutoActual,58);

	//actualizarPantallaPpalLCD();
	imprimirHoraSerial();
	enviaSerialEstadoSalidas();
	//enviarSerialProgramacionFLASH();

}






//-----------------------------------------------------
//---					void SETUP 					---
//-----------------------------------------------------

void setup(){
	
	// Add an event listener for this keypad
	keypad.addEventListener(keypadEvent); 

	lcd.begin();
	Serial.begin(57600);

	lcd.print("Iniciando...");
	Serial.println("Iniciando...");
	delay(1000);

	//led indicador como salida
	pinMode(led,OUTPUT);		
	digitalWrite(led,HIGH);

	pinMode(salida1,OUTPUT);
	pinMode(salida2,OUTPUT);
	pinMode(salida3,OUTPUT);
	

	digitalWrite(salida1,LOW);
	digitalWrite(salida2,LOW);
	digitalWrite(salida3,LOW);

	
	//actualizarMenuLcd();
		

	leerProgramacionDeEEPROM();								//pasa tabla horarios de la EEPROM --> FLASH

	leerHora();												//refresca los valores anoActual, mesActual,diaActual, horaActual minutoActual
	calculoOrtoOcaso(diaActual, mesActual, anoActual);		//calculamos el orto y ocaso para el dia actual

	RTC.resetAlarms();
	attachInterrupt(digitalPinToInterrupt(RTCpinInt), RTCinterrupcion, FALLING);		//interrupcion del reloj (INTA)
	siHayInterrupcion();				//comprueba si hay que activar alguna salida y programa la interrupcion para el minuto siguiente
	actualizarPantallaPpalLCD();		
	lcd.clear();
	
	actualizarPantallaPpalLCD();
		
	Serial.println("salimos del setup");
	
}



  
//-----------------------------------------------------
//---					void LOOP 					---
//-----------------------------------------------------
void loop(){
	
	//e//delay(delayPulsacion);
	teclaPulsada = leerTeclado();
	
	if(teclaPulsada){	
		Serial.println("TelcaPulsada: " + (String)teclaPulsada);
		actualizarPosicionMenu();
//		teclaPulsada = '0';
	}


	//comprobamos si la interrupcion ha activado el flag
	if((stateinterrupt == true) &(menuPosX == 0)){			
		stateinterrupt = false;			//lo reseteamos
		siHayInterrupcion();			//hacemos el codigo propio de la interrupcion
		actualizarPantallaPpalLCD();
	}

	
	if(menuPosX == 0 && menuPosY ==0){	
		teclaPulsada = leerTeclado();
		if(teclaPulsada){	
			actualizarPosicionMenu();
			teclaPulsada = '0';
		}
	} 	
}




//-----------------------------------------------------
//---					void LOOP 					---
//          Taking care of some special events
//-----------------------------------------------------

void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case PRESSED:
        if (key == 'o') {
            
            
        }
        break;

    case RELEASED:
        if (key == 'c') {
            
        }
        break;

    case HOLD:
        if (key == 'u') {
           teclaPulsada='u';
        }

		else if (key == 'd') {
           teclaPulsada='d';
        }
        break;
    }
}
