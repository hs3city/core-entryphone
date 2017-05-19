#include "header.h"

indicator::indicator(int pin) : pinOperator(pin)
{
    on();
}
void indicator::blink()
{
    off();
    delay(250);
    on();
    delay(250);
}

void indicator::on()
{
    digitalWrite(PIN, LOW);
}

void indicator::off()
{
    digitalWrite(PIN, HIGH);
}