#include "test_commands.h"

#define DD46_COMMAND_ID 0x46
#define DD46_PAYLOAD_SIZE 6

void test_command_controller_device_descriptor_46_first_byte() {
  uint8_t command_input[DD46_PAYLOAD_SIZE] = { 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, };
  uint8_t expected_output[DD46_PAYLOAD_SIZE] = { 0x00, 0x00, 0x01, 0x02, 0x00, 0x0A, };
  uint8_t *actual_output = helper_run_command(&state, DD46_COMMAND_ID, command_input, DD46_PAYLOAD_SIZE);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_output, actual_output, DD46_PAYLOAD_SIZE);
}

void test_command_controller_device_descriptor_46_second_byte() {
  uint8_t command_input[DD46_PAYLOAD_SIZE] = { 0x01, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, };
  uint8_t expected_output[DD46_PAYLOAD_SIZE] = { 0x00, 0x00, 0x01, 0x01, 0x01, 0x14, };
  uint8_t *actual_output = helper_run_command(&state, DD46_COMMAND_ID, command_input, DD46_PAYLOAD_SIZE);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_output, actual_output, DD46_PAYLOAD_SIZE);
}