#include <chrono>
#include <cstdio>
#include <iostream>
#include <string>
#include <thread>

#include <gpiod.hpp>

#include <driver/device.hpp>
#include <driver/drf7020d20.hpp>
#include <driver/pinmap.hpp>
#include <shared/messages.hpp>
#include "intersection.hpp"

int main() {

	drf7020d20 rf_test(gpio_pins, RASPI_40, RASPI_37, RASPI_38, 0);
	rf_test.enable();
	rf_test.configure(
		433900, drf7020d20::DR9600, 9, drf7020d20::DR9600, drf7020d20::NONE);

	/*init cars at int*/
	car_t car[3] = {};

	/*message init*/
	const msg_t sby_msg = {
		.caller_id = "1",
		.receiver_id = "1",
		.body = "SBY",
	};
	
	const msg_t grq_msg = {
		.caller_id = "1",
		.receiver_id = "1",
		.body = "GRQ",
	};

	const msg_t sbg_msg = {
		.caller_id = "1",
		.receiver_id = "1",
		.body = "SBG",
	};

	const msg_t rg1_msg = {
		.caller_id = "1",
		.receiver_id = "1",
		.body = "RG1",
	};

	const msg_t rg2_msg = {
		.caller_id = "1",
		.receiver_id = "1",
		.body = "RG2",
	};

	const msg_t rg3_msg = {
		.caller_id = "1",
		.receiver_id = "1",
		.body = "RG3",
	};

	const msg_t rg4_msg = {
		.caller_id = "1",
		.receiver_id = "1",
		.body = "RG4",
	};

	/*receive message*/
	std::string new_msg_str = rf_test.receive(std::chrono::seconds(100));
	
	msg_t new_msg;
	std::string caller_id;
	std::string body;

	try {

		new_msg = parse_message(new_msg_str);
		caller_id = new_msg.caller_id;
		body = new_msg.body;

		//find current car
		car_t current_car;
		std::string car_pos = current_car.entrance_pos;

		if (body == "CHK") {
			rf_test.receive(std::chrono::seconds(100)); // expect to receive CHK
		} else if (body == "PS1") {
			//update current car position
		} else if (body == "PS2") {

		} else if (body == "PS3") {

		} else if (body == "PS4") {

		} else if (body == "RQ1") {
			
			//if car is at position 2:
			// check if there is a cars at position 1 wants to go straight or left
			// check if cars at position 3 or 4 are requesting to go to position 1
			// check if cars at position 3 or 4 are requesting to go to position 2

			// if car at position 3:
			// Check if car at position 2 is requesting 4 or vice versa
			// compare times between current car and car at position 2 

			// if car at position 4:
			// Check if car at position 3 and requesting position 1

			// if none of these cases match, then stand by / redirect
			// else proceed as requested

		} else if (body == "RQ2") {
			
		} else if (body == "RQ3") {

		} else if (body == "RQ4") {

		} 	

	} catch (const std::exception& e) { //invalid messgae
		rf_test.transmit(format_message(sby_msg));
	}

	return 0;
}
