
//esta es la interrupcion generada por el reloj. lo que hacemos es poner una bandera en alto, la cual es comprobada ciclicamente en el void loop.
void RTCinterrupcion(){

	stateinterrupt = true;

}


//programa la alarma del RTC para el minuto siguiente. en el minuto 00:00 hace recalculo de orto-ocaso
void RTCrenuevaInterrupcion(void){

	//si estamos en el minuto 1-58
	if(minutoActual < (uint8_t)59){			
		//programamos alarma para el siguiente minuto
		ponerHoraAlarma(diaActual,mesActual,anoActual,horaActual,(minutoActual+1),(uint8_t)0);	
		Serial.println("alarma programada para: " + (String)diaActual + "/" + (String)mesActual + "/"  + (String)anoActual  + " " + (String)horaActual + ":" + (String)(minutoActual+1));
	}

	

	//si estamo sen el minuto 59
	else if (minutoActual == (uint8_t)59){

		//y son menos de las 23 horas
		if (horaActual < (uint8_t)23){

			//alarma para minuto siguiente del mismo dia
			ponerHoraAlarma(diaActual,mesActual,anoActual,(horaActual+1),(uint8_t)0,(uint8_t)0);	
			//Serial.println("2-alarma programada para: " + (String)diaActual + "/" + (String)mesActual + "/"  + (String)anoActual  + " " +(String)(horaActual+1) + ":" + (String)0);
		}

		//y si son las 23 horas --> cambio de dia
		else if (horaActual ==  (uint8_t)23){

			//es el ultimo dia del mes  -->  ponemos la alarma para el dia 1 del mes siguiente
			if(diaActual == numeroDiasMes[mesActual]){
							

				//es el ultimo dia de dicciembre
				if(mesActual == (uint8_t)12){
					//alarma para 1 enero año siguiente
					ponerHoraAlarma((uint8_t)1,(uint8_t)1,(anoActual+(uint8_t)1),(uint8_t)0,(uint8_t)0,(uint8_t)0);
					//Serial.println("3-alarma programada para: " + (String)1 + "/" + (String)1 + "/"  + (String)(anoActual+1)  +" " + (String)0 + ":" + (String)0);
					//calculoOrtoOcaso(diaActual, mesActual, anoActual);	

					if(anoBisiesto(anoActual+1)== true){
						numeroDiasMes[2]=29;
					}
					else{ 
						numeroDiasMes[2]=28;
					}
				}

				//no es el ultimo mes
				else{
					//alarma para 1 mes siguiente
					ponerHoraAlarma((uint8_t)1,(mesActual+1),anoActual,(uint8_t)0,(uint8_t)0,(uint8_t)0);
					//Serial.println("4-alarma programada para: " + (String)1 + "/" + (String)(mesActual+(uint8_t)1)+ "/"  + (String)anoActual  +" " + (String)0 + ":" + (String)0);
					//calculoOrtoOcaso(diaActual, mesActual, anoActual);
				}	
			}

			//no es ultimo dia del mes  -->  ponemos alarma para el dia siguiente
			else{
				//alarma para dia siguiente 
				ponerHoraAlarma((diaActual+1),mesActual,anoActual,(uint8_t)0,(uint8_t)0,(uint8_t)0);
				//Serial.println("5-alarma programada para: " + (String)(diaActual+1) + "/" + (String)mesActual + "/"  + (String)anoActual  +" " + (String)0 + ":" + (String)0);
				//calculoOrtoOcaso(diaActual, mesActual, anoActual);
			}		
		}
	}

	//si
	if (horaActual == (uint8_t)0 && minutoActual==(uint8_t)0){
		calculoOrtoOcaso(diaActual, mesActual, anoActual);
		
	}
}

//pone en hora el RTC
void ponerEnHora(uint8_t dia, uint8_t mes, int ano, uint8_t hora, uint8_t minutos, uint8_t segundos){
  tmElements_t tmSet;
  tmSet.Year = (ano-1970);
  tmSet.Month = mes;
  tmSet.Day = dia;
  tmSet.Hour = hora;
  tmSet.Minute = minutos;
  tmSet.Second = segundos;


  anoActual = ano;
  mesActual = mes;
  diaActual= dia;

  horaActual=hora;
  minutoActual = minutos;


  RTC.set(makeTime(tmSet), CLOCK_ADDRESS); // set the clock

  RTC.freqSelect(1);  // set the squarewave freq on alarm pin b to 4.096kHz
 }



