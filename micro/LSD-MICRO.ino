// DMTuino v0.2
// Stroboscopic psychedelic device
// Fork of: AnthonyDavidAdams.com/lsd
// Refactored by JFGilmore

int set_duration();
long light_program(long totalDuration);
//void time_led(int duration);

// Controller constants
const int EFFECT_LED = 13;
const int PLUS_BTN = 9;
const int MINUS_BTN = 10;
const int START_BTN = 11;

const int TIME_1 = 3;
const int TIME_2 = 4;
const int TIME_3 = 5;
const int TIME_4 = 6;
const int TIME_5 = 7;
const int TIME_6 = 8;

/******* WAVE VALUE CONSTANTS *******
  Do not change except for experimental use
*/
const int b = 22;   // beta Hz
const int a = 12;   // alpha/mu Hz
const int d = 3;  // delta Hz
const int t = 6;  // theta Hz
const int g = 32;   // gamma Hz

// [waveform][duration]
const int sequence[][2] {
  {b, 10} ,   // beta
  {a, 10},    // alpha/mu
  {d, 1},     // delta
  {t, 1},     // theta
  {g, 300},   // gamma
  {g, 60},    // gamma
  {t, 60},    // theta
  {d, 60},    // delta
  {a, 60},    // alpha/mu
  {b, 60}     // beta
};

void setup() {
  pinMode(EFFECT_LED, OUTPUT);
  pinMode(PLUS_BTN, INPUT);
  pinMode(MINUS_BTN, INPUT);
  pinMode(START_BTN, INPUT);

  pinMode(TIME_1, OUTPUT);
  pinMode(TIME_2, OUTPUT);
  pinMode(TIME_3, OUTPUT);
  pinMode(TIME_4, OUTPUT);
  pinMode(TIME_5, OUTPUT);
  pinMode(TIME_6, OUTPUT);
  
  Serial.begin(9600);

  Serial.println("DMTuino: Stroboscopic");
  Serial.println();
  Serial.println("█▀▀▄ █▄    ▄█ ███");
  Serial.println("█        █ █    █    █     █    ");
  Serial.println("█▄▄▀ █            █     █    ");
}

void loop() {
  const int t_base = 5; // base time unit in minutes.
  String str_out = "Select time [ " + (String)t_base + "mins -" + (String)t_base + "mins Start ]";
  Serial.println(str_out);

  long duration = set_duration();
  light_program(duration * t_base);
}

int set_duration() {
  int duration = 1;
  int minus, minusPrev, plus, plusPrev, strt = LOW;
  for(int i = TIME_1; i < TIME_6; i++) {
    digitalWrite(i, LOW);
  }
  digitalWrite(TIME_1, HIGH);
  
  while (strt == LOW) {
    minus = digitalRead(MINUS_BTN);
    plus = digitalRead(PLUS_BTN);
    strt = digitalRead(START_BTN);

    if (minus != minusPrev) {
      if (minus == HIGH && duration > 1) {
        duration = duration - 1;
        digitalWrite(duration + TIME_1, LOW);
      } 
    } else if (plus != plusPrev) {
      if (plus == HIGH && duration < 6) {
        digitalWrite(duration + TIME_1, HIGH);
        duration = duration + 1;
      }
    }
    minusPrev = minus;
    plusPrev = plus;
    // Debounce
    delay(50);
  }

  return(duration);
}

long light_program(long totalDuration) {
  unsigned long startMillis = millis();
  float hz = b ;
  int hzDelay = 33;
  int stp, stpPrev = LOW;
  int duration = 0;
  totalDuration = totalDuration * 6000; // time in mins to ms

  for (int i = 0; i < (sizeof sequence / sizeof sequence[0]); i++) {
    duration = sequence[i][1]; // in seconds
    totalDuration = totalDuration + duration;
  }
  
  Serial.println("SEQUENCE STARTED:");
  Serial.print(totalDuration / 6000);
  Serial.println(" Minutes total");
  Serial.println();

  for (int i = 0; i < (sizeof sequence / sizeof sequence[0]); i++) {

    hz = sequence[i][0];
    duration = sequence[i][1]; // in seconds
    
    hzDelay =  (1 / hz) * 1000;
    
    startMillis = millis();
    
    Serial.print("Section: ");
    Serial.print(i);
    Serial.print("\t Frequency: ");
    Serial.print(hz);
    Serial.print("hz \tDelay: ");
    Serial.print(hzDelay);
    Serial.print("\t Duration: ");
    Serial.print(" ");
    Serial.print(duration);
    Serial.print(" Seconds \t Actual: ");
    
    while(((millis() - startMillis)/1000 )< duration) {
      digitalWrite(EFFECT_LED, HIGH);
      delay(hzDelay);
      digitalWrite(EFFECT_LED, LOW);
      delay(hzDelay);

      stp = digitalRead(START_BTN);
      if (stp == HIGH) {
        Serial.println("CANCELLED!");
        Serial.println("Resetting...");
        delay(2000);
        return;
      }
      
    }
    Serial.print((millis() - startMillis)/1000);
    Serial.println(" Seconds");

  }
  Serial.println("SEQUENCE END");
  Serial.println();
  return;
}
//
//void time_led(int duration) {
//  
//}