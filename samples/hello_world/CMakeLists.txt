# SPDX-License-Identifier: Apache-2.0
#
# Archon LHS build (efuse GPIO enabled):
#   west build -b multizone_rc_rev2_lhs/nrf54l15/cpuapp -- \
#     -DBOARD_ROOT=c:/Users/tompr/Documents/GitHub/Archon-Controls-CAN-hybrid/archon_fw

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

target_sources(app PRIVATE src/main.c)
