/**
 * @file src/profile.cpp
 * @brief Car calibration profile.
 */
#include "profile.hpp"

#include <cstdint>
#include <fstream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>

// File parsing: servo profile
static constexpr std::string CHECK_SERVO = "[servo]";
static constexpr std::string CHECK_SERVO_MAX_LEFT = "left";
static constexpr std::string CHECK_SERVO_MAX_RIGHT = "right";
static constexpr std::string CHECK_SERVO_CENTER = "center";

// File parsing: tdma profile
static constexpr std::string CHECK_TDMA = "[tdma]";
static constexpr std::string CHECK_TDMA_TX_OFFSET_MS = "tx";
static constexpr std::string CHECK_TDMA_RX_OFFSET_MS = "rx";

template<typename T>
static void load_field(
	std::ifstream &file, const std::string &check, T &destination);

void profile::load(const std::string &filename) {
	std::ifstream file(filename);
	if (file.fail()) {
		throw std::runtime_error("Cannot use provided file");
	}

	servo servo_load = {};
	tdma tdma_load = {};

	std::string line;
	while (std::getline(file, line)) {
		if (line == CHECK_SERVO) {
			load_field(file, CHECK_SERVO_MAX_LEFT, servo_load.max_left);
			load_field(file, CHECK_SERVO_MAX_RIGHT, servo_load.max_right);
			load_field(file, CHECK_SERVO_CENTER, servo_load.center);

			servo_profile = servo_load;
		}
		if (line == CHECK_TDMA) {
			load_field(file, CHECK_TDMA_TX_OFFSET_MS, tdma_load.tx_offset_ms);
			load_field(file, CHECK_TDMA_RX_OFFSET_MS, tdma_load.rx_offset_ms);

			tdma_profile = tdma_load;
		}
	}
}

void profile::save(const std::string &filename) const {
	std::ofstream file(filename);
	if (file.fail()) {
		throw std::runtime_error("Cannot use provided file");
	}

	if (servo_profile.has_value()) {
		file << CHECK_SERVO << '\n';
		file << CHECK_SERVO_MAX_LEFT << ' ' << servo_profile->max_left << '\n';
		file << CHECK_SERVO_MAX_RIGHT << ' ' << servo_profile->max_right
			 << '\n';
		file << CHECK_SERVO_CENTER << ' ' << servo_profile->center << '\n';
	}
	if (tdma_profile.has_value()) {
		file << CHECK_TDMA << '\n';
		file << CHECK_TDMA_RX_OFFSET_MS << ' ' << tdma_profile->tx_offset_ms
			 << '\n';
		file << CHECK_TDMA_TX_OFFSET_MS << ' ' << tdma_profile->rx_offset_ms
			 << '\n';
	}
}

/**
 * @brief Try to load a field from line.
 *
 * @tparam T Destination type.
 * @param[in] line - Input line.
 * @param[in] check - Verification condition.
 * @param[out] destination - Write location.
 */
template<typename T>
void load_field(std::ifstream &file, const std::string &check, T &destination) {
	// Load line
	std::string line;
	std::getline(file, line);

	// Get check value
	std::istringstream tokens(line);
	std::string file_check;
	tokens >> file_check;

	if (file_check == check) {
		tokens >> destination;
	} else {
		throw std::runtime_error("Corrupted profile");
	}
}
