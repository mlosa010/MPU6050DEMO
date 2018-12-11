#include <Arduino.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);
volatile int flag = 0;
long timer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  DDRD &= ~( 1<< PD2 );
  PORTD |= (1 << PD2);

  //
  EICRA &= ~(1 << ISC00);
  EICRA |= (1 << ISC01);
  EIMSK |= (1 << INT0);

  sei();
}

void loop() {
  mpu6050.update();
  if(millis() - timer > 1000){
    Serial.println("=======================================================");
    Serial.print("temp : ");Serial.println(mpu6050.getTemp());
    if (flag){
      Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
      Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ());
    }
    Serial.println("=======================================================\n");
    timer = millis();
  }
}

ISR(INT0_vect){
  flag = !flag;
}
