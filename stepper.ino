// bind stepper with schmalzhaus.com easydriver to poti
#define DIR_PIN 2
#define STEP_PIN 3
#define POTI_PIN A0

int dir = LOW;
int threshold = 5;
int diff = 0;
//speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
float master_speed = .5;
int previous_val = 0;

void setup(){
  Serial.begin(9600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);


}
void loop(){
  // read from the poti
  int val = analogRead(POTI_PIN);
  // map the value to the steps of the stepper
  val = map(val, 0, 1023, -1600, 1600);

  if(val < previous_val - threshold){

    dir = HIGH;

    diff = previous_val - val;
    
    rotate(diff, master_speed, dir);

       Serial.print(val);
       Serial.print(" is ");
       Serial.print(" smaller ");
       Serial.print(" then ");
       Serial.println(previous_val);
       Serial.print("The difference is: ");
       Serial.println(diff);

  }
  else if(val > previous_val + threshold){
    dir = LOW;

    diff = val - previous_val;
    
    // call the function rotate
    rotate(diff, master_speed, dir);
       Serial.print(val);
       Serial.print(" is ");
       Serial.print(" higher ");
       Serial.print(" then ");
       Serial.println(previous_val);
       Serial.print("The difference is: ");
       Serial.println(diff);
  }
  else{
    val = 0;
    //    Serial.println("Still");
//      rotate(0, master_speed, LOW);
  }

  previous_val = val;
}



void rotate(int steps, float speed, int dir){
  //rotate a specific number of microsteps (8 microsteps per step) - (negitive for reverse movement)


  digitalWrite(DIR_PIN, dir);

  float usDelay = (1/speed) * 70;

  for(int i=0; i < steps; i++){

    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(usDelay);

    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(usDelay);
  }
}




