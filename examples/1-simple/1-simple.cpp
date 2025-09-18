#include "Particle.h"

#include "CRC32_RK.h"

SYSTEM_MODE(AUTOMATIC);

// System thread defaults to on in 6.2.0 and later and this line is not required
#ifndef SYSTEM_VERSION_v620
SYSTEM_THREAD(ENABLED);
#endif

SerialLogHandler logHandler;

static const unsigned char _testData[10] = {
    0x6d, 0x4e, 0x53, 0x28, 0x4d, 0x3b, 0x3e, 0x4c, 0x6a, 0x77
};


void setup() {

}

void loop() {
    uint32_t calcCrc = CRC32_RK::calculate(_testData, sizeof(_testData));
    if (calcCrc != 0xab08b05c) {
        Log.info("failed CRC check");
    }

    delay(10000);
}