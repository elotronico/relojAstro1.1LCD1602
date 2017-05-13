
//edita la programacion horaria correspondiente a menuposy-1
void mostrarPrograma1(){		//imprimimos el numero de programa que coincide con la pos en menuposy
	
			//delay(delayPulsacion);

			lcd.clear();
			lcd.print("Voluntario 1 ");
			
			//si  esta programacion horaria esta DESACTIVADA
			if(enC1==0){		
				lcd.print("OFF");
			}


			//si  esta programacion horaria esta ACTIVADA
			else if (enC1==1){
				lcd.print("ON");

				lcd.setCursor(1,1);
				lcd.print("Ocaso - ");

				imprimirDigitosLCD(horaOffc1);
				lcd.print(":");
				imprimirDigitosLCD(minutoOffc1);
			}

			//si hay cualquier otro valor es porque hay un ERROR
			else {
				avisoError(10);
			}						
}


void mostrarPrograma2(){

		
			//delay(delayPulsacion);

			lcd.clear();
			lcd.print("Voluntario 2 ");
			
			//si  esta programacion horaria esta DESACTIVADA
			if(enC2==0){		
				lcd.print("OFF");
			}


			//si  esta programacion horaria esta ACTIVADA
			else if (enC2==1){
				lcd.print("ON");


				lcd.setCursor(1,1);				
				imprimirDigitosLCD(horaOnC2);
				lcd.print(":");
				imprimirDigitosLCD(minutoOnC2);

				lcd.print(" - Orto");

				
								
				//si hay cualquier otro valor es porque hay un ERROR
			}

			//si hay cualquier otro valor es porque hay un ERROR
			else {
				avisoError(10);
			}	



}


//edita la programacion horaria correspondiente a menuposy-1
void editarPrograma2(){		
		
	//----------- modificamos on off -------------------
	lcd.setCursor(13,0);		
	lcd.blink_on();
	
	//e//teclaPulsada='0';
	//e//delay(delayPulsacion);

	//minentras no pulsemos ok
	while(teclaPulsada != 'o'){

		teclaPulsada = leerTeclado();	
		

		if((teclaPulsada =='u') | (teclaPulsada == 'd')){
			
			if(enC2==0){			//si el horario esta habilitado
				enC2=1;				//lo deshabilitamos
			}
			else if(enC2==1){	//si el horario esta deshabilitado
				enC2=0;			//lo habilitamos
			}

			//e//teclaPulsada = '0';	
			mostrarPrograma2();
			lcd.setCursor(13,0);		
			//e//delay(delayPulsacion);
		}
	}

	//e//delay(delayPulsacion);
	//e//teclaPulsada='0';

		
	//----------- si es por hora fija --> elegimos a que hora queremos que actue -------------------
	if(enC2==1){
		lcd.setCursor(1,1);

		//establecemos hora
		while(teclaPulsada!='o'){
				//e//delay(delayPulsacion);
				teclaPulsada = leerTeclado();
				if((teclaPulsada == 'u') & (horaOnC2<23)){			//hora ++
					horaOnC2++;
					lcd.setCursor(1,1);
					imprimirDigitosLCD(horaOnC2);
					lcd.setCursor(1,1);
				}
				else if ((teclaPulsada =='d') & (horaOnC2>0)){		//hora --
					horaOnC2--;
					lcd.setCursor(1,1);
					imprimirDigitosLCD(horaOnC2);
					lcd.setCursor(1,1);
				}				
			}

			lcd.setCursor(4,1);


			//establecer minutos
			//e//teclaPulsada='0';
			while (teclaPulsada != 'o')	{
				//e//delay(delayPulsacion);
				teclaPulsada = leerTeclado();
				if((teclaPulsada == 'u') && (minutoOnC2<59)){			//minutos ++
					minutoOnC2++;
					lcd.setCursor(4,1);
					imprimirDigitosLCD(minutoOnC2);
					lcd.setCursor(4,1);
				}
				else if ((teclaPulsada =='d') && (minutoOnC2>0)){		//minutos --
					minutoOnC2--;
					lcd.setCursor(4,1);
					imprimirDigitosLCD(minutoOnC2);
					lcd.setCursor(4,1);
				}
			}
	
			mdiarioC2=(horaOnC2*60)+minutoOnC2;	
	}
			
	//--------------- salimos -----------------------
	//e//teclaPulsada='0';
	//e//delay(delayPulsacion);
	//guardarProgramacionEnEEPROM();
	
	lineas();
	Serial.println("Programacion Modificada");
	siHayInterrupcion();		//comprobamos si hay que actuar sobre alguna salida con la nueva programacion
	//e//teclaPulsada='0';

	lcd.blink_off();


}


