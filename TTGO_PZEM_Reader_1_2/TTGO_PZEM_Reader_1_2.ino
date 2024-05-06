/**************************************************
PZEM reader by FSA
uses one PZEM module with Hardware Serial interface.
display on lilygo T-Display
===================================================
Hardware :
PZEM004T connected to pin GPIO26 (TX) and pin GPIO27 (RX)
plus power supply (5V/GND)
signals compatibility Ok, no voltage shift  
===================================================
Includes libraries from Adafruit and Jakub Mandula
*/

//Librairies
#include <PZEM004Tv30.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <Fonts/FreeSans18pt7b.h>

	

// graphic display :
// pinouts from https://github.com/Xinyuan-LilyGO/TTGO-T-Display
#define TFT_MOSI 19
#define TFT_SCLK 18
#define TFT_CS 5
#define TFT_DC 16
#define TFT_RST 23
#define TFT_BL 4
#define BUTTON_PIN_1  0   // bouton du bas
#define BUTTON_PIN_2  35  // bouton du haut
// constructor for data object named tft 
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

#if !defined(PZEM_RX_PIN) && !defined(PZEM_TX_PIN)
#define PZEM_RX_PIN 26
#define PZEM_TX_PIN 27
#endif
#if !defined(PZEM_SERIAL)
#define PZEM_SERIAL Serial2
#endif

/*************************
 *  ESP32 initialization
 * ---------------------
 * The ESP32 HW Serial interface can be routed to any GPIO pin 
 * Here we initialize the PZEM on Serial2 with RX/TX pins 16 and 17
 */

PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);

// definition of variables 
// data from the sensor
    float voltage;
    float current ;
    float power ;
    float energy ;
    float frequency ;
    float pf ;
// affichage
    int mode = 0; // which screen mode is displayed    //  mode 0 = Normal / 1=detail / 2=24 hours / 3=10 jours / 4 = reset 
    int modechange = 10; // indique si il y a eu un changement de mode d affichage, 
                        // modechange deviendra égal a mode ensuite. Ici mis à 10 pour changer l affichage au démarrage
// display rotation
uint8_t rotation = 3 ;    // 3 pour mode paysage, USB a droite
// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF
// variables diverses
int dayly[240] ;        // tableau de 240 valeurs toute les 6 minutes pour affichage journalier
int weekly[240] ;       // tableau de 240 valeurs pour affichage"weekly", en fait sur 10 jours, 1 variable par heure, 10 variables par 24 heures 
int daylyindex = 0;     // pour indexer le tableau dayly (position de lecture/écriture)
int weeklyindex = 0;    // pour indexer le tableau weekly
int tableindex= 0;      // index utilisé pour l'affichage du tableau
int shift = 0 ;         // utilisé dans mode2 pour le calcul d'index du tableau
float oldindex = 0;        // valeur de l'index de lecture d énergie. C est un"float"  Sera converti en Int pour le stocker dans le tableau dayly et en faire des valeurs de pixels (0 à 135)
float newindex = 0;        // valeur de l'index de lecture d énergie. C est un"float"  idem ...
float deltaindex = 0;      // difference entre ancien et nouvel index
int deltaindexI = 0;       // valeur corespondante EN ENTIERS de deltaindex, multipliée par MILLE , pour avoir une valeur cohérente et ne pas perdre les décimales

float oldindex_horaire = 0;        // valeur de l'index horaire de lecture d énergie. C est un"float"  Sera converti en Int pour le stocker dans le tableau weekly et en faire des valeurs de pixels (de 0 à 135)
float newindex_horaire = 0;        // valeur de l'index horaire de lecture d énergie. C est un"float"  idem ...
float deltaindex_horaire = 0;      // difference entre ancien et nouvel index
int deltaindexI_horaire = 0;       // valeur corespondante EN ENTIERS de deltaindex, multipliée par MILLE , pour avoir une valeur cohérente et ne pas perdre les décimales

