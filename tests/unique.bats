#!/usr/bin/env bats

load 'test_helper/bats-support/load'
load 'test_helper/bats-assert/load'

prefix="./tests/runtime/unique"

input_json_flat="${prefix}_input_flat.json"
test_json_flat="${prefix}_text_flat.json"
output_json_flat="${prefix}_output_flat.json"

input_json_flat_string="${prefix}_input_flat_string.json"
test_json_flat_string="${prefix}_text_flat_string.json"
output_json_flat_string="${prefix}_output_flat_string.json"

input_json_flat_int="${prefix}_input_flat_int.json"
test_json_flat_int="${prefix}_text_flat_int.json"
output_json_flat_int="${prefix}_output_flat_int.json"

input_json_objects="${prefix}_input_objects.json"
test_json_objects="${prefix}_text_objects.json"
output_json_objects="${prefix}_output_objects.json"

seed="unique"

@test "Run unique with mixed flat json" {
  ./scripts/makeflatjson.py 1000 "${input_json_flat}" mixed "${seed}"
  cp "${input_json_flat}" "${test_json_flat}"
  ./scripts/uniquejson.py "${test_json_flat}" array key
  ./scripts/unspacejson.py "${test_json_flat}"

  run ./build/atomic_processors unique --input1="${input_json_flat}" --output1="${output_json_flat}" --param1=json --param2=simple

  test="$(cat ${test_json_flat})"
  run cat ${output_json_flat}
  assert_success
  assert_output "${test}"

  rm "${input_json_flat}" "${test_json_flat}" "${output_json_flat}"
}

@test "Run unique with string flat json" {
  ./scripts/makeflatjson.py 1000 "${input_json_flat_string}" string "${seed}"
  cp "${input_json_flat_string}" "${test_json_flat_string}"
  ./scripts/uniquejson.py "${test_json_flat_string}" array key
  ./scripts/unspacejson.py "${test_json_flat_string}"

  run ./build/atomic_processors unique --input1="${input_json_flat_string}" --output1="${output_json_flat_string}" --param1=json --param2=simple

  test="$(cat ${test_json_flat_string})"
  run cat ${output_json_flat_string}
  assert_success
  assert_output "${test}"

  rm "${input_json_flat_string}" "${test_json_flat_string}" "${output_json_flat_string}"
}

@test "Run unique with int flat json" {
  ./scripts/makeflatjson.py 1000 "${input_json_flat_int}" int "${seed}"
  cp "${input_json_flat_int}" "${test_json_flat_int}"
  ./scripts/uniquejson.py "${test_json_flat_int}" array key
  ./scripts/unspacejson.py "${test_json_flat_int}"

  run ./build/atomic_processors unique --input1="${input_json_flat_int}" --output1="${output_json_flat_int}" --param1=json --param2=simple

  test="$(cat ${test_json_flat_int})"
  run cat ${output_json_flat_int}
  assert_success
  assert_output "${test}"

  rm "${input_json_flat_int}" "${test_json_flat_int}" "${output_json_flat_int}"
}

@test "Run unique with mixed objects json" {
  keys="age,id,city,name"

  ./scripts/makejson.py 250 "${input_json_objects}" true "${seed}"
  cp "${input_json_objects}" "${test_json_objects}"
  ./scripts/uniquejson.py "${test_json_objects}" objects "${keys}"
  ./scripts/sortjson.py "${test_json_objects}"
  ./scripts/unspacejson.py "${test_json_objects}"

  run ./build/atomic_processors unique --input1="${input_json_objects}" --output1="${output_json_objects}" --param1=json --param2=complex --param3="${keys}"

  test="$(cat ${test_json_objects})"
  run cat ${output_json_objects}
  assert_success
  assert_output "${test}"

  rm "${input_json_objects}" "${test_json_objects}" "${output_json_objects}"
}
