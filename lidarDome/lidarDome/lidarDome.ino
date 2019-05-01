int newcommand;


unsigned long sinceMoving=0;

#define a 2
#define b 3

int i;


char incomingByte;
char command;
char serialdata[10];

void openShutter(){

    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    sinceMoving=millis();
    
}

void closeShutter(){

    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    sinceMoving=millis();
    
}

void stopShutter(){
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);

}

void setup() {
  // put your setup code here, to run once:

    Serial.begin(9600);
    Serial.setTimeout(500);
  
    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);

    stopShutter();
    

}

void loop() {
  // put your main code here, to run repeatedly:

    if(Serial.available()){
        incomingByte = Serial.read();
        if(incomingByte==':'){
          
          for(i=0; i<10; i++){
              serialdata[i]=0;
          }
          
          Serial.readBytesUntil('#', serialdata, 10);
          
          if(serialdata[0]=='D'){
            //dome data
            if(serialdata[1]=='C'){
              closeShutter();
              
            }else if(serialdata[1]=='O'){
              openShutter();

            }
          }
        }
      
    }


  if(millis()-sinceMoving>5000){
      stopShutter();    
  }

}
