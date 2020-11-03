// DMTuino v0.2
// Stroboscopic psychedelic device
// Fork of: AnthonyDavidAdams.com/lsd
// Refactored by JFGilmore

// Controller constants
const unsigned long INTERVAL = 5;

const int EFFECT_LED = 11;
const int PLUS_BTN = 8;
const int MINUS_BTN = 9;
const int START_BTN = 10;

const int LED_METER_1 = 2;
const int LED_METER_2 = 3;
const int LED_METER_3 = 4;
const int LED_METER_4 = 5;
const int LED_METER_5 = 6;
const int LED_METER_6 = 7;

class Display {  
   public:
     Display() {}
     void init() {
       Serial.begin(9600);
       Serial.println();
       Serial.println("DMTuino: Stroboscopic");
       Serial.println("█▀▀▄ █▄░▄█ ███");
       Serial.println("█░░█ █░█░█ ░█░");
       Serial.println("█▄▄▀ █░░░█ ░█░");
     }
     void configure(unsigned long intervalLength) {
       Serial.println("Select time [ " + (String)intervalLength + "mins -" + (String)intervalLength + "mins Start ]");
     }
     void sequenceStatus(unsigned long duration, int section, int frequency) {
       String out = "Section: " + (String)section + " \t Frequency: " + (String)frequency + "hz \t Duration: " + (String)duration + "m";
       Serial.println(out);
     }
     void start(int duration) {
       String out = "SEQUENCE STARTED: " + (String)duration + " mins total\n";
       Serial.println(out);
     }
     void stopSequence() {
       Serial.println("STOPPED\n");
     }
     void pause() {
       Serial.println("PAUSED\n");
     }
     void resume() {
       Serial.println("RESUMED");
     }
 };

class Button {
  protected:
    int pin;
  public:
    unsigned long duration;
    const int noPress = 0;
    const int shortPress = 1;
    const int longPress = 2;
    int state;
    Button(int p) {
      pin = p;
    }
    void init() {
      pinMode(pin, INPUT);
      state = noPress;
    }
    int check() {
      duration = 0;
      int reading = digitalRead(pin);
      unsigned long longPressDuration = 500;

      while (reading == HIGH) {
        duration ++;
        delay(1);
        reading = digitalRead(pin);
      }

      if (duration >= longPressDuration) {
        state = longPress;
        return;
      } else if (duration < longPressDuration && duration != noPress) {
        state = shortPress;
        return;
      } else {
        state = noPress;
        return;
      }
    }
};

class Light {
  protected:
    int pin;
  public:
    const unsigned int minBrightness = 1;
    const unsigned int maxBrightness = 255;
    unsigned int brightness = maxBrightness;
    Light(int p) {
      pin = p;
    }
    void init() {
      pinMode(pin, OUTPUT);
      off();
    }
    ~Light() {
      off();
    }
    void off() {
      digitalWrite(pin, LOW);
    }
    void on(void) {
      digitalWrite(pin, HIGH);
    }
    void on(unsigned int bright) {
      analogWrite(pin, bright);
    }
};

class EffectLight: public Light {
  private:
    unsigned long intervalLength; // base time unit in minutes.
    unsigned long tDuration = 1;
    Display disp = Display();
    Button plus = Button(PLUS_BTN);
    Button minus = Button(MINUS_BTN);
    Button startStop = Button(START_BTN);
    Light minLight = Light(LED_METER_1);
    Light oneLight = Light(LED_METER_2);
    Light twoLight = Light(LED_METER_3);
    Light threeLight = Light(LED_METER_4);
    Light fourLight = Light(LED_METER_5);
    Light maxLight = Light(LED_METER_6);
    unsigned int brightness = 255;
    /******* WAVEFORM CONSTANTS *******
    Only change for experimental purposes
    */
    const int b = 22; // beta Hz
    const int a = 10; // alpha Hz => high intensity, simple visual hallucinations
    const int d = 3;  // delta Hz => low intensity, complex visual hallucinations
    const int t = 6;  // theta Hz
    const int g = 32; // gamma Hz
    // Sequence of opperating pattern [frequency(Hz)][duration(ms)]
    const int sequence[6][2] = {
      {b, 1},
      {g, 1},
      {a, 2},
      {d, 2},
      {g, 3},
      {t, 1}
    };

  public:
    EffectLight(int pin, unsigned long interval): Light(pin) {
      intervalLength = interval;
    }
    void init() {
      Light::init();
      minLight.init();
      oneLight.init();
      twoLight.init();
      threeLight.init();
      fourLight.init();
      maxLight.init();
      plus.init();
      minus.init();
      startStop.init();
      disp.init();
    }
    void configure() {
      disp.configure(intervalLength);
      while (startStop.state != startStop.shortPress)
      {
        // Set bightness & duration
        plus.check();
        minus.check();
         if (plus.state == plus.longPress) {
           brightness += 20;
           brightness = (brightness > maxBrightness ? maxBrightness : brightness);
           on(brightness);
         } else if (minus.state == minus.longPress) {
           brightness -= 20;
           brightness = (brightness < minBrightness ? minBrightness : brightness);
           on(brightness);
         } else 
        if (plus.state == plus.shortPress && tDuration < 6) {
           tDuration ++;
           digitalWrite(tDuration, HIGH);
        } else if (minus.state == minus.shortPress && tDuration > 1) {
           digitalWrite(tDuration, LOW);
           tDuration --;
        }
        delay(50);
        startStop.check();
      }
      return;
    }

    long runSequence(unsigned long duration, unsigned int bright) {
      tDuration = duration;
      brightness = bright;
      runSequence();
    }
    long runSequence() {
      disp.start(tDuration * intervalLength);
      unsigned long startMillis;
      unsigned long pauseMillis;
      int hz;
      int hzDelay;
      unsigned long duration;

      for (int repeat = tDuration; repeat > 0; repeat--) {
        for (int i = 0; i < (sizeof sequence / sizeof sequence[0]); i++) {
          hz = sequence[i][0];
          duration = sequence[i][1]; // in seconds
          hzDelay = 1000 / hz;
          startMillis = millis();

          disp.sequenceStatus(duration, i, hz);
          
          while((millis() - startMillis) < duration * 60000) {
            on(brightness);
            delay(hzDelay);
            off();
            delay(hzDelay);

            startStop.check();
            if (startStop.state == startStop.shortPress) {
              // Pause
              pauseMillis = millis();
              disp.pause();
              do {
                delay(50);
                startStop.check();
              } while (startStop.state == startStop.noPress);
              disp.resume();
              startMillis -= (millis() - pauseMillis);
            }
            if (startStop.state == startStop.longPress) {
              // Stop
              disp.stopSequence();
              startStop.state = startStop.noPress;
              return;
            }
          }
        }
        digitalWrite(tDuration, LOW);
      }
    }
};

EffectLight effectLed(EFFECT_LED, INTERVAL);

void setup() {
  effectLed.init();
}

void loop() {
  effectLed.configure();
  effectLed.runSequence();
}