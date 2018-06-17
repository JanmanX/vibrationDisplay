// vibrationDriver.ino
// Arduino program used to control the vibration display

int DELAY = 400;
int letters[][50] =
{
  {1,4,7,10,13,-1,-1,1,2,6,9,12,15,-1,-1,7,8,9,-1,-1,-1},
  {-1, -1,-1, 3,2,1,-1,-1,1,2,3, -1, -1, -1}
};
int totalLetters = 2;
int letterLengths[26] = {21, 14, 14, 14, 14}; //rest 0
int lengths[][50] = {
  {200, 200, 200, 200, 200, 200, 200,200, 200, 200, 200, 200, 200, 200,200, 200, 200, 200, 200, 200, 200},
  {200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200}
};

//                    1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16
//int pin_port[] = {0, 24, 26, 28, 30, 32, 34, 36, 38, 40, 50, 52, 44, 48, 42, 46}; // Bottom
int pin_port[] = {0, 28, 26, 24, 34, 32, 30, 40, 38, 36, 44, 52, 50, 46, 42, 48}; // Top


int pwm_pin[64] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 }; //rest 0
int pin_power[64] = {0}; //all 0

int target = 0;

int minPWM = 110;
int maxPWM = 255;

int pattern[50] = {-1};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i=0; i<64; i++)
    pinMode(i, OUTPUT);
}

bool inRange(int id, int target) {
  if (id < 0) return false;
  if (id >= letterLengths[target]) return false;
  return true;
}


void writeLetter(int sequence[])
{
  int pin = -1;

  for(int i = 0; i < 50; i++) {
    if(sequence[i] != -1){
      pin = pin_port[sequence[i]];
      digitalWrite(pin, HIGH);
    }
    delay(DELAY);

    if(i > 0) {
      if(sequence[i-1] != -1){
        pin = pin_port[sequence[i-1]];
        digitalWrite(pin, LOW);
      }
      delay(DELAY);
    }
  }

  return;
}

void loop() {
  //turn off everything
  for (int k = 0; k<16; k++) {
    if (pwm_pin[pin_port[k]] == 0) digitalWrite(pin_port[k], LOW);
    else analogWrite(pin_port[k], 0);
  }


  delay(100);
  //Serial.println("Before Loop");

  int counter = 0;
    // send data only when you receive data:
    while (Serial.available() > 0) {



      //Serial.println("in da loop");
      if(counter < 50){
        // read the incoming byte:
        pattern[counter] = Serial.read();

        // say what you got:
        //Serial.print("I received: ");
        //Serial.println(pattern[counter], DEC);
        counter ++;
      }
        else {
          while (Serial.available() > 0)
            Serial.read();
        }
    }
  //Serial.println("After Loop");


   if(pattern[0] != -1){
        for (int i = 0; i < 50; i ++){
          //Serial.print(pattern[i]);
          //Serial.print(", ");
        }
	DELAY = pattern[0];
      writeLetter(pattern+1);
   }

  for (int i = 0; i < 50; i ++){
    pattern[i]  = -1;
  }
}
