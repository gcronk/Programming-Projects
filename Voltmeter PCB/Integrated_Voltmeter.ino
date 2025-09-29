/*
  Grady Cronkite
  
  University of Maryland Robotics - Terraformers

  Voltmeter PCB
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 1:
  // R1 = 750   R2 = 470   Rtot = 1220
  int battery_volt = 12;
  int resistance_end = 470;
  long resistance_total = 1220;
  int sensorValue = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float ard_voltage = sensorValue * (5.0 / 1023.0) * ((resistance_total)/(resistance_total - resistance_end));    //voltage going to arduino.
  //The arduino can not read more than 5V
  double ard_current = ard_voltage/resistance_end;    //current going to the arduino. Keep below 50mA
  ard_current = ard_current *1000;
  float motor_volt = ard_voltage/0.4;   //Voltage estimated to be going through the motor
  double motor_current = battery_volt/(resistance_total);  //not usable yet

  // print out the value you read:
  Serial.print("Voltage thru Motor: ");
  Serial.print(motor_volt);
  Serial.println("V");
  delay(50);
  Serial.println(" ");


  Serial.print("Voltage thr Ard: ");
  Serial.print(ard_voltage);
  Serial.println("V");
  Serial.println(" ");

  delay(50);


  Serial.print("Current thru Ard: ");
  Serial.print(ard_current);
  Serial.println("mA");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");

  
  delay(5000);
  
  //Serial.println("Resistance: " resistance "ohms");
  //Serial.println("Current: " current "A");
}
