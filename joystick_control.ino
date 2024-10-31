#include <LiquidCrystal_I2C.h> //Include the library in your program
#include <AbleButtons.h> 
LiquidCrystal_I2C LCD(0x27, 16, 2); //set up your lcd_i2c

using Button = AblePullupButton;
using button_list = AblePullupButtonList;

#define sw 2 //mouse_button_1
int sw_value;
Button btn(sw);

int Y_axis = A1; 
int X_axis = A2; 
int xy_axis[2] = {Y_axis, X_axis};
int xy_value[2] = {Y_axis, X_axis};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i<2; i++) {
    pinMode(xy_axis[i], INPUT);
  }
  pinMode(sw, INPUT); //set pin to input
  LCD.init(); 
  LCD.backlight(); //turn on blacklight 
  btn.begin();
}

void loop() {
  btn.handle();
  xy_value[0] = analogRead(xy_axis[0]);
  xy_value[1] = analogRead(xy_axis[1]); 
  //my monitor is 1440x900
  xy_value[0] = map(xy_value[0], 0, 1023, 0, 900); 
  xy_value[1] = map(xy_value[1], 0, 1023, 0, 1440); 
  sw_value = digitalRead(sw);
  Display_LCD();

  Serial.print(xy_value[0]); //output for python to read it
  Serial.print(" ");
  Serial.print(xy_value[1]);
  Serial.print(" ");
  Serial.println(sw_value);

  delay(180);
  LCD.clear();
}

void Display_LCD() { //Display x, y axis on lcd
  LCD.setCursor(0, 0);
  LCD.print("Y = ");
  LCD.print(xy_value[0]);
  LCD.setCursor(9, 0);
  LCD.print("c : ");
  LCD.print(sw_value);
  LCD.setCursor(0, 1);
  LCD.print("X = ");
  LCD.print(xy_value[1]);
}
