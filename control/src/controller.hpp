/**
 * @file src/controller.hpp
 * @brief handles control logic of cars
 */
#pragma once

#include <cstdlib>
#include <deque>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include <driver/drf7020d20.hpp>
#include <shared/tdma.hpp>

#include "messageworker.hpp"

class controller {
public:
	enum car_state {
		CHECKIN,
		STANDBY,
		MOVING,
	};

	struct car {
		std::string car_id;
		car_state state;
		uint8_t current_pos;
		uint8_t request_pos;
	};

	/**
	 * @brief constuctor for message worker
	 * @param[in] ms_in
	 */
	controller(uint8_t intersect_size, tdma::scheme div);

	/**
	 * @brief callback for car request receival
	 */
	void receive_request_callback(uint8_t current_pos,
		uint8_t requested_pos,
		std::string car_id,
		message_worker worker);

	/**
	 * @brief process car requests
	 */
	void process_requests();

	/**
	 * @brief callbcak for clear receivals
	 */
	void clear_callback(bool cleared, message_worker worker);

	/**
	 * @brief places car in moving state and blocks entrances
	 */
	void move_car(car &car);

private:
	std::shared_ptr<drf7020d20> rf_module;
	std::vector<tdma> tdmas;
	std::vector<message_worker> workers;
	std::vector<bool> blocked_intersects;
	std::deque<car> cars;
	std::mutex lock;
};
