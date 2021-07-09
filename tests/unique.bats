#!/usr/bin/env bats

prefix="./tests/runtime/unique"

input_json_flat="${prefix}_input_flat.json"
test_json_flat="${prefix}_text_flat.json"
output_json_flat="${prefix}_output_flat.json"

seed="unique"


setup() {
  load 'test_helper/bats-support/load'
  load 'test_helper/bats-assert/load'

  ./scripts/makeflatjson.py 10 "${input_json_flat}" mixed "${seed}"
  cp "${input_json_flat}" "${test_json_flat}"
  ./scripts/uniquejson.py "${test_json_flat}" array
  ./scripts/unspacejson.py "${test_json_flat}"
}

@test "Run unique with mixed flat json" {
  ./build/atomic_processors unique --input1="${input_json_flat}" --output1="${output_json_flat}" --param1=json --param2=simple

  test="$(cat ${test_json_flat})"
  run cat ${output_json_flat}
  assert_success
  assert_output "${test}"
}

function teardown() {
  rm "${input_json_flat}"
  rm "${test_json_flat}"
  rm "${output_json_flat}"
}
