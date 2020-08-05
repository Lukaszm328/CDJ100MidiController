//  -------------------------------- ABOUT ---------------------------------------
// | Project: Pioneer CDJ 100 MIDI                                               |
// | Autor: Łukasz Kucia                                                         |
// | Version : 1.0 Beta                                                          |
// | Hardware: Arduino Pro Micro
// | Description: Change old cd player on midi controller works with dj programs |
// |             (Traktor, Virtual DJ, Serato, FL studio etc.)                   |
// | Github: https://github.com/Lukaszm328/ArduinoMidiControllerUsb              | 
//  ------------------------------------------------------------------------------ 
#define USE_ROTARY_ENCODER
#include <MIDI_Controller.h>

// --------------------------------------------- VARIABLES -----------------------------------------------------
const uint8_t velocity   = 0b1111111;  // Maximum velocity (0b1111111 = 0x7F = 127)                             |
const uint8_t ledPlayPin = 19;         // LED pin play                                                          |
const uint8_t ledCuePin  = 20;         // LED pin cue                                                           |
const int speedMultiply  = 1;          // No change in speed of the encoder (number of steps is multiplied by 1)|
// -------------------------------------------------------------------------------------------------------------

// ------------------------ BUTTONS ----------------------------
  Digital Button_PLAY(1, 60, 1, velocity);           // PIN 1  |  
  Digital Button_CUE(0, 61, 1, velocity);            // PIN 0  |
  Digital Button_FORWARD(2, 62, 1, velocity);        // PIN 2  |
  Digital Button_BACKWARDS(3, 63, 1, velocity);      // PIN 3  |
  Digital Button_NEXT(4, 64, 1, velocity);           // PIN 4  |
  Digital Button_PREVIOUS(5, 65, 1, velocity);       // PIN 5  |
  Digital Button_JET(6, 66, 1, velocity);            // PIN 6  |
  Digital Button_ZIP(7, 67, 1, velocity);            // PIN 7  |
  Digital Button_WAH(8, 68, 1, velocity);            // PIN 8  |
  Digital Button_HOLD(9, 69, 1, velocity);           // PIN 9  |
  Digital Button_TIME(10, 70, 1, velocity);          // PIN 10 |
  Digital Button_EJECT(16, 71, 1, velocity);         // PIN 11 |
  Digital Button_TEMPO(14, 72, 1, velocity);         // PIN 12 |
  Digital Button_ENCODER_BT(21, 73, 1, velocity);    // PIN 13 |
// -------------------------------------------------------------

// ------------------- ROTARY  ENCODERS -----------------------------------------------------
// MODE: POS1_NEG127 - 7Fh/01h || ADD_64 - 3Fh/41h || TWOS_COMPLEMENT                       |
// Set pulsesPerStep to 4, for normal rotary encoders  1, for jog wheels.                   |
// JOG                                                                                      |
  RotaryEncoder encoderJOG(15, 18, 0x14, 1, speedMultiply, JOG, POS1_NEG127); // PIN 15, 18 |
// BROWSER(OPTIONAL)                                                                        |
  RotaryEncoder encoderBrowser(15, 18, 0x15, 1, speedMultiply, JOG, ADD_64);  // PIN 19, 20 |  
// ------------------------------------------------------------------------------------------

// -------------------------- ANALOG --------------------------------- 
 // TEMPO VALUE                                                      |
  Analog potentiometerTEMPO(A3, MIDI_CC::Channel_Volume, 1); //PIN A3|
// -------------------------------------------------------------------

// ------------------------- SETUP -----------------------------------

void setup() {
// --------------------------- LED -----------------------------------
   // PLAY/PAUSE Ch01.CC.000                                  PIN 19 |
//   pinMode(ledPlayPin, OUTPUT);                                  //|
   // CUE        Ch01.CC.001                                  PIN 20 |
//   pinMode(ledCuePin, OUTPUT);                                   //|
// ------------------------------------------------------------------- 
}

void loop() {
  MIDI_Controller.refresh();
  MIDI_Controller.read();
}
