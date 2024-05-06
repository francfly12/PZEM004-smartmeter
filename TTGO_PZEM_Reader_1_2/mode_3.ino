void mode3 ()
{
   // affichage sur 10 jours / 240 barres = 1/heure = 10 jours
  
  if (modechange != mode) {        // si il y a changement du mode d'affichage ...
    tft.fillScreen(ST77XX_BLACK); // efface l'écran
     tft.setFont();       // revient aux font de base
     tft.setTextSize(3);  // 
     tft.setCursor(6,4);      tft.setTextColor(GREEN);  tft.print("10 Jours");
 
     modechange = mode ;            // ca y est, le mode est changé !  
  } ;
  for (int i=238 ; i > 0 ; i--) {   // affiche de droite à gauche
    tft.drawLine (i,134,i,(134-(weekly[i])),BLUE) ;
   } ;
   // affichage cadre blanc
   tft.drawRect (0,0,240,136,WHITE) ;       // cadre
  for (int16_t y = 1; y < 240; y += 24) {  // petites barres
  tft.drawLine (y,120,y,134, WHITE) ;
    };
   
   
  // defaut en y =70
  /*
  y = 70;
  tft.drawLine (y-1,10,y-1,134, WHITE) ;
  tft.drawLine (y,10,y,134, WHITE) ;
  tft.drawLine (y+1,10,y+1,134, WHITE) ;
  */

      
}
// note: affichage a revoir, en fonction de l index  