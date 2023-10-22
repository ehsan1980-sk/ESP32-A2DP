#pragma once

#ifndef AUTOCONNECT_TRY_NUM
#  define AUTOCONNECT_TRY_NUM 1000
#endif

// Activate I2S Support 
#ifndef A2DP_I2S_SUPPORT
#  define A2DP_I2S_SUPPORT true
#endif

// Max I2S write size  
#ifndef A2DP_I2S_MAX_SIZE
#  define A2DP_I2S_MAX_SIZE 1024
#endif


// Use https://github.com/pschatzmann/arduino-audio-tools as output library: 
#ifndef A2DP_I2S_AUDIOTOOLS
#  define A2DP_I2S_AUDIOTOOLS true
#endif

#ifndef A2DP_SPP_SUPPORT
#  define A2DP_SPP_SUPPORT (ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0))
#endif

// log all writes of audio data with log level debug (set to true of false) 
#ifndef A2DP_DEBUG_AUDIO
#  define A2DP_DEBUG_AUDIO true
#endif
