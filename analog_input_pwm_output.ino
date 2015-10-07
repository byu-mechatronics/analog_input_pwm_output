/*****************************************************
analog_input_pwm_output.ino

Walter Coe, 10-07-15
BYU Mechatronics Club

This code takes an analog input and converts it to a PWM output, which
can be used to drive a motor, LED, or as a form of analog output.

*****************************************************/

const int pwmOut = 3;			//Define the output pin. Only certain pins can produce PWM output. Check Arduino's website
const int analogIn = A0;		//Define the input pin.

float values[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	//This is for a simple digital filter for analog input


void setup()
{
	Serial.begin(9600);			//Setup serial for printing to the screen
	pinMode(pwmOut, OUTPUT);	//Set pin direction
	pinMode(analogIn, INPUT);	//set pin direction
}

void loop()
{
	float value = (analogRead(analogIn)*.2656);		//Scale from 10-bit input to 8-bit output. ((2^8)-1)/((2^10)-1) = .2656
	
	updateValues(value);					//Adds new value to values array (for filtering)
	
	value = averageValue();					//Averages the values array (simple digital filter)
	
	Serial.print((value/255.0)*100.0);		//Print to the screen the duty cycle as a percentage
	Serial.println("%");
	
	analogWrite(pwmOut, value);				//Set PWM on the pin using analogWrite()
}


float averageValue()
{
	float sum = 0;
	for(int i = 0; i < 10; i++)
	{
		sum = sum + values[i];
	}
	return(sum/10.0);
	
}

void updateValues(float newValue)
{
	for(int i = 0; i < 9; i++)
	{
		values[i] = values[i + 1];
	}
	values[9] = newValue;
}