// Program to blink an LED connected to pin D0 by S0 pulse
// of the Spark Core.
// provide S0, kwh, watt, ahwatt, adwatt

#include "inepro.h"

// We name pin D0 as led
// int hb_led = D7;
int S0_led = D7;
int e_inp = D3;

unsigned long S0 = 0;
unsigned long m_uptime = 0;
unsigned long p_micros, p_millis, c_micros, c_millis;
double kwh = -0.001;

int watt = 0;
int ahwatt = 0;
int adwatt = 0;
int intowerflow = 0;

int hb_led_state = LOW;
int S0_led_state = LOW;
int S0_led_count = 30;
int hb = 0;

// This routine runs only once upon reset
void setup()
{
  // Initialize Dx pin as output
//  pinMode(hb_led, OUTPUT);
  pinMode(S0_led, OUTPUT);
  digitalWrite(S0_led,LOW);
//   pinMode(e_inp, INPUT_PULLDOWN);
  pinMode(e_inp, INPUT);
  attachInterrupt(e_inp, inpuls, RISING);

// variable name max length is 12 characters long
  Particle.variable("S0", S0);
  Particle.variable("m_uptime", m_uptime);

  Particle.variable("kwh", kwh);
  Particle.variable("watt", watt);

  Particle.variable("ahwatt", ahwatt);
  Particle.variable("adwatt", adwatt);

//  Particle.variable("mess", message);
  RGB.control(true);
// red, green, blue, 0-255.
// the following sets the RGB LED to white:
  RGB.color(0, 0, 0);
}

// This routine loops forever
void loop()
{
//    fhb();
    if (S0>1)
        measure();

}


void measure()
{
    unsigned long t;

    if ((millis()-c_millis)>S0_led_count)
        RGB.color(0, 0, 0);
//            pinResetFast(S0_led);

//        if (S0_led_count>(milis0)
//            S0_led_count--;


    t = c_millis - p_millis;
    ahwatt = t ;
    watt = 360000 / t ;
    m_uptime = c_millis / 60000;
    kwh = (double) S0 / 10000;

}


void inpuls()
{
//    pinSetFast(S0_led);
    RGB.color(255, 0, 0);

    S0++; intowerflow++;
    p_micros = c_micros;
    p_millis = c_millis;
    c_micros = micros();
    c_millis = millis();
    S0_led_count = 20;

}

// You can attach a method in a C++ object as an interrupt handler.
class Robot {
  public:
    Robot() {
      attachInterrupt(e_inp, &Robot::handler, this, RISING);
    }
    void handler() {
      // do something on interrupt
    }
};

Robot myRobot;
// nothing else needed in setup() or loop()
