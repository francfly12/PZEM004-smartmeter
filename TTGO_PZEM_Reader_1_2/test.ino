//  routines pour les test
void remplirdayly () {    // pour test, valeur sinusoidale
  Serial.println ("remplissage du tableau dayly");
  for ( float i = 0; i < 239; i++) {
  dayly [int(i)] =  int((sin (i/75)) *130) ;
  // Serial.print (i) ;
  // Serial.print (" ") ;
  Serial.print (dayly[int(i)]) ; 
   Serial.print (" ") ;          // pour vérifier
  } ;
  Serial.println();
  };
 void remplirweekly () { 
  Serial.println ("remplissage du tableau weekly");
  for ( float i = 0; i < 239; i++) {
  weekly [int(i)] =  int((sin (i/10)) *130) ;
  // Serial.print (i) ;
  Serial.print (" ") ;
  Serial.print (weekly[int(i)]) ;           // pour vérifier
  } ;
   Serial.println();
 } ;
void resetdayly () { 
  Serial.println ("reset du tableau dayly");
  for ( int i = 0; i < 240; i++) {
  dayly [i] =  0 ;
   } ;
  };
void resetweekly () { 
  Serial.println ("reset du tableau weekly");
  for ( int i = 0; i < 240; i++) {
  dayly [i] =  0 ;
   } ;
  };
 void afficherdayly () {
 for (int y=0; y <10; y++) { // afficher 10 lignes de 24 data
   for (int x=0; x<24; x++) {  // afficher une ligne
   int index_affichage = (x+(24*y)) ; //Serial.print (" i="); Serial.print(index_affichage); Serial.print(" ") ; 
   Serial.print (dayly [index_affichage]) ;Serial.print(" ");
    } ;
   Serial.println();  // fin de ligne
 }
 ;
 } 