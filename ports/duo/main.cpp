
#include "application.h"
#include "wiring.h"

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

void setup()
{
  mp_heap();
}

void loop()
{
	mp_setup();
	mp_loop();
}