//lee la hora del rtc y lo carga en los registros 
void leerHora()
{
	time_t clock = RTC.get(CLOCK_ADDRESS);
	time_t alarm = RTC.get(ALARM1_ADDRESS);  // get the time the alarm is set for
	tmElements_t clockSet;
	tmElements_t alarmSet;
	breakTime(clock, clockSet);
	breakTime(alarm, alarmSet);


	horaActual = clockSet.Hour;
	minutoActual = clockSet.Minute;
	  
	anoActual = (clockSet.Year + 1970);
	mesActual = clockSet.Month;
	diaActual = clockSet.Day;
	diaDeSemana = clockSet.Wday;

	mdiarioHora= (horaActual*60)+minutoActual;

}


/*
void leerAlarma(void)
{

	time_t clock = RTC.get(CLOCK_ADDRESS);
	time_t alarm = RTC.get(ALARM1_ADDRESS);  // get the time the alarm is set for
	tmElements_t clockSet;
	tmElements_t alarmSet;
	breakTime(clock, clockSet);
	breakTime(alarm, alarmSet);
	

	// print the alarm time
	Serial.print("ALARM1: ");
	Serial.print((int)alarmSet.Day);
	Serial.print(" ");
	Serial.print((int)alarmSet.Hour);
	printDigits(alarmSet.Minute);
	printDigits(alarmSet.Second);
	Serial.print("\t");
  
	if(digitalRead(alarmPin) == HIGH)		//pin is set low when alarm is triggered
	{  
	Serial.println("ALARM off");
	}
	else
	{
	Serial.println("ALARM on");
	RTC.resetAlarms();
	}
  
}
*/


//envia la hora entregada por el puerto serie
void imprimirHoraSerial(){
	Serial.print((int)diaActual);
	Serial.print("/");
	Serial.print((int)mesActual);		//monthName[month() - 1]);
	Serial.print("/");
	Serial.print((int)anoActual);		//year());
	Serial.print(" ");
	Serial.print((int)horaActual);		//hour());
	Serial.print(":");
	if(minutoActual<10)	{
		Serial.print('0');
	}
	Serial.println(minutoActual);

}


//muesta la FECHA ACTUAL, HORA ACTUAL Y HORA ORTO Y OCASO DE EL DIA DE HOY en el lcd (antes llamado imprimirHoraLCD)
void actualizarPantallaPpalLCD(){

	//-----------------------------------------------------
	//						linea 1
	//-----------------------------------------------------
	////imprimimos la fecha
	lcd.setCursor(0,0);
	//----------------imprime la fecha ---------------------
		
	imprimirDigitosLCD(diaActual);
	lcd.print("/");	
	
	//imprime mes
	imprimirDigitosLCD(mesActual);
	lcd.print("/");	
	
	//imprime año  -- la resta es para imprimir solo dos digitos
	lcd.print((String)(anoActual-2000)); 


	//----------------imprimimos la hora orto ---------------------
	lcd.setCursor(11,0);
	//imprime hora
	if(horaAmanece<10)
	{	lcd.print("0");	}
	lcd.print((String)horaAmanece + ":"); 

	//imprime minutos
	if(minutoAmanece<10)
	{	lcd.print("0");	}
	lcd.print((String)minutoAmanece); 


	//-----------------------------------------------------
	//						linea 2
	//-----------------------------------------------------
	//----------------imprimimos la hora ---------------------
	lcd.setCursor(1,1);
	//imprime hora
	if(horaActual<10)
	{	lcd.print("0" + (String)horaActual + ":");	}
	else
	{	lcd.print((String)horaActual + ":"); }
	
	//imprime minutos
	if(minutoActual<10)
	{	lcd.print("0" + (String)minutoActual);	}
	else
	{	lcd.print((String)minutoActual); }


	//----------------imprimimos la hora ocaso ---------------------
	lcd.setCursor(11,1);
	//imprime hora
	if(horaAnochece<10)
	{	lcd.print("0");	}
	lcd.print((String)horaAnochece + ":"); 

	//imprime minutos
	if(minutoAnochece<10)
	{	lcd.print("0");	}
	lcd.print((String)minutoAnochece); 

			


}


