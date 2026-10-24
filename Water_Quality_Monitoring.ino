#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define TDS_PIN A0
#define ONE_WIRE_BUS 2
#define BUZZER 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 6);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Smiley faces
byte happy[8] = {
  B00000,
  B01010,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

byte sad[8] = {
  B00000,
  B01010,
  B01010,
  B00000,
  B01110,
  B10001,
  B00000,
  B00000
};

// buzzer control
unsigned long previousMillis = 0;
bool buzzerState = false;
const int beepInterval = 200;

// smoothing
float stableTDS = 0;

int readTDS() {
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(TDS_PIN);
    delay(5);
  }
  return sum / 10;
}

void setup() {
  pinMode(BUZZER, OUTPUT);

  lcd.begin(16, 2);
  sensors.begin();

  lcd.createChar(0, happy);
  lcd.createChar(1, sad);

  lcd.setCursor(0, 0);
  lcd.print("Water Quality");
  lcd.setCursor(0, 1);
  lcd.print("Initializing");

  delay(2000);
  lcd.clear();
}

void loop() {

  // Temperature
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  // TDS
  int raw = readTDS();

  float voltage = raw * (5.0 / 1023.0);

  int newTDS = (133.42 * voltage * voltage * voltage
               - 255.86 * voltage * voltage
               + 857.39 * voltage) * 0.5;

  stableTDS = (stableTDS * 0.8) + (newTDS * 0.2);
  int tds = stableTDS;

  // alert condition
  bool alert = (tds < 50 || tds > 500 || temp < 15 || temp > 35);

  // LCD DISPLAY (FIXED)
  lcd.setCursor(0, 0);
  lcd.print("TDS:");
  lcd.print(tds);
  lcd.print("      ");

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temp, 0);
  lcd.print("C ");

  // SMILEY (FIXED POSITION)
  lcd.setCursor(15, 1);

  if (alert) {
    lcd.write(byte(1));  // sad

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= beepInterval) {
      previousMillis = currentMillis;

      buzzerState = !buzzerState;

      if (buzzerState) tone(BUZZER, 1000);
      else noTone(BUZZER);
    }

  } else {
    lcd.write(byte(0));  // happy
    noTone(BUZZER);
    buzzerState = false;
  }
}
