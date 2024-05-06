
void action6minutes () { // a faire toute les 6 minutes
// il faut calculer la difference d energie et la stocker dans le tableau dayly
// dayly stocke des valeurs en pixels (0 à 135)
// variables oldindex, newindex en float, delta a mettre dans le tableau dayly en int

newindex = pzem.energy();                   // lire nouvelle valeur, c'est d'abord un float avec 3 decimales
deltaindex = newindex - oldindex ;          // calcul différence
// Serial.print("newindex="); Serial.println(newindex,3);
// Serial.print("oldindex="); Serial.println(oldindex,3);
oldindex = newindex ;                       // on remet le nouveau dans le vieux
// Serial.print("deltaindex="); Serial.print(deltaindex,3);
deltaindexI = deltaindex * 1000 ;     // transforme en fois 1000 pour ne pas perdre les décimales
//Serial.print(" deltaindexI="); Serial.print(deltaindexI);
deltaindexI = int((deltaindexI * 135) / 300) ; // transforme en valeur d'affichage
// Serial.print(" puis devient= "); Serial.println(deltaindexI);
// Serial.print("daylyindex = "); Serial.println(daylyindex);
dayly [daylyindex] = deltaindexI  ;          // on met la valeur convertie dans la table dayly à la position daylyindex
// Serial.print("reading dayly [daylyindex] = "); Serial.println(dayly [daylyindex] );
// 
daylyindex ++ ; 
if (daylyindex > 239 ) { daylyindex = 0 ; } // rebouclage
// Serial.println("storage"); 
// Serial.print("daylyindex = "); Serial.println(daylyindex);
// Serial.print("dayly [daylyindex] = "); Serial.println(dayly [(daylyindex-1)] );
Serial.println("6 minutes ! ========================================================");
  ;};   

void action1heure () { // a faire toute les heures
// il faut calculer la difference d energie et la stocker dans le tableau weekly, qui contient en fait dix jours de données horaires
// modifier les index

newindex_horaire = pzem.energy();                   // lire nouvelle valeur
deltaindex_horaire = newindex_horaire - oldindex_horaire ;          // calcul différence
oldindex_horaire = newindex_horaire ;                       // on remet le nouveau dans le vieux
deltaindexI_horaire = int (deltaindex_horaire * 1000) ;     // transforme en entier fois 1000 pour ne pas perdre les décimales
weekly [weeklyindex] = ((deltaindexI_horaire * 135) / 3000) ;          // on met la valeur convertie dans la table dayly à l'index 
weeklyindex ++ ; 
if (weeklyindex > 239 ) { weeklyindex = 0 ; } // reset de l'index
Serial.println("1 heure ! ******************************************************");
  ;};

void action10jours () { // a faire tous les 10 jours 
 // modifier les index
// rien de spécial ... en fait
}
void interrupt_bouton1 () { // appui sur bouton du bas
   //    Serial.println ("interrupt 1") ;
   // en fait rien, est utilisé pour le reset
    
   } ;
void interrupt_bouton2 () {
   // Serial.println ("interrupt 2") ;
     mode ++ ;   if (mode == 5) {mode = 0;} ;
     Serial.print ("mode = ") ;
     Serial.println (mode) ;
   } ;


/*
note : on considère l'affichage pleine barre (135 pixels) pour une production de 3000 W = 3Kwh, soit en 6 minutes 0,3Kwh
D'ou un facteur de conversion K  ;   Valeur_en_pixels = K x (deltaindex)
                              K = 1000 * (135/300)   pour dayly
                              et K = 1000 * (135/3000) pour weekly

Boutons :
void handler(Button2& btn) {
    switch (btn.getType()) {
        case single_click:
            break;
        case double_click:
            Serial.print("double ");
            break;
    }
    Serial.print("click ");
    Serial.print("on button #");
    Serial.print((btn == button_1) ? "1" : "2");
    Serial.println();
}
*/