//bueno - PARA PONER EN FECHA EL RTC MEDIANTE LCD
void RTCponerEnFechaLCD(){
	unsigned int setAno=anoActual, setMes=mesActual, setDia=diaActual;
	bool bisiesto= false;
	//----------------------
	//establecer año
	//----------------------
	lcd.clear();
	lcd.print("--Cambio Fecha--");


	lcd.blink_on();

	lcd.setCursor(0,1);
	lcd.print("A");
	lcd.write(0);
	lcd.print("o:");
	lcd.setCursor(12,1);
	lcd.print((String)setAno );
	lcd.setCursor(15,1);
	teclaPulsada= '0';
	while (teclaPulsada != 'o')	//mientras no pulsemos ok
	{	
		//e//delay(delayPulsacion);
		teclaPulsada = leerTeclado();
		if((teclaPulsada == 'u') && (setAno<2100))		//año ++
		{
			setAno++;
			lcd.setCursor(12,1);
			lcd.print((String)setAno );
			lcd.setCursor(15,1);
		}
		else if ((teclaPulsada =='d') && (setAno>1970))		//año --
		{
			setAno--;lcd.setCursor(12,1);
			lcd.print((String)setAno );
			lcd.setCursor(15,1);
		}
		else if (teclaPulsada== 'c')			//cancelamos cambios
		{
			
			lcd.clear();
			lcd.blink_off();
			lcd.print("Cancelado");
			delay(1000);
			return;
		}

	}

	//comprobamos si el año es bisiesto. si el resto de dividir el año entre 4 es cero --> es bisiesto
	if(anoBisiesto(setAno)==1){
		bisiesto= true; 
	}
	else{
		bisiesto = false;
	}


	
	//----------------------
	//establecer mes
	//----------------------
	teclaPulsada= '0';

	lcd.clear();
	lcd.print("--Cambio Fecha--");

	lcd.setCursor(0,1);
	lcd.print("Mes: ");

	lcd.setCursor(14,1);
	imprimirDigitosLCD(setMes);
	
	lcd.setCursor(15,1);
	lcd.blink_on();
	
	while(teclaPulsada!='o')
	{
		//e//delay(delayPulsacion);
		teclaPulsada = leerTeclado();
		if((teclaPulsada == 'u') && (setMes<12))			//mes ++
		{
			setMes++;
			lcd.setCursor(14,1);
			imprimirDigitosLCD(setMes);
			lcd.setCursor(15,1);
		}
		else if ((teclaPulsada =='d') && (setMes>1))		//mes --
		{
			setMes--;
			lcd.setCursor(14,1);
			imprimirDigitosLCD(setMes);
			lcd.setCursor(15,1);
		}
		else if (teclaPulsada== 'c')			//cancelamos cambios
		{
			lcd.clear();
			lcd.blink_off();
			lcd.print("Cancelado");
			delay(1000);
			return;
		}
	}

	//----------------------
	//establecer dia
	//----------------------


	uint8_t numDias=28;
	
	
	//si estamos en febrero de año bisiesto
	if((setMes==2) & (bisiesto== true)){
		numDias=29;
	}

	//sino
	else{
		numDias=numeroDiasMes[setMes];
	}
	
	//si el dia actual es mayor al maximo de dias que tiene el mes seleccionado
	//establecemos el setdia en el maximo del mes seleccionado
	if(setDia>numDias){
		setDia=numDias;
	}



	teclaPulsada= '0';

	lcd.clear();
	lcd.print("--Cambio Fecha--");

	lcd.setCursor(0,1);
	lcd.print("Dia: ");
	
	lcd.setCursor(14,1);
	imprimirDigitosLCD(setDia);
	
	lcd.setCursor(15,1);
	lcd.blink_on();

	while(teclaPulsada!='o')
	{
		//e//delay(delayPulsacion);
		teclaPulsada = leerTeclado();


		if((teclaPulsada == 'u') && (setDia<numDias))		//dia ++
		{
			setDia++;
			lcd.setCursor(14,1);
			imprimirDigitosLCD(setDia);
			lcd.setCursor(15,1);
		}
		else if ((teclaPulsada =='d') && (setDia>1))					//dia --
		{
			setDia--;
			lcd.setCursor(14,1);
			imprimirDigitosLCD(setDia);
			lcd.setCursor(15,1);
		}
		else if (teclaPulsada== 'c')							//cancelamos cambios
		{	
			lcd.clear();
			lcd.blink_off();
			lcd.print("Cancelado");
			delay(1000);
			return;
		}
	}



	lcd.clear();
	lcd.blink_off();



	ponerEnHora(setDia,setMes,setAno,horaActual,minutoActual,(uint8_t)0);
	Serial.println("Puesto en Fecha: "+ (String)setDia + '/'+  (String)setMes +'/'+ (String)setAno + '\t' +(String)horaActual + ':' +(String)minutoActual); 

	
	lcd.setCursor(1,0);
	lcd.print("Fecha ajustada");

	//imprimimos en la linea 1 del lcd la fecha
	lcd.setCursor(2,1);
	imprimirDigitosLCD(setDia);
	lcd.print("/");
	imprimirDigitosLCD(setMes);
	lcd.print("/");
	imprimirDigitosLCD(setAno);

	calculoOrtoOcaso(diaActual, mesActual, anoActual);						//si cambiamos la fecha hacemos un recalculo de hora orto ocaso			
	
	
	
	delay(2000);
	lcd.clear();

	siHayInterrupcion();	//usamos este porque asi tambien coprobamos si hay que modificar el estado de alguna salida, de lo contrario habria que esperar al siguiente minuto

	teclaPulsada = '0';
}







