// Example by Nick Gammon
// http://forum.arduino.cc/index.php?topic=129249.msg972860#msg972860



//----------------------------------------------------------------------------------
//calcula orto y ocaso de la fecha entregada y guarda los datos en tablaOrtoOcaso[]
//----------------------------------------------------------------------------------
void calculoOrtoOcaso(uint8_t dia, uint8_t mes, int ano)
  {
	byte today[] = {  0, 0, 12, 01, 02 ,2016  };		// store today's date (at noon) in an array for TimeLord to use
   	
	today[3]=dia;	
	today[4]=mes;	
	today[5]=ano;	

	TimeLord tardis; 
	tardis.TimeZone(zonaHoraria * 60);			// tell TimeLord what timezone your RTC is synchronized to. You can ignore DST
	
	// as long as the RTC never changes back and forth between DST and non-DST
	tardis.Position(LATITUDE, LONGITUDE); // tell TimeLord where in the world we are

	//calculamos hora orto (amanece)
	tardis.SunRise(today);
	horaAmanece = today[tl_hour];
	minutoAmanece = today[tl_minute];
	mdiarioAmanece = (horaAmanece*60)+minutoAmanece;

	//calculamos hora ocaso (anochece)
	tardis.SunSet(today);
	horaAnochece = today[tl_hour];
	minutoAnochece = today[tl_minute];
	mdiarioAnochece = (horaAnochece*60)+minutoAnochece;



}
  
