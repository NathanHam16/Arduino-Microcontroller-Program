// The following code was written by Nathan Wang, September 2020.
long randomNumber;
long randomNumbers[25] = {};

int leds[] = {12, 11, 10, 9}; // Assign pins 9-12 to all leds
int redled = 10; // Assign pin 12 to redled output
int redstate = 6; // Assign pin 8 to redled input
int redtone = 196; // Set the frequency associated with the red button to G2

int greenled = 11; // Assign pin 11 to greenled output
int greenstate = 7; // Assign pin 7 to redled input
int greentone = 294; // Set the frequency associated with the green button to D3

int blueled = 12; // Assign pin 10 to blueled output
int bluestate = 8; // Assign pin 6 to blueled input
int bluetone = 392; // Set the frequency associated with the blue button to G3

int yellowled = 9; // Assign pin 9 to yellowled input
int yellowstate = 5; // Assign pin 5 to yellowled output
int yellowtone = 587; // Set the frequency associated with the yellow button to D4

int buzzer = 4; // Assign pin 4 to buzzer
int potentiometer = A1; // Assign analog pin 5 to potentiometer input
int sensorvalue = 0; // Assign sensorValue to store the value coming form potentiometer
int flash = 0;
int answerdelay = 0;
unsigned long time;
int response = 0;
int restart = 0;
int timeLimit = 3000;

int C3  = 131;
int CS3 = 139;
int D3  = 147;
int DS3 = 156;
int E3  = 165;
int F3  = 175;
int FS3 = 185;
int G3  = 196;
int GS3 = 208;
int noteA3  = 220;
int AS3 = 233;
int B3  = 247;
int C4  = 262;
int CS4 = 277;
int D4  = 294;
int DS4 = 311;
int E4  = 330;
int F4  = 349;
int FS4 = 370;
int G4  = 392;
int GS4 = 415;
int noteA4  = 440;
int AS4 = 466;
int B4  = 494;
int C5  = 523;
int CS5 = 554;
int D5  = 587;
int DS5 = 622;
int E5  = 659;
int F5  = 698;
int FS5 = 740;
int G5  = 784;
int GS5 = 831;
int noteA5  = 880;
int AS5 = 932;
int B5  = 988;
int C6  = 1047;
int CS6 = 1109;
int D6  = 1175;
int DS6 = 1245;
int E6  = 1319;
int F6  = 1397;
int FS6 = 1480;
int G6  = 1568;
int GS6 = 1661;


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++)
    pinMode(leds[i], OUTPUT);
  pinMode (redled, OUTPUT); // Identifies redled as an output
  pinMode (redstate, INPUT_PULLUP); // Identifies redstate as input. (red button)
  pinMode (greenled, OUTPUT);
  pinMode (greenstate, INPUT_PULLUP);
  pinMode (blueled, OUTPUT);
  pinMode (bluestate, INPUT_PULLUP);
  pinMode (yellowled, OUTPUT);
  pinMode (yellowstate, INPUT_PULLUP);
  pinMode (buzzer, OUTPUT);
  pinMode (buzzer, INPUT_PULLUP);
  pinMode (potentiometer, INPUT_PULLUP);

int ledstates[] = {8, 7, 6, 5};
  for (int i = 0; i < 4; i++)
    if (digitalRead(ledstates[i]) == LOW) {
        buzzer = 0;  // Silent Mode
    }


  digitalWrite(redled, HIGH);
  tone (buzzer, redtone, 100);
  delay (100);
  digitalWrite(greenled, HIGH);
  tone (buzzer, greentone, 100);
  delay (100);
  digitalWrite(blueled, HIGH);
  tone (buzzer, bluetone, 100);
  delay (100);
  digitalWrite(yellowled, HIGH);
  tone (buzzer, yellowtone, 100);
  delay (800);
  tone (buzzer, redtone, 500);
  tone (buzzer, greentone, 500);
  tone (buzzer, bluetone, 500);
  delay (1000);
  for (int i = 0; i < 4; i++)
    digitalWrite (leds[i], LOW);
}

