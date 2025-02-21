// No. d'étudiant
// 2370489

const int ledPins[] = { 8, 9, 10, 11 };  // Tableau des numéros de broches
const int potentiometerPin = A1;
const int buttonPin = 2;
int ledIndex = 0;  // Index du DEL allume
const int ledSize = sizeof(ledPins) / sizeof(ledPins[0]);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < 4; i++) {
    // Initialisation des DEL en sortie
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.println("Setup Completed");
}

int isClicked() {
  const int time = 10;
  static unsigned long long int lastTimeClicked;
  static int lastState = 1;
  int click = 0;

  if (millis() - lastTimeClicked < time) {
    return click;
  }

  lastTimeClicked = millis();
  int currentState = digitalRead(buttonPin);
  if (currentState == 0 && currentState != lastState) {
    click = 1;

}
  lastState = currentState;
  return click;
}

void progressionBar(int mappedValue, int mappedPercent) {

  Serial.print("[");
  for (int i = 0; i < mappedValue; i++) {
    Serial.print("#");
  }
  for (int i = 20; i > mappedValue;i--) {
    Serial.print(".");
  }
  Serial.print("] "); 
  Serial.print(mappedPercent);
  Serial.println("%");

}

void powerLeds(int mappedLedIndex) {
  for (int i = 0; i <= ledSize ; i++) {
      if (i == mappedLedIndex) {
        digitalWrite(ledPins[i], HIGH);
      } else {
        digitalWrite(ledPins[i], LOW);
      }
    }
}

void loop() {
  // put your main code here, to run repeatedly:
    int potentiometerValue = analogRead(potentiometerPin);
    int mappedPotentiometerValue = map(potentiometerValue, 0, 1023, 0, 20);
    int mappedPotentiometerPercent = map(potentiometerValue, 0, 1023, 0, 100);
    int mappedLedIndex = map(potentiometerValue, 0, (1023 + 1), 0, ledSize); // le 1023 + 1 sert à que mappedLedIndex n'atteigne jamais 4

  int clic = isClicked();
  if (clic) {
    progressionBar(mappedPotentiometerValue, mappedPotentiometerPercent);
    }

  powerLeds(mappedLedIndex);
}
