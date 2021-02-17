int buttonpin = 2; //define switch port
int  val;      //define digital variable val
 
void  setup() {
  Serial.begin(9600);
  
  pinMode(buttonpin,INPUT);//define switch as a output port
}


void  loop() {
  val=digitalRead(buttonpin);//read the value of the digital interface 3 assigned to val 
  
  if(val==LOW)//when the switch sensor have signal, LED blink
  {
    Serial.println("OUI");
  }
  
  else
  {
    Serial.println("NON");
  }

  delay(500);
}