void loop() {
  timeLimit = 3000;
  answerdelay = 1000;
  sensorvalue = analogRead(potentiometer);
  if (sensorvalue <= 200) { // Pattern memory
    potentiometerchange();
    for (int i = 0; i < 25; i++) {
      randomNumbers[i] = random(9, 13);
    }
    int counter = 0;
    for (int j = 0; j < 25; j++) {
      counter++;
      for (int i = 0; i < counter; i++) {
        digitalWrite(randomNumbers[i], HIGH);
        tone(buzzer, randomNumbers[i] * 50 - 100, 500);
        delay(500);
        digitalWrite(randomNumbers[i], LOW);
        delay(500);
      }
      if (ledcheck2(counter)) {
        return;
      }
    }
  }
  else if (sensorvalue > 200) { // Wack a mole
    while (1) {
      potentiometerchange();
      if (level()) {
        break;
      }
      delay(2000);
      if (timeLimit > 400) {
        timeLimit /= 2;
      }
    }
  }
}
boolean level()
{
  for (int j = 0; j < 15; j++) {
    if (ledcheck1()) {
      return true;
    }
  }
  return false;
}
void potentiometerchange()
{
  for (int i = 0; i < 4; i++)
    digitalWrite (leds[i], HIGH);
  tone(buzzer, yellowtone, 100);
  delay(100);
  for (int i = 0; i < 4; i++)
    digitalWrite(leds[i], LOW);
  delay(100);
  for (int i = 0; i < 4; i++)
    digitalWrite (leds[i], HIGH);
  tone(buzzer, yellowtone, 100);
  delay(100);
  for (int i = 0; i < 4; i++)
    digitalWrite(leds[i], LOW);
  delay(100);
  for (int i = 0; i < 4; i++)
    digitalWrite (leds[i], HIGH);
  tone(buzzer, yellowtone, 100);
  delay(100);
  for (int i = 0; i < 4; i++)
    digitalWrite(leds[i], LOW);
  delay(100);
  for (int i = 0; i < 4; i++)
    digitalWrite (leds[i], HIGH);
  tone(buzzer, yellowtone, 500);
  delay(500);
  for (int i = 0; i < 4; i++)
    digitalWrite(leds[i], LOW);
  delay(500);
}
void fail()
{
  delay(500);
  Serial.print("fail");
  for (int i = 0; i < 4; i++)
    digitalWrite (leds[i], HIGH);
  tone(buzzer, 554, 40);
  delay (75);
  tone(buzzer, 370, 40);
  for (int i = 0; i < 4; i++)
    digitalWrite (leds[i], LOW);
  delay(200);
  for (int i = 0; i < 4; i++)
    digitalWrite (leds[i], HIGH);
  tone(buzzer, 554, 40);
  delay (75);
  tone(buzzer, 370, 40);
  for (int i = 0; i < 4; i++)
    digitalWrite (leds[i], LOW);
  delay(1000);
}
boolean ledcheck1()
{
  randomNumber = random(9, 13);
  digitalWrite(randomNumber, HIGH);
  tone(buzzer, redtone, 250);

  time = millis();
  //Serial.println(response);

  while (millis() <  time + timeLimit)
  {
    if (digitalRead(randomNumber - 4) == LOW)
    {
      digitalWrite(randomNumber, LOW);
      noTone(buzzer);
      Serial.print("rightanswer");
      delay(300);
      return false;
    }
    else {
      if (wrongbutton1()) {
        break;
      }
    }
  }
  fail();
  return true;
}
boolean wrongbutton1()
{
  response = 0;
  if (digitalRead(redstate) == LOW)
    response = 6;
  if (digitalRead(greenstate) == LOW)
    response = 7;
  if (digitalRead(bluestate) == LOW)
    response = 8;
  if (digitalRead(yellowstate) == LOW)
    response = 5;
  if (response == 0) {
    return false;
  }
  else if (response != randomNumber - 4) {
    return true;
  }
  else if (response == randomNumber - 4)
    return false;
}
boolean ledcheck2(int counter)
{
  Serial.println("ledcheck2");
  boolean failed;
  for (int i = 0; i < counter; i++)
  {
    time = millis();
    while (millis() <  time + timeLimit + 99999999999999999)
    {
      failed = false;
      if (digitalRead(randomNumbers[i] - 4) == LOW)
      {
        Serial.println("rightanswer2");
        delay(300);
        break;
      }
      else {
        if (wrongbutton2(randomNumbers[i])) {
          failed = true;
          break;
        }
      }
    }
    if (failed) break;
  }
  if (!failed) return false;
  fail();
  return true;
}
boolean wrongbutton2(int randomNumber)
{
  response = 0;
  if (digitalRead(redstate) == LOW)
    response = 6;
  if (digitalRead(greenstate) == LOW)
    response = 7;
  if (digitalRead(bluestate) == LOW)
    response = 8;
  if (digitalRead(yellowstate) == LOW)
    response = 5;

  if (response == 0) {
    return false;
  }
  else if (response != randomNumber - 4) {
    Serial.println("wronganswer");
    return true;
  }
  else if (response == randomNumber - 4)
    return false;
}
