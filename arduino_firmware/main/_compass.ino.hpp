#include <Arduino.h>
#include "modules.hpp"


// Unlike header file (.hpp), module implementation file (.ino.hpp) must not be included multiple times:
#ifdef COMPASS_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .hpp file instead?
#endif
#define COMPASS_INO_HPP
#include "_compass.hpp"


#ifndef DECLINATION_HPP
  #warning compass module compiled without declination modules, assuming 0.0 declination!
#endif

void Compass::setup()
{
    // prepare averaging buffer
    for (int i=0; i<COMPASS_AVERAGE_BUFFER; i++) {
        average[i] = 0;
    }


    #ifndef DECLINATION_HPP
      Serial.print(F("Warning: compass module compiled without declination modules, assuming 0.0 declination!\n"));
    #endif
}


void Compass::loop()
{

  //TODO make the efort to make compass module independent of other modules
  // e.g. if no calibrations, take range from precision
  // if no acc, use only simple x/y magnetic bearing
  // if no magnetometer... ok, then can break

  // don't do anyhing else if not calibrated:
  if (!mag_calibration->calibrated) return;
  if (!acc_calibration->calibrated) return;

  // also, magnetometer and accelerometer must have been inited:
  if (!magnetometer->inited) return;
  if (!accelerometer->inited) return;

  #ifdef DECLINATION_HPP
    if (declination->inited) {
      alpha = declination->declination;
    }
  #endif

  // enter loop only every COMPASS_LOOP_INTERVAL millis:
  uint32_t now = millis();
  if (now - last_loop < COMPASS_LOOP_INTERVAL) return;
  last_loop = now;
  // set the "inited" flag:
  inited = true;

  // module of the magnetic vector:
  B = sqrt(
      pow(magnetometer->x, 2.0) +
      pow(magnetometer->y, 2.0) +
      pow(magnetometer->z, 2.0)
  );

  /*
  Serial.print("\n");
  Serial.print("B: ");
  Serial.println(B);
  */

  // other angles, ref. calculations:
  phi = atan2(
      -1 * magnetometer->y,  // FIXME accelerometer, not magnetometer!
      magnetometer->z
  );
  /*
  Serial.print("phi: ");
  Serial.println(rad2deg(phi));
  */

  theta = atan(
      -1 * magnetometer->x /
      (magnetometer->y * sin(phi) - magnetometer->z * cos(phi))
  );
  /*
  Serial.print("theta: ");
  Serial.println(rad2deg(theta));
  */

  delta = asin(
      1.0 * magnetometer->x / B * sin(theta) -
      1.0 * magnetometer->y / B * cos(theta) * sin(phi) +
      1.0 * magnetometer->z / B * cos(theta) * cos(phi)
  );
  /*
  Serial.print("delta: ");
  Serial.println(rad2deg(delta));
  */

  /*
  Serial.print(magnetometer->x);
  Serial.print("\t");
  Serial.print(magnetometer->y);
  Serial.print("\t");
  Serial.print(magnetometer->z);
  Serial.print("\t");
  Serial.print(B);
  Serial.print("\t");
  Serial.print(rad2deg(delta));
  */
//  Serial.print("  ");
  //Serial.print(rad2deg(theta));
  //Serial.print("\n");
  Dx = (
      magnetometer->x * cos(theta) +
      magnetometer->y * sin(theta) * sin(phi) -
      magnetometer->z * sin(theta) * cos(phi)
  ) / (
      B * cos(delta)
  );
  Dy = (
      magnetometer->y * cos(phi) +
      magnetometer->z * sin(phi)
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

  // TODO apply offset!
}
