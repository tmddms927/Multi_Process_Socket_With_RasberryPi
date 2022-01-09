#include "header.h"

void *thread_sensor(void *arg)
{
	int a = 0;
	a = psd_sensor();
	while (1)
	{
		if (a <= 20 || gate_open == 1)
		{
			//초음파센서를 통해 키 값 받기
			digitalWrite(trigPin, LOW);
			usleep(2);
			digitalWrite(trigPin, HIGH);
			usleep(20);
			digitalWrite(trigPin, LOW);
			while (digitalRead(echoPin) == LOW)
				;
			startTime = micros();
			while (digitalRead(echoPin) == HIGH)
				;
			travelTime = micros() - startTime;
			distance = travelTime * 17 / 1000;
			sprintf(message, "%d", distance);
			pthread_mutex_lock(&mutx);
			boolean = 2;
			pthread_mutex_unlock(&mutx);
		}
		else
		{
			distance = 180;
			sprintf(message, "%d", distance);
			pthread_mutex_lock(&mutx);
			boolean = 2;
			pthread_mutex_unlock(&mutx);
		}
		a = 0;
		sleep(10);
		a = psd_sensor();
	}
}
