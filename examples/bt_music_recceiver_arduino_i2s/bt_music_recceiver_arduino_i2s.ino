/*
  Streaming Music from Bluetooth
  
  Copyright (C) 2020 Phil Schatzmann
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// ==> Example A2DP Receiver which uses the ESP32 Arduino I2S API

#include "BluetoothA2DPSink.h" // https://github.com/pschatzmann/ESP32-A2DP
#include <I2S.h>

const int sampleRate = 44100; // sample rate in Hz
const int bps = 16;
i2s_mode_t mode = I2S_PHILIPS_MODE; // I2S decoder is needed
BluetoothA2DPSink a2dp_sink;


// Output audio
void write_data_stream(const uint8_t *data, uint32_t length){
    I2S.write(data, length);
}


void setup() {
  Serial.begin(115200);

  // start I2S at the sample rate with 16-bits per sample
  if (!I2S.begin(mode, sampleRate, bps)) {
    Serial.println("Failed to initialize I2S!");
    while (1); // do nothing
  }

  // start a2dp
  a2dp_sink.set_stream_reader(write_data_stream, false);
  a2dp_sink.start("MyMusic");  

}


void loop() {
  delay(1000); // do nothing
}
