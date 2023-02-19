
#include <MIDI.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// digital pin for strand signal
#define PIN 6 

// number of pixels in strand
#define NUMPIXELS 60 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time to pause between pixels

//global rgb values
int r = 0;
int g = 0;
int b = 0;


//constants 
const int piezoSensor = A0; // piezo pin
const int potPin = A1; //potentimeter pin
const int piezoThreshold = 250; 

//variables 
int sensorReading = 0; // sensor output
int potValue = 0; // current value of the potentiometer
//int sens255 = (sensorReading / 4); 
//int sensBright = constrain(sensBright, 75, 200);

MIDI_CREATE_DEFAULT_INSTANCE();



void setup() {
  pixels.begin(); 
  pixels.show();
  pixels.setBrightness(200);
  MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
  Serial.begin(9600);
  
}

void loop() {

  //Debug Prints

  //Serial.println(sensorReading);

  //Serial.println(piezoThreshold);

  //Serial.println(sens255);

  /////
  
  
  potValue = analogRead(potPin); 
  sensorReading = analogRead(piezoSensor); 
  pixels.clear(); // Set all pixel colors to 'off'

  //pixels.setBrightness(sensorReading * 4);

  int hue = (sensorReading * 64);
  uint32_t rgbcolor = pixels.ColorHSV(hue);

  if (sensorReading > piezoThreshold) {

    pixels.fill(rgbcolor);

    pixels.show();

    MIDI.sendNoteOn(42, 127, 1);
    delay(potValue);
    MIDI.sendNoteOff(42,0,1);

    
    
    //delay(potValue);
   
    }

  pixels.show();
    
  //delay(10);     

  
    
    

}
