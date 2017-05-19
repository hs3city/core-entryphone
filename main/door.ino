#include "header.h"

door::door(int pin) : pinOperator(pin)
{
    close();
}

void door::open()
{
    digitalWrite(PIN, LOW);
    delay(1000);
    close();
}

void door::close()
{
    digitalWrite(PIN, HIGH);
}
