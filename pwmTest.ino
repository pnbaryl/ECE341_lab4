//test code for junior design power supply
//Paige Barylsky
////////////////////////////////////////////////

//ANALOUGE INPUT PIN DECLARATIONS
#define PIN_CURR_IN    A0 //Analog input pin for Current Shunt Monitor
#define PIN_CURR_OUT   A1 //Analog input pin for Current Shunt Monitor
#define PIN_POT        A2 //Analog input pin that the potentiometer is attached to
#define PIN_THERMO     A3 //Analog input pin for thermoresistor
#define PIN_V1         A4 //Analog input to monitor voltage
#define PIN_V2         A5 //Analog input to monitor voltage

//PWM OUTPUT PIN
#define PIN_PWM_OUT    3  //Analog output pin for PWM signal to tip29C
//Global Variable Declaration
int pot_signal;        // input read from the pot
int pwm_output_value;  // value mapped from 0 to 1023 from pot_signal for PWM analogWrite to tip29C base
int curr_in_signal;    // input value stored from current sensor measureing input of U1
int curr_out_signal;   // input value stored from current sensor measureing ouput of U1
int curr_in_value;     // the value mapped from 0 to 1023 from curr_in_signal
int curr_out_value;    // the value mapped from 0 to 1023 from curr_out_signal
int v1_signal;         // input value of the voltage measured from PIN_V1, attached to 3.3v input
int v2_signal;         // input value of the voltage measured from PIN_V1, attached to 3.3v input
int v1;                // the value mapped from v1_signal
int v2;                // the value mapped from v2_signal
int thermo_signal;     // input value of thermoresistor
int thermo_value;      // the value mapped from thermo_signal
//INITALIZATION FUNCTION
void setup() {
  pinMode(PIN_PWM_OUT, OUTPUT);     //set digital pin 3, pwm, as output
  pinMode(PIN_CURR_IN, INPUT);
  pinMode(PIN_CURR_OUT, INPUT);
  pinMode(PIN_POT, INPUT);
  pinMode(PIN_THERMO, INPUT);
  pinMode(PIN_V2, INPUT);
  pinMode(PIN_V1, INPUT);
  
  analogWrite(PIN_PWM_OUT, 1023);  //initalize to cutoff transistor by raising base voltage 
  Serial.begin(9600);             //initialize serial communications at 9600 baud
}
//ENDLESS LOOP
void loop() {
  /////////Read Pot, Map value to max range, write to PWM//
  pot_signal = analogRead(PIN_POT);                     // read the analog in value
  pwm_output_value = map(pot_signal, 0, 1023, 15, 240);// map it to the range of the analog out:
  analogWrite(PIN_PWM_OUT, pwm_output_value);               // change the analog out value:
  /////////////////////////////////////////////////////

  //////////////Read and map current values/////////////////////   
  curr_in_signal = analogRead(PIN_CURR_IN);                  //
  curr_in_value = map(curr_in_signal, 0, 1023, 0, 255);     //
  curr_out_signal = analogRead(PIN_CURR_OUT);              //
  curr_out_value = map(curr_out_signal, 0, 1023, 0, 255); //
  /////////////////////////////////////////////////////////
  //////////////Read and map Thermo value/////////////////   
  thermo_signal = analogRead(PIN_THERMO);              //
  thermo_value = map(thermo_signal, 0, 1023, 15, 240);//
  //////////////Read and map voltage values////////////
  v1_signal = analogRead(PIN_V1);              
  v1 = map(v1_signal, 0, 1023, 15, 240);// 
  v2_signal = analogRead(PIN_V2);               
  v2 = map(v2_signal, 0, 1023, 15, 240);//
  
  ////////print the results to the Serial Monitor://////
  Serial.print(pot_signal);                            
  Serial.print("\t ");                            
  Serial.print(curr_in_value);
  Serial.print("\t");
  Serial.print(curr_out_value);
  Serial.print("\t");
  Serial.print(thermo_value);
  Serial.print("\t");
  Serial.print(v1);
  Serial.print("\t");
  Serial.print(v2);
  Serial.print("\t");
  Serial.println(pwm_output_value);


  
  delay(100);    // wait 100 milliseconds before the next loop
}
