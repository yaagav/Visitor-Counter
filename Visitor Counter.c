#include<reg51.h> // Header file name of all 51 families

// Declaring sensors
sbit sen1=P1^0; //entry ,P1.0
sbit sen2=P1^1; //exit , P1.1

// LCD declarations
sbit rs=P1^2; // Register Selector
sbit rw=P1^3; // Read or write operations
sbit en=P1^4; // Enable

// User Defined Functions 
void lcdcmd(unsigned char); //Command
void lcddat(unsigned char); // Data
void delay(); // Delay
void lcddis(unsigned char *s,unsigned char r); // Display function
void lcdconv(unsigned char); // Converting numbers to Decimal

// Main Function
void main() 
{
    unsigned char x,y; // Entry Count and Exit Count variables
    // First we will look at the basic commands we need for 
	// initialising the LCD screen (liquid-crystal display)
	lcdcmd(0x38); // Selecting the crystal for the device
	delay();
	lcdcmd(0x01); // Clearing the screen
	delay();
	lcdcmd(0x10); // Shift the cursor position to right
	delay();
	lcdcmd(0x0c); // To display cursor blinking
	delay();
	lcddis("WELCOME",8); // Displaying WELCOME, size 7
	lcdcmd(0xc0); // Moving cursor to second line
	delay();
	lcddis("VISITOR COUNTER",16);
	delay();
	lcdcmd(0x01); // Clearing the screen
	delay();

	while(1) // While loop
		{
		if(sen1==0) // If logic is zero
		{
		lcdcmd(0x80);
		delay();
		lcddis("ENTRY:",6);
		lcdcmd(0x87);
		delay();
		x=x+1; // Incrementing x value by one (Entry count variable)
		lcdconv(x); // Sending the value to conversion
		}
		if(sen2==0)
		{
		lcdcmd(0xc0); // Moving cursor to second line
		lcddis("EXIT:",5);
		lcdcmd(0xc6);
		delay();
		y=y+1; // Incrementing y value by one (Exit count variable)
		lcdconv(y);
		delay();
		}
	}	}

// Command (Argument)
// Function Description
void lcdcmd(unsigned char val)
{
	P2=val;
	rs=0; // Initialise Logic to 0
	rw=0;
	en=1; // Initialise logic to 1
	delay();
	en=0;
}

void lcddat(unsigned char dat)
{
	P2=dat;
	rs=1;
	rw=0;
	en=1;
	delay();
	en=0;
}

//  		pointer variable, size
void lcddis(unsigned char *s, unsigned char r)
{
	unsigned char w;
	for(w=0;w<r;w++) 
	{
		lcddat(s[w]);
		delay();
	}
}

// Converting the variables into decimal numbers
void lcdconv(unsigned char num)
{
	unsigned char p,n;
	p=num/10;
	n=num%10;
	p=p+0x30; // ASCII Conversion value for displaying the number
	n=n+0x30;
	lcddat(p);
	lcddat(n);
}

// Delay function doesn't have arguments
void delay()
{
	unsigned int k,l;
	for(k=0;k<1000;k++);
	for(l=0;l<100;l++);
}