//bueno - PARA PONER EN HORA EL RTC MEDIANTE LCD
void RTCponerEnHoraLCD(){
	unsigned int setHora=horaActual, setMinutos=minutoActual;


	
	teclaPulsada= '0';
	lcd.clear();
	lcd.print("--Cambio  hora--");
	lcd.setCursor(0,1);
	lcd.print("Hora:"); 

	lcd.blink_on();
	lcd.setCursor(11,1);
	imprimirDigitosLCD(setHora);
	lcd.print(":");
	imprimirDigitosLCD(setMinutos);
	lcd.setCursor(12,1);
	
	//----------------------
	//establecemos hora
	//----------------------
	while(teclaPulsada!='o')		
	{
		//e//delay(delayPulsacion);
		teclaPulsada = leerTeclado();
		if((teclaPulsada == 'u') && (setHora<23))		//hora ++
		{
			setHora++;
			lcd.setCursor(11,1);
			imprimirDigitosLCD(setHora);
			lcd.setCursor(12,1);
		}
		else if ((teclaPulsada =='d') && (setHora>0))		//hora --
		{
			setHora--;
			lcd.setCursor(11,1);
			imprimirDigitosLCD(setHora);
			lcd.setCursor(12,1);
		}
		else if (teclaPulsada== 'c')					//cancelamos cambios
		{	
			lcd.clear();
			lcd.blink_off();
			lcd.print("Cancelado");
			delay(1000);
			return;
		}
	}

	lcd.setCursor(0,1);
	lcd.print("Minuto:");

	lcd.setCursor(15,1);

	//----------------------
	//establecer minutos
	//----------------------
	//e//teclaPulsada='0';
	while (teclaPulsada != 'o')
	{
		//e//delay(delayPulsacion);
		teclaPulsada = leerTeclado();
		if((teclaPulsada == 'u') && (setMinutos<59))			//hora ++
		{
			setMinutos++;
			lcd.setCursor(14,1);
			imprimirDigitosLCD(setMinutos);
			lcd.setCursor(15,1);
		}
		else if ((teclaPulsada =='d') && (setMinutos>0))		//hora --
		{
			setMinutos--;
			lcd.setCursor(14,1);
			imprimirDigitosLCD(setMinutos);
			lcd.setCursor(15,1);
		}
		else if (teclaPulsada== 'c')					//cancelamos cambios
		{	
			lcd.clear();
			lcd.blink_off();
			lcd.print("Cancelado");
			delay(1000);
			return;
		}
	}




	lcd.clear();
	lcd.blink_off();

	ponerEnHora(diaActual,mesActual,anoActual,setHora,setMinutos,(uint8_t)0);
	Serial.println("Puesto en Hora: "+ (String)diaActual + '/'+  (String)mesActual +'/'+ (String)anoActual + '\t' +(String)setHora + ':' +(String)setMinutos); 

	//imprimimos en la linea 3 del lcd la hora
	lcd.setCursor(1,0);
	lcd.print("Fecha ajustada");


	lcd.setCursor(3,1);
	imprimirDigitosLCD(setHora);
	lcd.print(":");
	imprimirDigitosLCD(setMinutos);

	
	
	delay(2000);
	//RTCrenuevaInterrupcion();
	siHayInterrupcion();	//usamos este porque asi tambien coprobamos si hay que modificar el estado de alguna salida, de lo contrario habria que esperar al siguiente minuto
	lcd.clear();
	
	
	teclaPulsada = '0';
	actualizarPantallaPpalLCD();

}


