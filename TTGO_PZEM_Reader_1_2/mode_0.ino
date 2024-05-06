void mode0 ()
{  
   // mode 0 : affichage simple Power + energy
      if (modechange != mode) {        // si il y a changement du mode d'affichage ...
      tft.setFont(&FreeSans18pt7b);  // large fonts
      tft.fillScreen(ST77XX_BLACK);  // efface l'écran
      tft.setTextSize(1);  // une seule taille existe pour cette fonte
      tft.setCursor(0,28);      tft.setTextColor(WHITE);  tft.print("Power");
      tft.setCursor(200,28);      tft.setTextColor(BLUE);  tft.print("W");
      tft.setCursor(0,70);      tft.setTextColor(WHITE);  tft.print("Energy");
       tft.setCursor(170,115);      tft.setTextColor(BLUE);  tft.print("Kwh");
       oldpower = 5000 ; oldenergy = 5000 ; // pour obliger reset de l'affichage des valeurs, valeurs au hasard
      modechange = mode ;            // ca y est, le mode est changé !
      }
      // affichage normal
      newpower = power ;
      if (oldpower != newpower) {
      tft.fillRect(102,1,94,34,BLACK); // efface la zone sous la valeur power
      tft.setCursor(110,28);    tft.setTextColor(GREEN);  tft.print(power,0);
      oldpower = newpower ;
       }  ;   
       newenergy = energy ; 
      if (oldenergy != newenergy) {
       tft.fillRect(1,88,170,34,BLACK); // efface la zone sous la valeur energy
      tft.setCursor(70,115);    tft.setTextColor(GREEN);  tft.print(energy,3);
       oldenergy = newenergy ;
       } ;
}


