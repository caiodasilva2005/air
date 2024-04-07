/**
 * @file include/tdma.hpp
 * @brief TDMA wrapper for RF communication.
 */
#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <driver/drf7020d20.hpp>

class tdma {
public:
	enum scheme {
		AIR_A,
		AIR_B,
		AIR_C
	};

	struct scheme_info {
		uint32_t frame_duration_ms;
		uint32_t frames_per_second;
	};

	tdma(const std::shared_ptr<drf7020d20> &rf_dev_in,
		uint32_t timeslot,
		scheme div);

	/**
	 * @brief Transmit message synchronously.
	 *
	 * @param[in] msg - Message, must be at most 15 bytes.
	 * @return Boolean result.
	 */
	bool tx_sync(const std::string &msg) const;

	/**
	 * @brief Receive message synchronously.
	 *
	 * @param[in] max_frames - Maximum frames before timeout
	 * @return Received message, or empty string on timeout.
	 */
	std::string rx_sync(uint32_t max_frames) const;

	/**
	 * @brief Adjust timing for receiving.
	 *
	 * @param[in] new_offset - ms offset for message start.
	 */
	inline void rx_set_offset(int32_t new_offset_ms) {
		rx_offset_ms = new_offset_ms;
	}

	/**
	 * @brief Adjust timing for transmitting.
	 *
	 * @param[in] new_offset - ms offset for message start.
	 */
	inline void tx_set_offset(int32_t new_offset_ms) {
		tx_offset_ms = new_offset_ms;
	}

	/**
	 * @brief get the timeslot of device
	 */
	inline uint32_t get_timeslot() {
		return slot;
	}

private:
	void sleep_until_next_slot(int32_t offset_ms) const;

	std::shared_ptr<drf7020d20> rf_dev;
	uint32_t slot;
	scheme_info sch_info;

	int32_t rx_offset_ms = 0;
	int32_t tx_offset_ms = 0;
};