void imprimirDigitosLCD(unsigned int dato)
{
	if(dato<10)	{
		lcd.print("0" + (String)dato);
	}
	else	{
		lcd.print((String)dato);
	}

}


void imprimirDigitosSerial(unsigned int dato)
{
	if(dato<10)	{
		Serial.print("0" + (String)dato);
	}
	else	{
		Serial.print((String)dato);
	}

}

/*
//bueno - para programar hora desde lcd
void RTCponerAlarmaLCD()
{
	unsigned int setAno=anoActual, setMes=mesActual, setDia=diaActual, setHora=horaActual, setMinutos=minutoActual;

	//establecer año
	lcd.clear();
	lcd.blink_on();

	lcd.print("Anho:");
	lcd.setCursor(12,0);
	lcd.print((String)setAno );
	lcd.setCursor(15,0);
	teclaPulsada= '0';
	while (teclaPulsada != 'o')	//mientras no pulsemos ok
	{	
		delay(delayPulsacion);
		teclaPulsada = leerTeclado();
		if((teclaPulsada == 'u') && (setAno<2100))		//año ++
		{
			setAno++;
			lcd.setCursor(12,0);
			lcd.print((String)setAno );
			lcd.setCursor(15,0);
		}
		else if ((teclaPulsada =='d') && (setAno>1970))		//año --
		{
			setAno--;
			lcd.setCursor(12,0);
			lcd.print((String)setAno );
			lcd.setCursor(15,0);
		}
		else if (teclaPulsada== 'c')			//cancelamos cambios
		{
			
			lcd.clear();
			lcd.blink_off();
			lcd.print("Cancelado");
			delay(1000);
			return;
		}
	}

	//comprobamos si el año es bisiesto. si el resto de dividir el año entre 4 es cero --> es bisiesto
	if(setAno%4==0)				//si es bisiesto
	{
		digitalWrite(led,HIGH);
		numeroDiasMes[2]=29;
	}
	else						//si no es bisiesto
	{
		digitalWrite(led,LOW);
		numeroDiasMes[2]=28;
	}

	
		
	//establecer mes
	teclaPulsada= '0';
	
	lcd.clear();
	lcd.print("Mes:");

	lcd.setCursor(14,0);
	imprimirDigitosLCD(setMes);
	lcd.setCursor(15,0);
	
	while(teclaPulsada!='o')
	{
		delay(delayPulsacion);
		teclaPulsada = leerTeclado();
		if((teclaPulsada == 'u') && (setMes<12))		//año ++
		{
			setMes++;
			lcd.setCursor(14,0);
			imprimirDigitosLCD(setMes);
			lcd.setCursor(15,0);
		}
		else if ((teclaPulsada =='d') && (setMes>1))		//año --
		{
			setMes--;
			lcd.setCursor(14,0);
			imprimirDigitosLCD(setMes);
			lcd.setCursor(15,0);
		}
		else if (teclaPulsada== 'c')			//cancelamos cambios
		{
			lcd.clear();
			lcd.blink_off();
			lcd.print("Cancelado");
			delay(1000);
			return;
		}
	}


	//establecer dia
	teclaPulsada= '0';

	lcd.clear();
	lcd.print("Dia:");

	lcd.setCursor(14,0);
	imprimirDigitosLCD(setDia);
	lcd.setCursor(15,0);

	while(teclaPulsada!='o')
	{
		delay(delayPulsacion);
		teclaPulsada = leerTeclado();


		if((teclaPulsada == 'u') && (setDia<numeroDiasMes[setMes]))		//año ++
		{
			setDia++;
			lcd.setCursor(14,0);
			imprimirDigitosLCD(setDia);
			lcd.setCursor(15,0);
		}
		else if ((teclaPulsada =='d') && (setDia>1))		//año --
		{
			setDia--;
			lcd.setCursor(14,0);
			imprimirDigitosLCD(setDia);
			lcd.setCursor(15,0);
		}
		else if (teclaPulsada== 'c')			//cancelamos cambios
		{	
			lcd.clear();
			lcd.blink_off();
			lcd.print("Cancelado");
			delay(1000);
			return;
		}
	}


	//establecer hora y minutos
	teclaPulsada= '0';
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Hora:"); 

	lcd.setCursor(11,0);
	imprimirDigitosLCD(setHora);
	lcd.print(":");
	imprimirDigitosLCD(setMinutos);
	lcd.setCursor(12,0);
	
	//establecemos hora
	while(teclaPulsada!='o')		
	{
		delay(delayPulsacion);
		teclaPulsada = leerTeclado();
		if((teclaPulsada == 'u') && (setHora<23))		//hora ++
		{
			setHora++;
			lcd.setCursor(11,0);
			imprimirDigitosLCD(setHora);
			lcd.setCursor(12,0);
		}
		else if ((teclaPulsada =='d') && (setHora>0))		//hora --
		{
			setHora--;
			lcd.setCursor(11,0);
			imprimirDigitosLCD(setHora);
			lcd.setCursor(12,0);
		}
		else if (teclaPulsada== 'c')			//cancelamos cambios
		{	
			lcd.clear();
			lcd.blink_off();
			lcd.print("Cancelado");
			delay(1000);
			return;
		}
	}

	lcd.setCursor(0,0);
	lcd.print("Minuto:");

	lcd.setCursor(15,0);

	//establecer minutos
	teclaPulsada='0';
	while (teclaPulsada != 'o')
	{
		delay(delayPulsacion);
		teclaPulsada = leerTeclado();
		if((teclaPulsada == 'u') && (setMinutos<59))		//hora ++
		{
			setMinutos++;
			lcd.setCursor(14,0);
			imprimirDigitosLCD(setMinutos);
			lcd.setCursor(15,0);
		}
		else if ((teclaPulsada =='d') && (setMinutos>0))		//hora --
		{
			setMinutos--;
			lcd.setCursor(14,0);
			imprimirDigitosLCD(setMinutos);
			lcd.setCursor(15,0);
		}
		else if (teclaPulsada== 'c')			//cancelamos cambios
		{	
			lcd.clear();
			lcd.blink_off();
			lcd.print("Cancelado");
			delay(1000);
			return;
		}
	}

	//establecemos fehca y hora de la alarma
	ponerHoraAlarma(setDia,setMes,setAno,setHora,setMinutos,(uint8_t)0);
	
	
	lcd.clear();
	lcd.blink_off();
	

	//imprimimos en la linea 1 del lcd la fecha
	lcd.setCursor(3,0);
	imprimirDigitosLCD(setDia);
	lcd.print("/");
	imprimirDigitosLCD(setMes);
	lcd.print("/");
	imprimirDigitosLCD(setAno);


	//imprimimos en la linea 2 del lcd la hora
	lcd.setCursor(5,1);
	imprimirDigitosLCD(setHora);
	lcd.print(":");
	imprimirDigitosLCD(setMinutos);
	
	delay(2000);

	lcd.clear();
	lcd.print("alarma activa");
	delay(1000);

	
	teclaPulsada = '0';
}
*/

//bueno - para pner alarma directamente
void ponerHoraAlarma(uint8_t dia, uint8_t mes, int ano, uint8_t hora, uint8_t minutos, uint8_t segundos){
	tmElements_t tmSet;
	tmSet.Year = (ano - 1970);
	tmSet.Month = mes;
	tmSet.Day = dia;
	tmSet.Hour = hora;
	tmSet.Minute = minutos;
	tmSet.Second = 0;

	RTC.set(makeTime(tmSet), ALARM1_ADDRESS); // set the alarm for 4 seconds later
	RTC.enableAlarm(ALARM1_ADDRESS);
	
}


//devuelve 1 si el año es bisiesto, si no lo es devuelve 0
bool anoBisiesto(uint16_t ano){
	if(ano%4==0)	{			//si es bisiesto
		return 1;
	}
	else{						//si no es bisiesto
		return 0; 
	}
}




