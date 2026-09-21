#define RGB_BUILTIN 38 
#define RGB_BRIGHTNESS 50 
 
void setup() { 
  // No separate initialisation is required for this example. 
} 
 
void loop() { 
  // Red ON 
  neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS, 0, 0); 
  delay(200); 
 
  // LED OFF 
  neopixelWrite(RGB_BUILTIN, 0, 30, 0); 
  delay(450); 

  neopixelWrite(RGB_BUILTIN, 0, 0, 0); 
  delay(500); 

  neopixelWrite(RGB_BUILTIN, 0, 0, 40); 
  delay(300); 

  neopixelWrite(RGB_BUILTIN, 36, 0, 50); 
  delay(200); 

  neopixelWrite(RGB_BUILTIN, 0, 0, 0); 
  delay(250); 

  neopixelWrite(RGB_BUILTIN, 54, 0, 0); 
  delay(500); 

} 