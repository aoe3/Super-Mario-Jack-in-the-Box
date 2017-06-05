Servo myservo;
//pins for flex sensor, speaker, servo, and light (only used for silent testing)
const int flexPin = A0;
const int tonePin = D0;
const int jackPin = D1;
const int slntPin = D7;

//Is the jack up? Default to false.
bool up = false;

void setup(){
  Serial.begin(9600);
  pinMode(tonePin, OUTPUT);
  pinMode(flexPin, OUTPUT);
  myservo.attach(jackPin);
  //For quiet testing, when someone is sleeping in the lab...
  pinMode(slntPin, OUTPUT);
}

void loop(){

  //read in flex pin
  int val = analogRead(flexPin);
  Serial.println(val);
  if ((val < 910) || (val > 970)){
    if (! up){
      up = true;
      //box is closed but flex sensor has been triggered. open box
      myservo.write(150);
      delay(370);

      //play coin sound from Super Mario Bros. Values obtained from trials.
      tone(tonePin,1018);
      delay(100);
      noTone(tonePin);
      tone(tonePin,2028);
      delay(300);
      noTone(tonePin);
      delay(1000);

      //Someone's sleeping in lab. Instead turn D7 (blue light) on.
      /*digitalWrite(slntPin, HIGH);
      delay(2000);
      digitalWrite(slntPin, LOW);*/
    }
  } else {
    if (up){
      //the jack is up but flex sensor is reset. close the box
      //reset boolean
      up = false;
      delay(300);

      //pull jack back into the box
      myservo.write(0);
    }
  }
  delay(200);
}
