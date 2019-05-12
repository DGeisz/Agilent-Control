
int ThermistorPin[3] = {A0,A1,A2};
float V1;
float Vin = 5.;
float R0 = 10000.;
float logR1, R1;
float R01 = 10980.;
float c2 = 295.95;
float T[3];
float c1 = 298.15, b1=3070., b2 = 3380.;
String incomingMessage;
String messageKey = "a";
bool start = false;

void setup() {
Serial.begin(9600);
/*while (not start){
  if (Serial.available() > 0){
    messageKey = Serial.readString();
    start = true;
  }
}*/
}
void gettemp(){
    //for(int i=0; i<2; i++){
    V1=(5./1023.0)*analogRead(ThermistorPin[0]);
    R1 = R0 * (Vin/V1 - 1.0);
    logR1 = log(R1/R0);
    T[0] = (1.0 / (1/c1 + ((1/3435.)*logR1)))-273.15;
   //}
    V1=(5./1023.0)*analogRead(ThermistorPin[1]);
    R1 = R0 * (Vin/V1 - 1.0);
    logR1 = log(R1/R0);
    T[1] = (1.0 / (1/c1 + ((1/b1)*logR1)))-273.15;
    
    V1=(5./1023.0)*analogRead(ThermistorPin[2]);
    R1 = R0 * (Vin/V1 - 1.0);
    logR1 = log(R1/R0);
    T[2] = (1.0 /(1/c1 + ((1/b2)*logR1))) - 273.15;
}

void loop() {
  gettemp();
  if (Serial.available() > 0){
    incomingMessage = Serial.readString();
      //Serial.read();
    if (incomingMessage == messageKey){
      for (int i=0; i<3; i++){
        Serial.print(T[i]);
        Serial.print(" "); 
      }
    }
  //Serial.println(); 
  }  
    
}
