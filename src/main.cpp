/*
 *   Автомат управления воздушной заслонкой ДВС
 *   = vlapa = 20221225 - 20221226
 *   v.002
 */

#include <avr/io.h>
#include <util/delay.h>

#define pin_UP PB1
#define pin_DOWN PB0
#define pin_IN PB4
#define delayPrivodWork 782   //  время работы привода (0.8сек)
#define delayPrivodPause 2300 //  пауза перед сбросом (3сек)

int main(void)
{
  PORTB = 0b00010000;
  PINB = 0b00010000;
  DDRB = 0b00000011;

  PORTB &= (~(1 << pin_DOWN));
  PORTB |= (1 << pin_UP);
  _delay_ms(delayPrivodWork);
  PORTB &= (~(1 << pin_UP));
  PORTB &= (~(1 << pin_DOWN));
  _delay_ms(10);
  PORTB &= (~(1 << pin_UP));
  PORTB |= (1 << pin_DOWN);
  _delay_ms(delayPrivodWork);
  PORTB &= (~(1 << pin_UP));
  PORTB &= (~(1 << pin_DOWN));
  _delay_ms(10);

  while (1)
  {
    PORTB = 0b00010000;
    if (!((1 << pin_IN) & PINB))
    {
      _delay_ms(30);
      if (!((1 << pin_IN) & PINB))
      {
        PORTB |= (1 << pin_UP);
        PORTB &= (~(1 << pin_DOWN));
        _delay_ms(delayPrivodWork);
        PORTB &= (~(1 << pin_UP));
        PORTB &= (~(1 << pin_DOWN));

        while (!((1 << pin_IN) & PINB))
        {
          _delay_ms(10);
          continue;
        }

        if (((1 << pin_IN) & PINB))
        {
          _delay_ms(30);
          if ((1 << pin_IN) & PINB)
          {
            _delay_ms(delayPrivodPause);
            PORTB &= (~(1 << pin_UP));
            PORTB |= (1 << pin_DOWN);
            _delay_ms(delayPrivodWork);
            PORTB &= (~(1 << pin_UP));
            PORTB &= (~(1 << pin_DOWN));
          }
        }
      }
    }
  }
}