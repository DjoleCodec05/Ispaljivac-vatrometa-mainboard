#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Channel buttons
int Ch1 = A3;
int Ch2 = A2;
int Ch3 = A1;
int Ch4 = A0;

//Other buttons
int Rapid = 6; // Btn1
int AllFire = 5; //Btn2

//Encoder
int DT = 9;
int CLK = 10;
int SW = 3;

//Safety key
int KEY = 4;


int buttonval1 = 1;
int buttonval2 = 1;
int buttonval3 = 1;
int buttonval4 = 1;

int Ch1Val;
int Ch2Val;
int Ch3Val;
int Ch4Val;

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "Node1";
//const byte address[6] = "Node2";
//const byte address[6] = "Node3";
//const byte address[6] = "Node4";


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Fireworks    ");
  lcd.setCursor(0, 1);
  lcd.print("    Igniter     ");
  delay(2000);
  lcd.clear();
  pinMode(Ch1, INPUT_PULLUP);
  pinMode(Ch2, INPUT_PULLUP);
  pinMode(Ch3, INPUT_PULLUP);
  pinMode(Ch4, INPUT_PULLUP);
  pinMode(KEY, INPUT_PULLUP);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {

  Ch1Val = analogRead(Ch1);
  Ch2Val = analogRead(Ch2);
  Ch3Val = analogRead(Ch3);
  Ch4Val = analogRead(Ch4);

  lcd.setCursor(0, 0);
  lcd.print("Select channel:");

  if (Ch1Val < 1000) {
    buttonval1 = 0;
    lcd.setCursor(0, 1);
    lcd.print(" 1 ");
    delay(300);
    lcd.clear();
    delay(100);

  }

  else if (Ch2Val < 1000) {
    buttonval2 = 0;
    lcd.setCursor(0, 1);
    lcd.print("   2 ");
    delay(300);
    lcd.clear();
    delay(100);
  }

  else if (Ch3Val < 1000) {
    buttonval3 = 0;
    lcd.setCursor(0, 1);
    lcd.print("      3 ");
    delay(300);
    lcd.clear();
    delay(100);
  }

  else if (Ch4Val < 1000) {
    buttonval4 = 0;
    lcd.setCursor(0, 1);
    lcd.print("         4 ");
    delay(300);
    lcd.clear();
    delay(100);
  }

  else {
    buttonval1 = 1;
    buttonval2 = 1;
    buttonval3 = 1;
    buttonval4 = 1;
    delay(100);
  }





  radio.write(&buttonval1, sizeof(buttonval1));
  radio.write(&buttonval2, sizeof(buttonval2));
  radio.write(&buttonval3, sizeof(buttonval3));
  radio.write(&buttonval4, sizeof(buttonval4));


}
