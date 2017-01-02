#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include "small_display.h"

#define RLBIT 0x10
#define GLBIT 0x20
#define BLBIT 0x40
#define YLBIT 0x80

#define RBBIT 0x04
#define GBBIT 0x08
#define BBBIT 0x02
#define YBBIT 0x01

//Defines frequencies for sounds
#define RED_SOUND 100
#define YELLOW_SOUND 200
#define BLUE_SOUND 300
#define GREEN_SOUND 400

#define POWER 16
#define SPEAKER 17
//Definitions for ID of colors
#define R 1
#define G 2
#define B 3
#define Y 4
#define SLEEP_TIME 60000 //Sleep time in milliseconds

//global variables, easy to use and program does not use much memory
#define ROUNDS 50
byte game_nums[ROUNDS]; //colors for rounds stored here
byte turn = 0; //Which turn/round number it currently is
byte input = 0; //Byte for holding input
unsigned long sleep_timer = 0;
byte port_d = 0;

Adafruit_SSD1306 display(A3, A2);

ISR(PCINT0_vect) {  
  if (PINB & 0x04) {
    PORTB |= 0xF0;
    PORTF &= ~0xC0;
    noTone(SPEAKER);
    delay(300);
    wdt_enable(WDTO_15MS);
  }
}

void setup() 
{ 
  //Seed RNG with analog reads, and disable ADC/usart
  randomSeed(analogRead(0) + analogRead(5)); //Seed random number generator with a floating input
  power_adc_disable();
  power_usart1_disable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); 

  
  //Set LED pins to outputs
  DDRB = 0xF1; //LED's and speaker are outputs
  PORTB = 0xF4; //Enable power button pullup
  DDRD = 0x00; //Buttons are inputs
  PORTD = 0x0F; //Enable pullups for buttons
  DDRF |= 0xC0; //Set A0/A1(display power\ground) to output
  PORTF = 0x80;  //Power enable

  GetNewGame(); //Start a new game
  pciSetup(POWER); //Enable interrupt
  
  delay(500);
  display.begin();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  sleep_enable();
  sleep_timer = millis();
}

void loop() { 
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Follow me!");
    display.display();
    SimonSay(); //Function for lights and sounds based on global game_nums[]

    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Round: ");
    display.print(turn+1);
    display.display();
      
    ///Get and check player input
    for (size_t i = 0; i <= turn; ++i) {
      input = 0; //Make sure input is zeroed
      sleep_timer = millis();
      
      //Check for input. Messy to take care of press debounce
      while(!input) {
        port_d = (PIND & 0x0F);
        if (!(port_d & RBBIT) && !input) {
          input = R;
          Red();
        }
        if (!(port_d & GBBIT) && !input) {
          input = G;
          Green();
        }
        if (!(port_d & BBBIT) && !input) {
          input = B;
          Blue();
        }
        if (!(port_d & YBBIT) && !input) {
          input = Y;
          Yellow();
        }
        
        if (millis() - sleep_timer >= SLEEP_TIME) Sleep();
      }
      
      //These lines are to keep lights and sound going while button is held
      while(!(PIND & RBBIT) && input == R) Red();
      while(!(PIND & GBBIT) && input == G) Green();
      while(!(PIND & BBBIT) && input == B) Blue();
      while(!(PIND & YBBIT) && input == Y) Yellow();

      if (input != game_nums[i]) GameOver(); //If player pressed right input game continues, else game over lights/sound
    }
    
    delay(900); //Delay before displaying next round
    turn++; //Increment turn number, if you don't game will keep replaying same round
}

//Starts a new game
void GetNewGame() {
  for (size_t i = 0; i < ROUNDS; ++i) game_nums[i] = random(1, 5);
}

//Plays lights/colors
void SimonSay() {  
  for (size_t i = 0; i <= turn; ++i) {    
    delay(225); //Delay between colors, less delay makes it more difficult
    
    //Call appropriate function by color, Can tune for difficulty
    switch (game_nums[i]) {
      case R:
      for (size_t i = 0; i < 7; ++i) Red();
      break;     
      case G:
      for (size_t i = 0; i < 7; ++i) Green();
      break;
      case B:
      for (size_t i = 0; i < 7; ++i) Blue();
      break;
      case Y:
      for (size_t i = 0; i < 7; ++i) Yellow();
      break;
    }
  }
}
            
void GameOver() {
  //Game is over, be annoying until a reset happens
  //When reset interrupt is called game turns false
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("GAME");
  display.println("  OVER!");
  display.print("Score: ");
  display.println((turn * 17));
  display.print("Turn: ");
  display.print(turn+1);
  display.display();
  PORTB &= ~0xF0;
  
  sleep_timer = millis();
  
  while(1) {
    PORTB |= RLBIT;
    tone(SPEAKER, RED_SOUND, 95);
    delay(100);
    PORTB &= ~RLBIT;
    
    PORTB |= BLBIT;
    tone(SPEAKER, BLUE_SOUND, 95);
    delay(100);
    PORTB &= ~BLBIT;
    
    PORTB |= GLBIT;
    tone(SPEAKER, GREEN_SOUND, 95);
    delay(100);
    PORTB &= ~GLBIT;
    
    PORTB |= YLBIT;
    tone(SPEAKER, YELLOW_SOUND, 95);
    delay(100);
    PORTB &= ~YLBIT;
    
    PORTB |= GLBIT;
    tone(SPEAKER, GREEN_SOUND, 95);
    delay(100);
    PORTB &= ~GLBIT;

    PORTB |= BLBIT;
    tone(SPEAKER, BLUE_SOUND, 95);
    delay(100);
    PORTB &= ~BLBIT;
    
    if (millis() - sleep_timer >= (SLEEP_TIME / 4)) Sleep();
   }
}

void Sleep() {
  PORTB |= 0xF0; //
  PORTF &= ~0x80; //Cut power to LCD
  noTone(SPEAKER);
  sleep_mode();
}

//RED LED and speaker sound
void Red() {
  PORTB &= ~RLBIT;
  tone(SPEAKER, RED_SOUND, 100);
  delay(100);
  PORTB |= RLBIT;
}

//Green LED and speaker sound
void Green() {
  PORTB &= ~GLBIT;
  tone(SPEAKER, GREEN_SOUND, 100);
  delay(100);
  PORTB |= GLBIT;
}

//Blue LED and speaker sound
void Blue() {
  PORTB &= ~BLBIT;
  tone(SPEAKER, BLUE_SOUND, 100);
  delay(100);
  PORTB |= BLBIT;
}

//Yellow LED and speaker sound
void Yellow() {
  PORTB &= ~YLBIT;
  tone(SPEAKER, YELLOW_SOUND, 100);
  delay(100);
  PORTB |= YLBIT;
}

void pciSetup(byte pin) {
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group 
}