float oldpower = 1, newpower = 0 ;  // pour tester les changements dans mode 0
float oldenergy = 1, newenergy = 0 ; // doivent etre différents pour le premier affichage
//Internal Timers
unsigned long startmillis;
unsigned long oldmillis;
unsigned long newmillis;
unsigned long timer6minutes = 0 ; // incremente toute les 6 minutes
unsigned long timerheures = 0 ; // incremente toute les heures
unsigned long timer10jours = 0 ; // incremente tous les 10 jours
// Bouton positionnés en pin number 0 et35:
const int button1 = 0;  // the number of the pushbutton pin
const int button2 = 35;  // 
// variables boutons:
int buttonState1 = 0;  // variable pour l etat du bouton 1
int buttonState2 = 0;  // variable pour l'état du bouton 2

// SETUP
//*******
void setup() {
    // Debugging Serial port
  Serial.begin(115200);
   delay(600);
    pinMode(TFT_BL, OUTPUT);      // TTGO T-Display enable Backlight pin 4
  digitalWrite(TFT_BL, HIGH);   // T-Display turn on Backlight
  tft.init(135, 240);           // Initialize ST7789 240x135
  tft.setRotation(rotation);
  tft.setFont(&FreeSans18pt7b);  // large fonts
  Serial.println(F("*** DEMARRRAGE ***"));
   attachInterrupt(digitalPinToInterrupt(button1), interrupt_bouton1, RISING);  // interruption bouton 1 
    attachInterrupt(digitalPinToInterrupt(button2), interrupt_bouton2, RISING); // interruption bouton 2

    // Uncomment in order to reset the internal energy counter
    // pzem.resetEnergy()
    tft.fillScreen(ST77XX_BLACK); //  car il reste toujours des pixels allumés
startmillis = millis();           // initialise le timer 
oldmillis = startmillis ; 
  resetdayly () ;                 // reset tableau
  resetweekly () ;                // reset tableau 
  // remplirdayly () ;                 // pour test uniquement, remplir tableau avec une sinusoide
  // remplirweekly ();                 // idem
   mode = 0 ;
  
 }


// LOOP
//*******
void loop() {
    // Print the custom address of the PZEM
   // Serial.print("Custom Address:");
   // Serial.println(pzem.readAddress(), HEX);
    newmillis = millis ();  // quelle heure est il ?
    // if ((newmillis - oldmillis) > 36000)  {action6minutes(); oldmillis=newmillis ; timer6minutes ++ ;};  // TEST pour aller 100 fois plus vite !!!
    if ((newmillis - oldmillis) > 360000)  {action6minutes(); oldmillis=newmillis ; timer6minutes ++ ;};  // a faire au bout de 6 minutes, mise à jour du tableau dayly
    if (timer6minutes > 9  ) {action1heure(); timerheures ++;  } ;                  // a faire au bout de 1 heure
    if (timerheures > 239 ) {action10jours (); timerheures = 0;} ;                                 // a faire au bout de 10 jours
    if (timer6minutes > 9)  { timer6minutes = 0 ;} ;                        // laisser ici
   

    // Read the data from the sensor
    voltage = pzem.voltage();
    current = pzem.current();
    power = pzem.power();
    energy = pzem.energy();
    frequency = pzem.frequency();
    pf = pzem.pf();
        // Print the values to the Serial console
        /*  // FOR TEST ONLY
        Serial.print("Voltage: ");      Serial.print(voltage);      Serial.print(" V : ");
        Serial.print("Current: ");      Serial.print(current);      Serial.print(" A : ");
        Serial.print("Power: ");        Serial.print(power);        Serial.print(" W : ");
        Serial.print("Energy: ");       Serial.print(energy,3);     Serial.print(" kW : h");
    //    Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.print("Hz");
        Serial.print("PF: ");           Serial.println(pf);
        */ 
    // power = power * 100;  // test only  
      // Display on the screen
 // Serial.print("mode = ");Serial.print (mode) ;Serial.print(" daylyindex = ");Serial.println (daylyindex) ; // TEST ONLY
      // mode = 2 ;  // pour tests
      if (mode == 0) {mode0 ();};
      if (mode == 1) {mode1 ();};
      if (mode == 2) {mode2 ();};
      if (mode == 3) {mode3 ();};
      if (mode == 4) {mode4 ();};
     
   // afficherdayly ();
    delay(1000);
}
