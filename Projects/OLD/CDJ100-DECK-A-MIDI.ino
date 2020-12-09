//  -------------------------------- ABOUT ---------------------------------------
// | Project: Pioneer CDJ 100 MIDI                                               |
// | Autor: Łukasz Kucia                                                         |
// | Version : 1.0 Beta                                                          |
// | Hardware: Arduino Pro Micro
// | Description: Change old cd player on midi controller works with dj programs |
// |             (Traktor, Virtual DJ, Serato, FL studio etc.)                   |
// | Github: https://github.com/Lukaszm328/ArduinoMidiControllerUsb              | 
//  ------------------------------------------------------------------------------ 
#include "MIDIUSB.h"
#include "PitchToNote.h"
#define NUM_BUTTONS  13

const uint8_t button1 = 0;  // CUE
const uint8_t button2 = 1;  // PLAY
const uint8_t button3 = 5; // SEARCH +
const uint8_t button4 = 6; // SEARCH -
const uint8_t button5 = 15;  // TRACK +
const uint8_t button6 = 15;  // TRACK -
const uint8_t button7 = 6;  // JET
const uint8_t button8 = 7;  // ZIP
const uint8_t button9 = 8;  // WAH
const uint8_t button10 = 9; // HOLD
const uint8_t button11 = 10;// AUTO CUE
const uint8_t button12 = 14;// M.TEMPO
const uint8_t button13 = 16;// EJECT

const uint8_t buttons[NUM_BUTTONS] = {button1, button2, button3, button4, button5, button6, button7, button8, button9, button10, button11, button12, button13};
const byte notePitches[NUM_BUTTONS] = {60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72};

uint8_t notesTime[NUM_BUTTONS];
uint8_t pressedButtons = 0x00;
uint8_t previousButtons = 0x00;
uint8_t intensity;

// Timing for polling the encoder
unsigned long currentTime;
unsigned long lastTime;

// Pin definitions JOG
const int pinA = 3;
const int pinB = 2;

// Storing the readings
boolean encA;
boolean encB;
boolean lastA = false;

void setup() {
  
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT); 
  pinMode(17, OUTPUT);
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  pinMode(0, INPUT_PULLUP);

  for (int i = 0; i < NUM_BUTTONS; i++)
    pinMode(buttons[i], INPUT_PULLUP);
  
  // Set up the timing of the polling
  currentTime = millis();
  lastTime = currentTime;
   
  // Start the serial monitor for debugging
  Serial.begin (9600);
}

void loop() {
  ReadEncoder();
  ReadTempoValue();
  ReadButtons();
  playNotes();
  ReadMIDI(); 
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void playNotes()
{
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    if (bitRead(pressedButtons, i) != bitRead(previousButtons, i))
    {
      if (bitRead(pressedButtons, i))
      {
        bitWrite(previousButtons, i , 1);
        noteOn(0, notePitches[i], 127);
        MidiUSB.flush();
      }
      else
      {
        bitWrite(previousButtons, i , 0);
        noteOff(0, notePitches[i], 0);
        MidiUSB.flush();
      }
    }
  }
}

void ReadEncoder(){
  // Read elapsed time
  currentTime = millis();
  // Check if it's time to read
 if(currentTime >= (lastTime + 3))
  {
    // read the two pins
    encA = digitalRead(pinA);
    encB = digitalRead(pinB);
    // check if A has gone from high to low
    if ((!encA) && (lastA))
    {
      // check if B is high
      if (encB)
      {
        // clockwise
        noteOn(1, 48, 1);   // Channel 0, middle C, normal velocity
        MidiUSB.flush();
      }
      else
      {
        // anti-clockwise
        noteOn(1, 48, 127);   // Channel 0, middle C, normal velocity
        MidiUSB.flush();
      }
    }
    // store reading of A and millis for next loop
    lastA = encA;
    lastTime = currentTime;
  }
}

bool blinkLed = false;

void ReadMIDI(){
  
      midiEventPacket_t rx;
      rx = MidiUSB.read();
      
    if (rx.byte1 == 144 && rx.byte2 == 0 && rx.byte3 == 127)
    {
      Serial.println("PLAY LED ON");
            blinkLed = false;
      digitalWrite(19, HIGH);
    }
    if (rx.byte1 == 144 && rx.byte2 == 0 && rx.byte3 == 0){
       Serial.println("PLAY LED OFF");
       digitalWrite(19, LOW);
       blinkLed = true;
    }
    
    if (rx.byte1 == 144 && rx.byte2 == 1 && rx.byte3 == 127)
    {
      Serial.println("CUE LED ON");
      digitalWrite(20, HIGH);
    }
    if (rx.byte1 == 144 && rx.byte2 == 1 && rx.byte3 == 0){
       Serial.println("CUE LED OFF");
       digitalWrite(20, LOW);
    }

    if (rx.byte1 == 144 && rx.byte2 == 2 && rx.byte3 == 127)
    {
      //Serial.println("RX LED ON");
      digitalWrite(17, HIGH);
    }
    if (rx.byte1 == 144 && rx.byte2 == 2 && rx.byte3 == 0){
       //Serial.println("RX LED OFF");
       digitalWrite(17, LOW);
    }
}

uint8_t tempoValue;
void ReadTempoValue()
{
  int val = analogRead(A3);
  intensity = (uint8_t) (map(val, 0, 1023, 0, 127));
      if (tempoValue != intensity){
        noteOn(2, 2, intensity);
        MidiUSB.flush();
        tempoValue = intensity;
      }
}

int CueLastState = 1;

void ReadButtons(){

 for (int i = 0; i < NUM_BUTTONS; i++)
  {
    if (digitalRead(buttons[i]) == LOW)
    {
      bitWrite(pressedButtons, i, 127);
      //delay(10);
      Serial.println(i);
    }
    else{
       bitWrite(pressedButtons, i, 0);
    }
  }
}

void BlinkPlayLed(int ledPin, int timeSleep){
  digitalWrite(ledPin, LOW);
  delay(timeSleep);
  digitalWrite(ledPin, HIGH);
  delay(timeSleep);
}
