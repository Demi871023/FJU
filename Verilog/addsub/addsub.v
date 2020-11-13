//This module is the highest level of the module.
// it includes all the input and output in the DE2-70
module addsub(
// Clock Input (50 MHz)
  input  CLOCK_50,
  //  Push Buttons
  input  [3:0]  KEY,
  //  DPDT Switches 
  input  [17:0]  SW,
  input M,
    //  7-SEG Displays
  output  [6:0]  HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7,
  //Declare Sum which is 8-bits long
  output [3:0] sum,count,
   // This is added to the convert the 8-bits to different HEX_
  output [3:0] ONES, TENS,
  output [3:0] HUNDREDS,
  //  LEDs
  output  [8:0]  LEDG,  //  LED Green[8:0]
  output  [17:0]  LEDR, //  LED Red[17:0]
  //  GPIO Connections
  inout  [35:0]  GPIO_0, GPIO_1
);
//  set all inout ports to tri-state
	assign  GPIO_0    =  36'hzzzzzzzzz;
	assign  GPIO_1    =  36'hzzzzzzzzz;

// Connect dip switches to red LEDs
	assign LEDR[17:0] = SW[17:0];
	wire [15:0] A;
	
	assign bin = 1'b0;
//    A <= SW[15:0];
// I am adding this code to subtractor 4 bits code
	fouradd_sub(sum,count,SW[3:0],SW[7:4],SW[17]);
	hex_7seg dsp0(sum,HEX0);
	assign HEX1 = blank;
	assign HEX2 = blank;
	assign HEX3 = blank;
	assign HEX4 = blank;
	assign HEX5 = blank;
	assign HEX6 = blank;
	assign HEX7 = blank;

	wire [6:0] blank = ~7'h00;
	assign A = SW[15:0];
	
endmodule
