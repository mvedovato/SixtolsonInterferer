# Interferómetro de Sixtolson
Tecla de cambio de modo es tecla ISP, amanece en este orden el modo:
1. Modo FREE
2. Modo SWEEP
3. Modo Random

## Modo FREE
1. Genera PWM en OUT0 en pasos de 1% con tecla user.

## Modo SWEEP
1. Genera PWM en OUT0 en 21 pasos de 5%
2. Pasos de 5% cada 10 0 100 ms según se aprete la tecla user.

## Modo RANDOM
1. Genera un índice random del vector de duties.
2. Refresco cada 10 0 100 ms según se aprete la tecla user.

## Impresión por UART1 de parámetros
1. Valores de dutyFree, span y vecDuty[i] por UART1.
