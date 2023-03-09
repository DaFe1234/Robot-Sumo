#include <NHCSR04.h>

int baudrate = 9600;

int triggerPinIzq = A0;
int echoPinIzq = A1;

SR04 sensorIzq(triggerPinIzq, echoPinIzq);

double MedidaIzq;
//----------Ultrasonido Derecha-----------(Visto de frente)
int triggerPinDer = A2;
int echoPinDer = A3;

SR04 sensorDer(triggerPinDer, echoPinDer);

double MedidaDer;

void setup()
{
    Serial.begin(baudrate);
}

void loop()
{
    MedidaIzq = sensorIzq.centimeters();
    MedidaDer = sensorDer.centimeters();
    Serial.print("cm: ");
    Serial.print(MedidaIzq);
    Serial.print("        cm: ");
    Serial.println(MedidaDer);
}
