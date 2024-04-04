#include <iostream>

#include <gpiod.hpp>

#include <driver/device.hpp>
#include <driver/drf7020d20.hpp>
#include <driver/pinmap.hpp>
#include <shared/messages.hpp>
#include <driver/servo.hpp>
#include <driver/motors.hpp>
#include <driver/lightsens.hpp>

// NOLINTBEGIN: temporary code
#define CALLSIGN "?"
#define TAG "/2"

// NOLINTEND

int main() {
	/* auto rf_test = std::make_shared<drf7020d20>(gpio_pins, RASPI_40,
	 * RASPI_37, RASPI_38, 0); */
	auto rf_test = std::make_shared<drf7020d20>(
		gpio_pins, RASPI_12, RASPI_16, RASPI_18, 0);

	rf_test->enable();
	rf_test->configure(
		433900, drf7020d20::DR9600, 9, drf7020d20::DR9600, drf7020d20::NONE);

	motor m(gpio_pins, RASPI_15, RASPI_13, RASPI_11);
	servo s(gpio_pins, RASPI_19);

	return 0;
}
