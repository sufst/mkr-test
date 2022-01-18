#include "src/sys/sys__manager.h"

void setup() {
    sys__manager__init();
}

void loop() {
    sys__manager__process();
}