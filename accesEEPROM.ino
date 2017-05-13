

//----------------------------------------------------------
//crea la matriz preestablecida por mi en la memoria eeprom
// y comprueba si se ha escrito bien
//----------------------------------------------------------
void EEPROMformatearArrayProgramacion(void)
{
	//se escribe en la eeprom
	int ptr = 0;
		
	//formatemaos las dos tablas horarioC1[6]  y  horarioC2[6]
	for(int tabla=0;tabla<2; tabla++){
		for (int columna=0; columna<6; columna++){
			EEPROM.write(ptr, (uint8_t)1);
			ptr++;		 

		}
	}

	EEPROM.write(ptr,'\r');
	
	//comprueba lo escrito
	ptr= 0;
	for(int tabla=0; tabla<2; tabla++){
		for(int columna = 0; columna<9; columna++){
			if( (uint8_t)1 != EEPROM.read(ptr)){
				avisoError(7);
			}
			ptr++;
		}		
	}
	if(EEPROM.read(ptr) != '\r'){
		avisoError(8);
	}

	lineas();
	Serial.println("los " +(String)ptr + "registros de EEPROM se pusieron a 1");
}

//----------------------------------------------------------
//leemos los valores de la programacion guardada en la eeprom
//esto se debe leer a cada reinicio o cuando marche la luz.
//----------------------------------------------------------
void leerProgramacionDeEEPROM(void)
{
	unsigned int ptr=0;
	
	//-----------------------------------------
	//guardamos circuito 1
	for(int columna=0; columna<6; columna++){
		horarioC1[columna]= EEPROM.read(ptr);
		ptr++;
	}

	lineas();
	Serial.println("Se leyeron " + (String)(ptr) + " registros de EEPROM del circuito 1");


	//-----------------------------------------
	//leemos circuito 2
	for(int columna=0; columna<6; columna++){
			horarioC2[columna]= EEPROM.read(ptr);
			ptr++;
		}

	lineas();
	Serial.println("Se leyeron " + (String)(ptr) + " registros de EEPROM del circuito 1");



}



//----------------------------------------------------------
//guarda la configuracion actual a la EEPROM 
//----------------------------------------------------------
void guardarProgramacionEnEEPROM(void){

	//se escribe en la eeprom
	int ptr = 0;

	//-----------------------------------------
	//guardamos circuito 1
	for (int columna=0; columna<6; columna++){
		EEPROM.write(ptr, horarioC1[columna]);
		ptr++;		 
	}
	
	lineas();
	Serial.println("Se guardaron " + (String)(ptr) + " registros en la EEPROM del circuito 1");

	//-----------------------------------------
	//guardamos circuito 2
	for (int columna=0; columna<6; columna++){
		EEPROM.write(ptr, horarioC2[columna]);
		ptr++;		 
	}
	
	lineas();
	Serial.println("Se guardaron " + (String)(ptr) + " registros en la EEPROM del circuito 2");
}


