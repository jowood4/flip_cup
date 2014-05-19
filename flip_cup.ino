#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <Adafruit_NeoPixel.h>

int light_pin = 0;
//int x_pin = 1;
//int y_pin = 2;
int z_pin = 1;

//int x_val = 0;
//int y_val = 0;
int z_val = 0;
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel light = Adafruit_NeoPixel(1, light_pin, NEO_GRB + NEO_KHZ800);

volatile int f_wdt=1;

ISR(WDT_vect)
{
  if(f_wdt == 0)
  {
    f_wdt=1;
  }
}

void setup()
{
  /*** Setup the WDT ***/
  
  /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);
  
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCR |= (1<<WDCE) | (1<<WDE);

  /* set new watchdog timeout prescaler value */
  WDTCR = 1<<WDP2 | 1<<WDP1; /* 0.5 seconds */
  
  /* Enable the WD interrupt (note no reset). */
  WDTCR |= _BV(WDIE);
  //wdt_enable(WDTO_1S);

  /***   ***/

  //power_all_enable();     
  power_timer0_disable();
  power_timer1_disable(); 
  power_usi_disable();

  //set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  light.begin();
  light.setBrightness(255);
  light.show(); // Initialize all pixels to 'off'
}


void loop()
{
  if(f_wdt == 1)
  { 
    /* Don't forget to clear the flag. */
    f_wdt = 0;
    
    /* Re-enter sleep mode. */
    //enterSleep();
    sleep_enable();
    sleep_mode();
    sleep_disable();

    //power_all_enable();
    power_adc_enable();
    z_val = analogRead(z_pin);
    power_adc_disable();
  
    if(z_val < 500)
    {
      //z_val = 240;
      light.setPixelColor(0, 255, 0, 0);
    }
    else
    {
      //z_val = 0;
      light.setPixelColor(0, 0, 255, 0);
    }
    //light.setPixelColor(0, 255, 0, z_val);
    
    
    light.show();
    //delay(1000);
  }
}
