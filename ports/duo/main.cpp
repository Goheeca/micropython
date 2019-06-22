
#include "application.h"
#include "wiring.h"

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

void setup_button_handler(system_event_t event, int param)
{
  int times = system_button_clicks(param);
  if(times == 3) {
    clear_filesystem();
    soft_reset();
  }
}

void setup()
{
  System.on(button_final_click, setup_button_handler);
  mp_heap();
}

void loop()
{
	mp_setup();
	mp_loop();
}
