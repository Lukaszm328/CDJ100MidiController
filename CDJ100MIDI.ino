#define USE_ROTARY_ENCODER
#include <MIDI_Controller.h>

const uint8_t velocity = 0b1111111; // Maximum velocity (0b1111111 = 0x7F = 127)
const uint8_t Controller = 0x14; // MIDI Control Change controller number
const int speedMultiply = 1;     // No change in speed of the encoder (number of steps is multiplied by 1)

// ------------------------- DECK A ------------------------------

// Buttons
Digital A_Button_PLAY(22, 60, 1, velocity);
Digital A_Button_CUE(24, 61, 1, velocity);
Digital A_Button_FORWARD(26, 62, 1, velocity);
Digital A_Button_BACKWARDS(28, 63, 1, velocity);
Digital A_Button_NEXT(30, 64, 1, velocity);
Digital A_Button_PREVIOUS(32, 65, 1, velocity);
Digital A_Button_JET(34, 66, 1, velocity);
Digital A_Button_ZIP(36, 67, 1, velocity);
Digital A_Button_WAH(38, 68, 1, velocity);
Digital A_Button_HOLD(40, 69, 1, velocity);
Digital A_Button_TIME(42, 70, 1, velocity);
Digital A_Button_EJECT(44, 71, 1, velocity);
Digital A_Button_TEMPO(46, 72, 1, velocity);

// Encoder jog
RotaryEncoder encoderA(48, 50, Controller, 1, speedMultiply, JOG, TWOS_COMPLEMENT);

// Pitch fader
Analog potentiometerA(A0, MIDI_CC::Channel_Volume, 1);

// Led's

// ------------------------- DECK B ------------------------------

// Buttons
Digital B_Button_PLAY(23, 73, 2, velocity);
Digital B_Button_CUE(25, 74, 2, velocity);
Digital B_Button_FORWARD(27, 75, 2, velocity);
Digital B_Button_BACKWARDS(29, 76, 2, velocity);
Digital B_Button_NEXT(31, 77, 2, velocity);
Digital B_Button_PREVIOUS(33, 78, 2, velocity);
Digital B_Button_JET(35, 79, 2, velocity);
Digital B_Button_ZIP(37, 80, 2, velocity);
Digital B_Button_WAH(39, 81, 2, velocity);
Digital B_Button_HOLD(41, 82, 2, velocity);
Digital B_Button_TIME(43, 83, 2, velocity);
Digital B_Button_EJECT(45, 84, 2, velocity);
Digital B_Button_TEMPO(47, 85, 2, velocity);

// Encoder JOG
RotaryEncoder encoderB(49, 51, Controller, 2, speedMultiply, JOG, TWOS_COMPLEMENT);

// Pitch fader
Analog potentiometerB(A1, MIDI_CC::Channel_Volume, 2);

void setup() {}

void loop() {
  MIDI_Controller.refresh();
}
