#include "test_commands.h"

#define IPS_COMMAND_ID 0x40
#define IPS_PAYLOAD_SIZE 6

void test_command_controller_initialize_pressure_sensor_constant_response() {
  uint8_t command_input[IPS_PAYLOAD_SIZE] = { 0x00, 0x02, 0x00, 0x00, 0x00, 0x00 };
  uint8_t expected_output[IPS_PAYLOAD_SIZE] = { 0x00, 0x00, 0x02, 0x00, 0x00, 0x5A };
  uint8_t *actual_output = helper_run_command(&state, IPS_COMMAND_ID, command_input, IPS_PAYLOAD_SIZE);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_output, actual_output, IPS_PAYLOAD_SIZE);
}