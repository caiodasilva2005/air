/**
 * @file src/messageworker.hpp
 * @brief handler for control messages
 */
#pragma once

#include <cstdint>
#include <stdlib.h>
#include <string>

#include <shared/tdma.hpp>

class message_worker {
public:
	/**
	 * @brief constructor for control message worker
	 * @param[in] tdma_handler_in
	 */
	message_worker(const std::shared_ptr<tdma> &tdma_handler_in);

	/**
	 * @brief awaits check in from car and sends out a check in
	 * @return true if check in is sent successfully
	 */
	bool await_checkin();
	/**
	 * @brief receives request from car
	 * @return pair of current and desired position of car
	 */

	std::pair<uint8_t, uint8_t> await_request();

	/**
	 * @brief receives clear message from car and ends conversation
	 * @return true if clear is sent successfully
	 */
	bool await_clear();

	/**
	 * @brief creates check in message
	 */
	std::string format_checkin();

	/**
	 * @brief creates unsupported message
	 */
	std::string format_unsupported();

	/**
	 * @param command response to car's request
	 * @brief creates command message
	 */
	std::string format_command(const std::string &command);

	/**
	 * @brief sends command to car
	 * @param[in] command 
	*/
	inline void send_command(const std::string &command) {
		tdma_handler->tx_sync(format_command(command));
	}

	/**
	 * @brief get timeslot of car
	 * @return timeslot
	*/
	inline uint32_t get_timeslot() {
		return tdma_handler->get_timeslot();
	}

private:
	std::shared_ptr<tdma> tdma_handler;
	std::shared_ptr<std::string> control_id;
};