//edita la programacion horaria correspondiente a menuposy-1
void editarPrograma1(){		
		
	Serial.println("editar prog 1");
	//----------- modificamos on off -------------------
	lcd.setCursor(13,0);		
	lcd.blink_on();
	
	//e//teclaPulsada='0';
	//e//delay(delayPulsacion);

	//minentras no pulsemos ok
	while(teclaPulsada != 'o'){

		teclaPulsada = leerTeclado();	
		

		if((teclaPulsada =='u') | (teclaPulsada == 'd')){
			
			if(enC1==0){			//si el horario esta habilitado
				enC1=1;			//lo deshabilitamos
			}
			else if(enC1==1){	//si el horario esta deshabilitado
				enC1=0;			//lo habilitamos
			}

			teclaPulsada = '0';	
			mostrarPrograma1();
			lcd.setCursor(13,0);		
			//e//delay(delayPulsacion);
		}
	}

	//e//delay(delayPulsacion);
	//e//teclaPulsada='0';

		
	//----------- si es por hora fija --> elegimos a que hora queremos que actue -------------------
	if(enC1==1){
		lcd.setCursor(9,1);

		//establecemos hora
		while(teclaPulsada!='o'){
				//e//delay(delayPulsacion);
				teclaPulsada = leerTeclado();
				if((teclaPulsada == 'u') & (horaOffc1<23)){		//hora ++
					horaOffc1++;
					lcd.setCursor(9,1);
					imprimirDigitosLCD(horaOffc1);
					lcd.setCursor(9,1);
				}
				else if ((teclaPulsada =='d') & (horaOffc1>0)){		//hora --
					horaOffc1--;
					lcd.setCursor(9,1);
					imprimirDigitosLCD(horaOffc1);
					lcd.setCursor(9,1);
				}				
			}

			lcd.setCursor(4,1);


			//establecer minutos
			//e//teclaPulsada='0';
			while (teclaPulsada != 'o')	{
				//e//delay(delayPulsacion);
				teclaPulsada = leerTeclado();
				if((teclaPulsada == 'u') && (minutoOffc1<59)){		//minutos ++
					minutoOffc1++;
					lcd.setCursor(12,1);
					imprimirDigitosLCD(minutoOffc1);
					lcd.setCursor(12,1);
				}
				else if ((teclaPulsada =='d') && (minutoOffc1>0)){		//minutos --
					minutoOffc1--;
					lcd.setCursor(12,1);
					imprimirDigitosLCD(minutoOffc1);
					lcd.setCursor(12,1);
				}
			}
	
			mdiarioC1=(horaOffc1*60)+minutoOffc1;	
	}
			
	//--------------- salimos -----------------------
	//e//teclaPulsada='0';
	//e//delay(delayPulsacion);
	guardarProgramacionEnEEPROM();
	
	lineas();
	Serial.println("Programacion Modificada");
	siHayInterrupcion();		//comprobamos si hay que actuar sobre alguna salida con la nueva programacion
	//e//teclaPulsada='0';

	lcd.blink_off();
		
}



//sin desarrollar
void cambiarCoordenadasGeograficas(void){
	

}



//sin desarrollar
void establecerCiudad(void){

}

//sin desarrollar
void cambiarZonaHoraria(void){

}




