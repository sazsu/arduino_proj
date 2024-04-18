// C++ code
//
#include <Servo.h>
// Подключение сервопривода
Servo myservo;
// Пин для ультразвукового датчика 
const int trigPin = 9;
const int echoPin = 10;
// Пин для управления платформой 
const int platformPin = 7;
// Ширина дороги (расстояние столбов на разных сторонах дороги)
const int roadWidth = 100;
// Среднее расстояние от столба до транспортного средства
const int poleDistance = 20;
// Счетчик времени
int time = 0;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(platformPin, OUTPUT);
    // Подключение сервопривода 
    myservo.attach(7);
    // Установка начального положения платформы 
    digitalWrite(platformPin, HIGH);
    // Инициализация последовательного порта для мониторинга
    myservo.write(0);
    delayMicroseconds(2);
}

void loop() {
    // Отправка ультразвукового сигнала
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Измерение времени прохождения звука до препятствия
    long duration = pulseIn(echoPin, HIGH);
    // Расчет расстояния до препятствия в сантиметрах
    int distance = (duration * 0.034) / 2;
    // Транспортное средство проезжает мимо датчика медленнее,
    // чем человек проходит мимо него
    // Измерение времени прохождения объекта мимо датчика
    if (distance <= roadWidth && distance >= poleDistance) {
      time += 100;
    }
    else {
      time = 0;
    }
    if (time >= 1000) {
        myservo.write(90);
        delay(2000);
        myservo.write(0);
    }
    // Задержка между измерениями
    delay(100);
}