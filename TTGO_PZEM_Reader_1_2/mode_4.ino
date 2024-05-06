void mode4 ()
{
   // Reset compteur Kwh
    
     tft.fillScreen(ST77XX_BLACK); // efface l'écran
      // affichage cadre blanc
     tft.drawRect (0,0,240,135,WHITE) ;       // cadre
     tft.setFont();       // revient aux font de base
     tft.setTextSize(3);  // 
     tft.setCursor(6,4);      tft.setTextColor(WHITE);  tft.print(" RESET Kwh ?");
     tft.setTextSize(2);  //
     tft.setCursor(90,50);    tft.setTextColor(GREEN,BLACK);  tft.print(energy,3);
     tft.setCursor(190,50);      tft.setTextColor(BLUE);  tft.print("Kwh");
     tft.setTextSize(3);  //
     tft.setCursor (20,80);   tft.setTextColor(RED) ;   tft.print("Appuyer pour  reset    ->") ;
     delay (2000); 
      if (digitalRead(0) == LOW) {
          pzem.resetEnergy();
        delay(1000);

      }

   // affichage cadre blanc
   tft.drawRect (0,0,240,135,WHITE) ;       // cadre
        
}