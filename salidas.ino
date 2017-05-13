

//desactiva la salida del valor que recibe
void activarSalida(uint8_t salida){

	if(salida <=3){
	//Serial.println("salida " + (String)salida + " actviada");
		
		if(salida==1)
			StateS1=HIGH;
		else if(salida==2)
			StateS2=HIGH;
		else if(salida==3)
			StateS3=HIGH;
	 }
}


//activa la salida del valor que recibe
void desactivarSalida(uint8_t salida){

	if(salida <=8){
	//Serial.println("salida " + (String)salida + " desactviada");

		if(salida==1)
			StateS1=LOW;
		else if(salida==2)
			StateS2=LOW;
		else if(salida==3)
			StateS3=LOW;
	}
}


//-----------------------------------------------
//actualiza el estado de las salidas
//escribe 0 o 1 segun corresponda
//-----------------------------------------------
void refrescarSalidas(){

		if(StateS1==HIGH){
			digitalWrite(salida1,HIGH);
		}
		else{
			digitalWrite(salida1,LOW);
		}
//----------------		
		if(StateS2==HIGH){
			digitalWrite(salida2,HIGH);
		}
		else{
			digitalWrite(salida2,LOW);
		}
//----------------
		if(StateS3==HIGH){
			digitalWrite(salida3,HIGH);
		}
		else{
			digitalWrite(salida3,LOW);
		}


}


void enviaSerialEstadoSalidas(void){


	lineas();
	Serial.println("       ESTADO DE SALIDAS   ");
	lineas();


		Serial.print("Salida 1: ");
		if(StateS1==HIGH){
			Serial.println("Activa");
		}
		else{
			Serial.println("Inactiva");
		}

		//------------
		Serial.print("Salida 2: ");
		if(StateS2==HIGH){
			Serial.println("Activa");
		}
		else{
			Serial.println("Inactiva");
		}

		//------------
		Serial.print("Salida 3: ");
		if(StateS3==HIGH){
			Serial.println("Activa");
		}
		else{
			Serial.println("Inactiva");
		}


		lineas();
		Serial.println("");

}