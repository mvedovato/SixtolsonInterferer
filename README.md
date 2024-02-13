Inversor con SCTimer LPC845.
Genera dos PWMs independientes en OUT0 y OUT1. Cuando OUT0 genera el pwm, OUT1 está en 0 y viceversa (cada 10 ms).
La solución más sencilla funciona correctamente salvo que en los casos de 0% y 100% agrega picos que deforman la forma de onda final. El caso 100% se corrige poniendo un duty mayor al 100%. Para el 0% no hay solución elegante.
Con el ejemplo de AN11538 Two-channel PWM los casos 0% y 100% no parecen generar picos.
Pruebas realizadas:
Trafo de prueba, 220 VCA : 12+12 VCA 3A -> vacío I bobinado de alta por cálculo ~ 30mA.
Inversor con PWM 10 pasos (pwm freq 1KHz):
I  bobinado de baja > 5A, V alta ~ 180VCA, carga en alta 21 K con sonda medición para osciloscopio (10K 1W + 1K 1/2 W + 10K 1W).
Inversor con PWM 1 paso (pwm freq 50Hz -> 100% y 0%, señal cuadrada):
I bobinado de baja ~ 1A, V alta 220VCA, carga en alta 21 K con sonda medición para osciloscopio (10K 1W + 1K 1/2 W + 10K 1W).
Inversor con PWM 5 pasos (pwm 500Hz):
I bobinado de baja , carga en alta 21 K con sonda medición para osciloscopio (10K 1W + 1K 1/2 W + 10K 1W).
