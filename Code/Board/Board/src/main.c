/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>

#include <avr/io.h>
#include <util/delay.h>

#define portA 0
#define portB 1
#define portC 2
#define portD 3
#define portE 4

char lookup_table[16] ={
	0b11111100, //0
	0b01100000, //1
	0b11011010, //2
	0b11110010, //3
	0b01100110, //4
	0b10110110, //5
	0b10111110, //6
	0b11100000, //7
	0b11111110, //8
	0b11110110, //9
	0b11101110, //A
	0b00111110, //B
	0b10011100, //C
	0b01111010, //D
	0b10011110, //E
	0b10001110  //F
};

int display_pins[8][2] = {
	{portB, 0}, //seg0
	{portB, 1}, //seg1
	{portB, 2}, //seg2
	{portB, 3}, //seg3
	{portB, 4}, //seg4
	{portB, 5}, //seg5
	{portB, 6}, //seg6
	{portB, 7}  //seg7
};

int digit0_input_pins[4][2] = {
	{portC, 1}, //input0
	{portC, 0}, //input1
	{portE, 2}, //input2
	{portE, 3}  //input3
};

int digit1_input_pins[4][2] = {
	{portD, 3}, //input4
	{portD, 4}, //input5
	{portE, 1}, //input6
	{portB, 6}  //input7
};

int get_pin(int input_pin[2]){
	int data;
	switch(input_pin[0]){
		case portB:
		data = PINB;
		break;
		case portC:
		data = PINC;
		break;
		case portD:
		data = PIND;
		break;
		case portE:
		data = PINE;
		break;
	}
	return (data & (1 << input_pin[1])) >> input_pin[1];
}

void set_pin(int input_pin[2], int state){
	int mask = ~(1 << input_pin[1]);
	switch(input_pin[0]){
		case portB:
		if(state)
		PORTB |= (1 << input_pin[1]);
		else
		PORTB &= mask;
		break;
		case portC:
		if(state)
		PORTC |= (1 << input_pin[1]);
		else
		PORTC &= mask;
		break;
		case portD:
		if(state)
		PORTD |= (1 << input_pin[1]);
		else
		PORTD &= mask;
		break;
		case portE:
		if(state)
		PORTE |= (1 << input_pin[1]);
		else
		PORTE &= mask;
		break;
	}
}

int main(void) {
	// Initialization code
	board_init();
	//set outputs

	/*
	int display_pins[8][2] = {
		{portC, 6}, //seg0
		{portB, 3}, //seg1
		{portD, 7}, //seg2
		{portD, 6}, //seg3
		{portD, 5}, //seg4
		{portB, 2}, //seg5
		{portB, 0}, //seg6
		{portB, 7}  //seg7
	};

	*/
	DDRB |= (1 << 0) | (1 << 2) |(1 << 3) | (1 << 4) | (1 << 5) |(1 << 7); // Set pins 0, 2, 3 and 7 of port B as outputs
	DDRC |= (1 << 6); // Set pin 6 of port C as an output
	DDRD |= (1 << 5) | (1 << 6) | (1 << 7); // Set pin 5, 6, and 7 of port D as outputs
	
	
	DDRC &= ~((1 << 0) | (1 << 1)); // Set pin 0 and 1 of port C as inputs
	PORTC &= ~((1 << 0) | (1 << 1));
	DDRE &= ~((1 << 1) | (1 << 2) | (1 << 3)); // Set pin 1, 2, and 3 of port E as inputs
	PORTE &= ~((1 << 1) | (1 << 2) | (1 << 3));
	DDRD&= ~(1 << 4);
	PORTD &= ~(1 << 4);
	DDRB &= ~(1 << 6); // Set pin 6 of port B as an input
	PORTB &= ~(1 << 6);
	int num_to_display = 0;
	

		
	while (1) {
		//get inputs stage
		
		//get rotary switch
		
		//get buttons
		
		
		//get inputs from board
		
		
		//set outputs stage
		
		//set board outputs
		
		
		//output numbers
		num_to_display = 0;

		seven_segment_display(1,num_to_display); //digit 1

		
		_delay_ms(10);
		
		seven_segment_display(0,num_to_display); //digit 0
		
		
		
		_delay_ms(10);
		
	}
}


void seven_segment_display(int digit,int num_to_display){
	int digit0[2] = {portD,5};
	int digit1[2] = {portD,6};
	if(!digit){
		set_pin(digit1, 0);
		// Display digit 0
		for (int i = 0; i < 8; i++) {
			set_pin(display_pins[7-i], !(lookup_table[num_to_display] & (1 << i)));
		}

		set_pin(digit0, 1);
	}
	else{
		set_pin(digit0, 0);
		// Display digit 1
		for (int i = 0; i < 8; i++) {
			set_pin(display_pins[7-i], !(lookup_table[num_to_display] & (1 << i)));
		}
		set_pin(digit1, 1);
	}
	
}