/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/* Enable CAN power on LHS RC boards by asserting the eFuse enable GPIO.
 * The property is only present in the zephyr,user node on LHS boards
 * (e.g. multizone_rc_rev2_lhs), so the block compiles away on others. */
#if DT_NODE_HAS_PROP(DT_PATH(zephyr_user), mcu1_efuse_en_gpios)
static const struct gpio_dt_spec Efuse_en =
	GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), mcu1_efuse_en_gpios);
#endif

int main(void)
{
	LOG_INF("Hello World! %s", CONFIG_BOARD_TARGET);

#if DT_NODE_HAS_PROP(DT_PATH(zephyr_user), mcu1_efuse_en_gpios)
	int err;

	if (!gpio_is_ready_dt(&Efuse_en)) {
		LOG_ERR("efuse_en GPIO not ready");
		return -1;
	}

	/* Match archon GpioDev_init_output_gpio: config_flag | dt_flags */
	err = gpio_pin_configure(Efuse_en.port, Efuse_en.pin,
				 GPIO_OUTPUT_HIGH | Efuse_en.dt_flags);
	if (err) {
		LOG_ERR("efuse_en configure err %d", err);
		return err;
	}

	LOG_INF("efuse_en asserted (CAN power enabled)");
#endif

	return 0;
}
