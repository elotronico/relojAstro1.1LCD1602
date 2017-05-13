

/*
*				PARA MANEJAR EL MENU, SE UTILIZAN DOS COORDENADAS (X,Y) QUE SE VAN INCREMENTANDO O 
*				DECREMENTADO CON LOS PULSADORES.
*				
*				VARIABLES:
*				  - unsigned int menuPosX = 0;
*				  - unsigned int menuPosY = 0;
*				  - const int longMenuPpal=4;								//en realidad son 5 elementos (0,1,2,3,4)
*				  - int largoSubmenus[(longMenuPpal+1)]={4,6,5,6,4};		//valor [0]=4 pero en realidad son 5 elementos(0.0  0.1  0.2  0.3  0.4)
*						
*				LIBRERIAS NECESARIAS:
*				  #include <Wire.h>
*				  #include <LiquidCrystal_I2C.h>
*
*																			
*																			
*					
*
*		Menu 0.0 -------- Menu 1.0 -------- Menu 2.0 -------- Menu 3.0 -------- Menu 4.0		<------ MENU PRINCIPAL															
*			|				  |					|				  |					|			
*			|				  |					|				  |					|		    \
*		Menu 0.1 		  Menu 1.1 		   Menu 2.1 		  Menu 3.1 			 Menu 4.1		 |
*			|				  |					|				  |					|			 |
*			|				  |					|				  |					|			 |
*		Menu 0.2 		  Menu 1.3 		   Menu 2.3 		  Menu 3.3			 Menu 4.3		 |
*			|				  |					|				  |					|			 |
*			|				  |					|				  |					|			 |  <-- SUBMENUS
*		Menu 0.3 		  Menu 1.4 		   Menu 2.4 		  Menu 3.4			 Menu 4.4		 |
*			|				  |					|				  |								 |
*			|				  |					|				  |								 |
*		Menu 0.4 		  Menu 1.5 		   Menu 2.5 		  Menu 3.5							 |
*							  |									  |								 |
*							  |									  |								 |
						  Menu 1.6							  Menu 3.6	  						 |
*							  									  								/
*																			
*		
*/






//-----------------------------------------------------------------------
//- INTERPRETA LA TECLA PULSADA PARA ACTUALIZAR LA POSICION EN EL MENU --
//-----------------------------------------------------------------------
//	aqui mediante ifs averigua la posicion actual del menu (menuPosX,menuPosY)
//	y incrementa x o y segun corresponda. despues ejecuta actualizarMenuLcd() para
//	actulizar el texto en el lcd
void actualizarPosicionMenu(){
	#ifdef debug
	Serial.println("Cursor antes: " + (String)menuPosX + "," + (String)menuPosY);
	#endif

	//---------------  estamos en el menu principal -----------------
	if(menuPosY==0){	
		if((teclaPulsada== 'd') && (menuPosX<longMenuPpal)){
			#ifdef debug
			Serial.println("posx++");
			#endif
			if(menuPosX>0){
				menuPosX++;
			}			
		}
	
		else if((teclaPulsada== 'u') && (menuPosX>0)){
			#ifdef debug
			Serial.println("posx--");
			#endif
			if(menuPosX>1){
				menuPosX--;
			}
		}

		else if(teclaPulsada =='c'){
			menuPosX=0;
		}

		else if (teclaPulsada == 'o'){				
			//este if else es para evitar que el menu de la columna 0 este activo
			if(menuPosX==0){
				menuPosX++;
			}		
			else{
				menuPosY++;
			}
		}
	}

	//---------------- estamos en el submenu --------------------------
	else{		
		if((teclaPulsada=='d') && (menuPosY < largoSubmenus[menuPosX])){
			menuPosY++;
		}

		else if (teclaPulsada=='u' && menuPosY > 1){
			menuPosY--;
		}

		else if (teclaPulsada == 'c'){
			menuPosY=0;
		}
		
		else if (teclaPulsada == 'o'){
			accionMenu();
		}
	}

	#ifdef debug
	Serial.println("Cursor despues: " + (String)menuPosX + "," + (String)menuPosY);
	#endif

	actualizarMenuLcd();

}






