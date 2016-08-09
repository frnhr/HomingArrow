#include <Arduino.h>
#include "modules.hpp"

#include "_compass.hpp"

#include "_magnetometer.hpp"
#include "_mag_calibration.hpp"
#include "hardware_config.h"


// Unlike header file (.hpp), module implementation file (.ino.hpp) must not be included multiple times:
#ifdef COMPASS_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .hpp file instead?
#endif
#define COMPASS_INO_HPP


void Compass::setup()
{
    // prepare averaging buffer
    for (int i=0; i<COMPASS_AVERAGE_BUFFER; i++) {
        average[i] = 0;
    }
}


void Compass::loop()
{

  // don't do anyhing else if not calibrated:
  if (!mag_calibration->calibrated) return;

  // also, magnetometer must have been inited:
  if (!magnetometer->inited) return;

  // enter loop only every COMPASS_LOOP_INTERVAL millis:
  uint32_t now = millis();
  if (now - last_loop < COMPASS_LOOP_INTERVAL) return;
  last_loop = now;
  // set the "inited" flag:
  inited = true;

  // normalize range for each axes:
  float f = 1.0 * COMPASS_RESOLUTION / mag_calibration->z_range;
  cal_x = (magnetometer->m_x - mag_calibration->x_min) * f;
  cal_y = (magnetometer->m_y - mag_calibration->y_min) * f;
  cal_z = (magnetometer->m_z - mag_calibration->z_min) * f;

  // module of the magnetic vector:
  B = sqrt(
      pow(cal_x, 2.0) +
      pow(cal_y, 2.0) +
      pow(cal_z, 2.0)
  );

  Serial.print("\n");
  Serial.print("B: ");
  Serial.println(B);

  // other angles, ref. calculations:
  phi = atan2(
      -1 * magnetometer->m_y,  // FIXME accelerometer, not magnetometer!
      magnetometer->m_z
  );
  Serial.print("phi: ");
  Serial.println(rad2deg(phi));
  theta = atan(
      -1 * magnetometer->m_x /
      (magnetometer->m_y * sin(phi) - magnetometer->m_z * cos(phi))
  );
  Serial.print("theta: ");
  Serial.println(rad2deg(theta));
  delta = asin(
      1.0 * cal_x / B * sin(theta) -
      1.0 * cal_y / B * cos(theta) * sin(phi) +
      1.0 * cal_z / B * cos(theta) * cos(phi)
  );
  Serial.print("delta: ");
  Serial.println(rad2deg(delta));
  /*
  Serial.print(cal_x);
  Serial.print("\t");
  Serial.print(cal_y);
  Serial.print("\t");
  Serial.print(cal_z);
  Serial.print("\t");
  Serial.print(B);
  Serial.print("\t");
  Serial.print(rad2deg(delta));
  */
//  Serial.print("  ");
  //Serial.print(rad2deg(theta));
  //Serial.print("\n");
  Dx = (
      cal_x * cos(theta) +
      cal_y * sin(theta) * sin(phi) -
      cal_z * sin(theta) * cos(phi)
  ) / (
      B * cos(delta)
  );
  Dy = (
      cal_y * cos(phi) +
      cal_z * sin(phi)
  ) / (
      B * cos(delta)
  );
  psi = asin(
      Dy * cos(alpha) - Dx * sin(alpha)
  );

/*
  if (Dx < 0) {
      psi = M_PI - psi;
  }
*/
  /***** Put it into average buffer *****/
  average_i++;
  average_i = average_i % COMPASS_AVERAGE_BUFFER;
  average[average_i] = psi;

  /***** Calculate azimuth *****/
  azimuth = 0;
  for (int i=0; i<COMPASS_AVERAGE_BUFFER; i++) {
      azimuth += average[i] / COMPASS_AVERAGE_BUFFER;
  }
}
