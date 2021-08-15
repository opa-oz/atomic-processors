#!/usr/bin/env bats

load 'test_helper/bats-support/load'
load 'test_helper/bats-assert/load'

prefix="./__tests__/runtime/text-cleanup"

input_file="${prefix}_input.json"
output_file="${prefix}_output.json"
map_file="${prefix}_map.json"

setup() {
    echo '["  my text ", "right space  ", "   left space", "   ", ""]' > "${input_file}"
}

@test "Run text clean up" {
  run ./AtomicProcessors txt-cleanup --input1="${input_file}" --output1="${output_file}" --output2="${map_file}"

  run cat ${output_file}
  assert_success
  assert_output '["my text","right space","left space"]'

  rm "${input_file}" "${output_file}" "${map_file}"
}

@test "Run text clean up and check map" {
  run ./AtomicProcessors txt-cleanup --input1="${input_file}" --output1="${output_file}" --output2="${map_file}"

  run cat ${map_file}
  assert_success
  assert_output '[["  my text ","my text"],["right space  ","right space"],["   left space","left space"]]'

  rm "${input_file}" "${output_file}" "${map_file}"
}

