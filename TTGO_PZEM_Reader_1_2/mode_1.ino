void mode1 ()
{
   // affichage detaillé Power + energy + current + data...
      if (modechange != mode) {        // si il y a changement du mode d'affichage ...
     tft.fillScreen(ST77XX_BLACK); // pas necessaire
     tft.setFont();       // revient aux font de base
     tft.setTextSize(2);  // 
     tft.setCursor(0,16);      tft.setTextColor(WHITE);  tft.print("Power");
     tft.setCursor(195,16);      tft.setTextColor(BLUE);  tft.print("W");
     tft.setCursor(0,32);      tft.setTextColor(WHITE);  tft.print("Voltage");
     tft.setCursor(195,32);      tft.setTextColor(BLUE);  tft.print("V");
     tft.setCursor(0,48);      tft.setTextColor(WHITE);  tft.print("Current");
     tft.setCursor(195,48);      tft.setTextColor(BLUE);  tft.print("A");      
     tft.setCursor(0,64);      tft.setTextColor(WHITE);  tft.print("Frequency");
     tft.setCursor(195,64);      tft.setTextColor(BLUE);  tft.print("Hz");      
     tft.setCursor(0,80);      tft.setTextColor(WHITE);  tft.print("Energy");
     tft.setCursor(195,80);      tft.setTextColor(BLUE);  tft.print("Kwh");
     tft.setCursor(0,96);      tft.setTextColor(WHITE);  tft.print("Pwr fact");
     tft.setCursor(195,96);      tft.setTextColor(BLUE);  tft.print("");

    // tft.fillRect(110,1,80,133,BLACK); // efface la zone sous les valeurs
     modechange = mode ;            // ca y est, le mode est changé !
      } ;

     tft.setCursor(115,16);    tft.setTextColor(GREEN,BLACK);  tft.print("      ");
     tft.setCursor(115,16);    tft.setTextColor(GREEN,BLACK);  tft.print(power,0);
     tft.setCursor(115,32);    tft.setTextColor(GREEN,BLACK);  tft.print("      ");
     tft.setCursor(115,32);    tft.setTextColor(GREEN,BLACK);  tft.print(voltage,2);
     tft.setCursor(115,48);    tft.setTextColor(GREEN,BLACK);  tft.print("      ");
     tft.setCursor(115,48);    tft.setTextColor(GREEN,BLACK);  tft.print(current,2);
     tft.setCursor(115,64);    tft.setTextColor(GREEN,BLACK);  tft.print("      ");
     tft.setCursor(115,64);    tft.setTextColor(GREEN,BLACK);  tft.print(frequency,2);
     tft.setCursor(115,80);    tft.setTextColor(GREEN,BLACK);  tft.print("      ");
     tft.setCursor(115,80);    tft.setTextColor(GREEN,BLACK);  tft.print(energy,3);
     tft.setCursor(115,96);    tft.setTextColor(GREEN,BLACK);  tft.print("      ");
     tft.setCursor(115,96);    tft.setTextColor(GREEN,BLACK);  tft.print(pf,2);      
 
}