//------------------------------------------------------------------------
//--   ESTO ACTUALIZA LO QUE SE MUESTRA EN EL LCD (MENU SELECCIONADO)  ---
//------------------------------------------------------------------------
//	mediante sentencias if compara menuPosX y menuPosY y imprime en el lcd
//	el texto que corresponda a cada menu.
//	
void actualizarMenuLcd()
{
	lcd.clear();

	//--------------MENU 0---------------------------
	if(menuPosX == 0){	//menu ppal
		if(menuPosY==0){							//menu 0.0
			actualizarPantallaPpalLCD();
		}

		else{
			avisoError(1);
		}
	}

	//--------------MENU 1---------------------------
	else if(menuPosX == 1){	//menu ppal
		if(menuPosY==0){						//menu 1.0

			lcd.print(" >Reloj");
			lcd.setCursor(0,1);
			lcd.print("  Programacion");

		}
		
		else if(menuPosY==1){				//menu 1.1
			lcd.print(" >Cambiar hora");
			lcd.setCursor(0,1);
			lcd.print("  Cambiar Fecha");

		}
		
		else if(menuPosY==2){				//menu 1.2
			lcd.print("  Cambiar hora");
			lcd.setCursor(0,1);
			lcd.print(" >Cambiar Fecha");

		}
		
		else{
			avisoError(2);
		}

	}

	//--------------MENU 2---------------------------
	else if(menuPosX == 2){			//menu ppal
		if (menuPosY==0){			//menu 2.0
			lcd.print("  Reloj");
			lcd.setCursor(0,1);
			lcd.print(" >Programacion");
			lcd.setCursor(0,2);
	
		}

		else if(menuPosY== 1){
			mostrarPrograma1();
		}
		
		else if(menuPosY== 2){
			mostrarPrograma2();
		}

		else{
			avisoError(3);
		}
	}
	/*
	//--------------MENU 3---------------------------
	else if(menuPosX == 3){					//menu ppal
		if	(menuPosY==0){				//menu 3.0
			lcd.print("1  Reloj");
			lcd.setCursor(0,1);
			lcd.print("2  Programacion");
			lcd.setCursor(0,2);

		}
		
		else if(menuPosY==1){				//menu 3.1
			lcd.print("3.1 >Zona horaria");
			lcd.setCursor(0,1);
			lcd.print("3.2  Coordenadas");
			lcd.setCursor(0,2);
			lcd.print("3.3  Reset fabrica");
		}
		
		else if(menuPosY==2){				//menu 3.2		
			lcd.print("3.1  Zona horaria");
			lcd.setCursor(0,1);
			lcd.print("3.2 >Coordenadas");
			lcd.setCursor(0,2);
			lcd.print("3.3  Reset fabrica");
		}
		else if(menuPosY==3){				//menu 3.2		
			lcd.print("3.1  Zona horaria");
			lcd.setCursor(0,1);
			lcd.print("3.2  Coordenadas");
			lcd.setCursor(0,2);
			lcd.print("3.3 >Reset fabrica");
		}
		
		else{
			avisoError(4);
		}
	}

	//--------------MENU 4---------------------------
	else if(menuPosX == 4){	//menu ppal
		if	   (menuPosY==0){			//menu 4.0
			lcd.print("1  Reloj");
			lcd.setCursor(0,1);
			lcd.print("2  Programacion");
			lcd.setCursor(0,2);
			lcd.print("3  Ajustes");
			lcd.setCursor(0,3);
			lcd.print("4 >Tests");
		}
		
		else if(menuPosY==1){			//menu 4.1
			lcd.print("4.1 >guardar tabla");
			lcd.setCursor(0,1);
			lcd.print("4.2  leer tabla");
			lcd.setCursor(0,2);
			lcd.print("4.3  format tabla");
			lcd.setCursor(0,3);
			lcd.print("4.3  vacio");
		}

		else if(menuPosY==2){			//menu 4.2
			lcd.print("4.1  guardar tabla");
			lcd.setCursor(0,1);
			lcd.print("4.2 >leer tabla");
			lcd.setCursor(0,2);
			lcd.print("4.3  format tabla");
			lcd.setCursor(0,3);
			lcd.print("4.3  vacio");
		}

		else if(menuPosY==3){			//menu 4.3
			lcd.print("4.1  guardar tabla");
			lcd.setCursor(0,1);
			lcd.print("4.2  leer tabla");
			lcd.setCursor(0,2);
			lcd.print("4.3 >format tabla");
			lcd.setCursor(0,3);
			lcd.print("4.3  vacio");
		}
		
		else if(menuPosY==4){			//menu 4.3
			lcd.print("4.1  guardar tabla");
			lcd.setCursor(0,1);
			lcd.print("4.2  leer tabla");
			lcd.setCursor(0,2);
			lcd.print("4.3  format tabla");
			lcd.setCursor(0,3);
			lcd.print("4.3 >vacio");
		}

		else{		
			avisoError(5);
		}
	}*/

	else{	
		avisoError(6);
	}

}






//------------------------------------------------------------------------
//----						ACCIONES DEL MENU						  ----
//------------------------------------------------------------------------
//acciones de los menus
void accionMenu()
{
	//--------------MENU 1---------------------------
	if(menuPosX==1){		
		if (menuPosY==1){				//Submenu 1.1 - poner en hora el reloj
			RTCponerEnHoraLCD();		
		}		
		else if(menuPosY ==2){			//Submenu 1.2 - cambiar fecha
			RTCponerEnFechaLCD();			
		}
	}


	//--------------MENU 2---------------------------
	else if(menuPosX==2){
		
		if(menuPosY==1){
			editarPrograma1();		//accedemos a editar la programacion horaria (que corresponde con menuPosY)
		}
		else if(menuPosY==2){
			editarPrograma2();		//accedemos a editar la programacion horaria (que corresponde con menuPosY)
		}

	}

	/*
	//--------------MENU 3---------------------------
	else if(menuPosX==3){
		if(menuPosY==1){				//submenu 3.1
			cambiarZonaHoraria(); 
		}
		else if(menuPosY==2){				//submenu 3.2
		 
		}

		else if(menuPosY==3){				//submnu 3.3
			
				

		}

	}

	//--------------MENU 4---------------------------

		else if(menuPosX==4){
			if(menuPosY==1){				//submenu 3.1
				guardarProgramacionEnEEPROM();
			}
			else if(menuPosY==2){				//submenu 3.2
				leerProgramacionDeEEPROM();
			}

		
			else if(menuPosY==3){				//submenu 3.2
				EEPROMformatearArrayProgramacion();
			}

		}
		*/

}





