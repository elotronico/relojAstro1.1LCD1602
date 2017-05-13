#define led 13
//-----------------------------------------------------
//---	    		TECLAS DEL TECLADO				---
//-----------------------------------------------------
#define delayPulsacion 160

#define pinbtnUp 35
#define pinbtnDown 39
#define pinbtnOk 45
#define pinbtnCancel 47

#define pincommbtn 32


//-----------------------------------------------------
//---	    			astronomico.ino				---
//-----------------------------------------------------
// what is our longitude (west values negative) and latitude (south values negative)
float const LATITUDE = 42.22;
float const LONGITUDE = -8.81;
int zonaHoraria = 1;

uint8_t tablaOrtoOcaso[4] = {0,0,0,0};

#define horaAmanece tablaOrtoOcaso[0]
#define minutoAmanece tablaOrtoOcaso[1]

#define minutoAnochece tablaOrtoOcaso[2]
#define horaAnochece tablaOrtoOcaso[3]


//minutos dek dia a los que suceden [0-1440]
int mdiarioAmanece=0;
int mdiarioAnochece=0;


//-----------------------------------------------------
//---		tabla de horarios de encendidos		    ---
//-----------------------------------------------------


//circuito 1	
//enciende con ocaso - apaga a hora fija
int horarioC1[6]={};
#define enC1 horarioC1[0]
#define mdiarioC1 horarioC1[1]
#define horaOffc1 horarioC1[2]
#define minutoOffc1 horarioC1[3]



//circuito 2
//enciende con hora - apaga a orto
int horarioC2[6]={};
#define enC2 horarioC2[0]
#define mdiarioC2 horarioC2[1]
#define horaOnC2 horarioC2[2]
#define minutoOnC2 horarioC2[3]



//-----------------------------------------------------
//---		fecha y hora actual. leido de RTC	    ---
//-----------------------------------------------------

volatile uint8_t tablaHoraActual[5]={00,00,1,1,1};

#define horaActual tablaHoraActual[0]
#define minutoActual tablaHoraActual[1]
#define diaDeSemana tablaHoraActual[2]
#define mesActual tablaHoraActual[3]
#define diaActual tablaHoraActual[4]


int anoActual = 2016;

//minutos dek dia a los que suceden [0-1440]
int mdiarioHora=0;		//este es el minuto dek dia en el que estamos en cada instante


//-----------------------------------------------------
//---			definiciones para el menu			---
//-----------------------------------------------------

unsigned int menuPosX = 0;
unsigned int menuPosY = 0;

const int longMenuPpal=2;
int largoSubmenus[(longMenuPpal+1)]={0,2,2};
char teclaPulsada = NO_KEY;

uint8_t numeroDiasMes[14]={0,31,28,31,30,31,30,31,31,30,31,30,31,29};
uint8_t minutoAnterior;



//-----------------------------------------------------
//---					MISCELANEA					---
//-----------------------------------------------------
//#define alarmPin 12

LiquidCrystal_I2C lcd(0X27,20,4);

char *monthName[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

enum diasSemana
{Lu,Ma,Mi,Ju,Vi,Sa,Do
};
char botonPulsado = '0';

#define RTCpinInt 2			//pin al que esta conectado la interrupcion del RTC




//-----------------------------------------------------
//---					E/S					---
//-----------------------------------------------------


bool StateS1 = LOW;
bool StateS2 = LOW;
bool StateS3 = LOW;

#define salida1 54 //PF0
#define salida2 55//PF1
#define salida3 56//PF2




//-----------------------------------------------------
//---					LCD					---
//-----------------------------------------------------
uint8_t enhe[8] = { 
			B00000,
			B10110,
			B01000,
			B10110,
			B11001,
			B10001,
			B10001,
			B00000
			};

uint8_t barra[8] = { 
					B00100,
					B00100,
					B00100,
					B00100,
					B00100,
					B00100,
					B00100,
					B00100
					};

