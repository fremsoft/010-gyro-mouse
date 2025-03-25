#include <Adafruit_BMP085.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <AbsMouse.h>

#define CLICK_TH        60
#define UNCLICK_TH      40
#define T_MIN_CLICK_MS 500

// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)

Adafruit_BMP085 bmp;
Adafruit_MPU6050 mpu;

int32_t p, fp;
bool clicked;
int32_t t0_click, t1_click, t2_click, t_unclick;
float axf, ayf, azf;
int32_t x, y, xp, yp;


void setup() {
  Serial.begin(9600);

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  delay(2000);

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  clicked = false;
  t0_click = t1_click = t2_click = t_unclick = 0;

  fp = (float)bmp.readPressure();

  axf = ayf = azf = 0.0;
  x = y = 0;
  xp = yp = -1;

  AbsMouse.init(1920, 1080);  // full HD
}

void loop() {
  int32_t t;
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  axf = ((49.0 * axf) + a.acceleration.x) / 50.0;
  ayf = ((49.0 * ayf) + a.acceleration.y) / 50.0;
  azf = ((49.0 * azf) + a.acceleration.z) / 50.0;

  y = constrain(
    map((long)(10000.0 * atan2(axf, ayf)), -1000, 1000, 1080, 0),
    0, 1080);
  x = constrain(
    map((long)(10000.0 * atan2(azf, ayf)), -1000, 1000, 1920, 0),
    0, 1920);

  p = (float)bmp.readPressure();
  fp = ((fp * 999.0) + p) / 1000.0;

  t = millis();
  if ((!clicked) && (abs(fp - p) > CLICK_TH)) {
    clicked = true;
    if ((t - t2_click) > T_MIN_CLICK_MS) {
      /* primo impulso */
      t0_click = t1_click = t2_click = t;
//Serial.println("primo");
    }
    else if ((t - t0_click) < T_MIN_CLICK_MS) {
      /* secondo impulso */
      t1_click = t2_click = t;
//Serial.println("secondo");
    }    
    else if ((t - t1_click) < T_MIN_CLICK_MS) {
      /* terzo impulso di fila */
      t2_click = t;
//Serial.println("terzo");
    }    
  }
  
  if (clicked) {
    /* se è passato il tempo clicco sinistro */
    if ((t - t0_click) > T_MIN_CLICK_MS) {
      AbsMouse.press(MOUSE_LEFT);
//Serial.println("click");
    }

    /* quando ho rilasciato, entro il tempo aspetto e valuto */
    if (abs(fp - p) < UNCLICK_TH) {
      /* preparo la variabile clicked per accettare altri click */
      clicked = false;
    }
  }
  else {
    /* se è passato il tempo rilascio sinistro */
    if ((t - t2_click) > T_MIN_CLICK_MS) {
      if (t0_click != 0) {
        if (t0_click == t1_click) {
          /* click semplice */
//Serial.println("click semplice");
          AbsMouse.press(MOUSE_LEFT);
          delay(100);
          AbsMouse.release(MOUSE_LEFT);
        }
        else 
        if (t1_click == t2_click) {
          /* doppio click */
//Serial.println("doppio click");
          AbsMouse.press(MOUSE_LEFT);
          delay(100);
          AbsMouse.release(MOUSE_LEFT);
          delay(100);
          AbsMouse.press(MOUSE_LEFT);
          delay(100);
          AbsMouse.release(MOUSE_LEFT);
        }
        else {
          /* triplo click == tasto destro */
//Serial.println("triplo click");
          AbsMouse.release(MOUSE_LEFT);
          AbsMouse.press(MOUSE_RIGHT);
          delay(100);
          AbsMouse.release(MOUSE_RIGHT);
        }
        t0_click = 0;
      }
    }
  }

  if ((abs(x - xp) > 10) || (abs(y - yp) > 10)) {
    AbsMouse.move(x, y);

    xp = x;
    yp = y;
  }

  //Serial.print(p);
  //Serial.print(",");
  //Serial.println(fp);
  //Serial.print(",");
  //Serial.print(clicked);
  //Serial.print(",");
  //Serial.print(x);
  //Serial.print(",");
  //Serial.println(y);
}
