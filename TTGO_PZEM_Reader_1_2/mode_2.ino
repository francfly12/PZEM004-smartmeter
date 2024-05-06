void mode2 ()
{  // Serial.println ("affichage mode 2 ") ;
   // affichage dayly graphique / 24 heures
  // daylyindex ++ ;  // TEST ONLY
  // if (daylyindex > 239) { daylyindex = 0 ;} ;  
  if (modechange != mode) {        // si il y a changement du mode d'affichage ...
    tft.fillScreen(ST77XX_BLACK); // efface l'écran
       // modechange = mode ;            // ca y est, le mode est changé !  
  } ;
  // effacement zone graphique
    tft.drawRect (2,2,237,132,BLACK) ;       // 
    for (int i=239 ; i > 0 ; i--) {   // affiche de droite à gauche
   // for (int i=0 ; i < 239 ; i++) {   // affiche de gauche à droite
   if ((i + daylyindex) > 239) {shift = -240; } else { shift = 0 ;} ;
   tableindex = i + daylyindex + shift ;
   // Serial.print(tableindex) ; Serial.print (" : ") ; 
   // Serial.print (i) ; Serial.print (" = ") ;Serial.println (134-(dayly[tableindex])) ;  // TEST only
   tft.drawLine (i,134,i,(134-(dayly[tableindex])),BLUE) ;
   // Serial.print (i) ; Serial.print (" : ") ;Serial.println (133-(dayly[tableindex])) ;  // TEST only
   } ; 
   Serial.println ();
      // affichage cadre blanc
   tft.drawRect (0,0,240,136,WHITE) ;       // cadre
  for (int16_t y = 11; y < 240; y += 10) {  // petites barres
  tft.drawLine (y,120,y,134, WHITE) ;

   for (int16_t y = 40; y < 240; y += 40) {  // grandes barrees
  tft.drawLine (y,110,y,134, WHITE) ; 
   };
   tft.drawLine (120,100,120,134, WHITE) ; 

   tft.setFont();       // revient aux font de base
     tft.setTextSize(3);  // 
     tft.setCursor(6,4);      tft.setTextColor(GREEN);  tft.print("24 Heures");
  // defaut en y =70
  /*
  y = 70;
  tft.drawLine (y-1,10,y-1,134, WHITE) ;
  tft.drawLine (y,10,y,134, WHITE) ;
  tft.drawLine (y+1,10,y+1,134, WHITE) ;
  */
  };    
    delay (5000);

}
