#!/usr/bin/env bats

load 'test_helper/bats-support/load'
load 'test_helper/bats-assert/load'

prefix="./__tests__/runtime/pick"

input_file="${prefix}_input.json"
output_file="${prefix}_output.json"

expected_file="${prefix}_expected.json"

@test "Run pick with default settings" {
  ./__scripts__/makejson.py 1000 "${input_file}" "true" "${seed}"
  ./__scripts__/pick.py "${input_file}" "id,name" "${expected_file}" "false"

  run ./AtomicProcessors pick --input1="${input_file}" --output1="${output_file}" --param1 "id,name"

  test="$(cat ${expected_file})"
  run cat ${output_file}
  assert_success
  assert_output "${test}"

  rm "${input_file}" "${output_file}" "${expected_file}"
}

@test "Run pick with full objects" {
  ./__scripts__/makejson.py 1000 "${input_file}" "true" "${seed}"
  ./__scripts__/pick.py "${input_file}" "id,name,age,city" "${expected_file}" "false"

  run ./AtomicProcessors pick --input1="${input_file}" --output1="${output_file}" --param1 "id,name,age,city"

  test="$(cat ${expected_file})"
  run cat ${output_file}
  assert_success
  assert_output "${test}"

  rm "${input_file}" "${output_file}" "${expected_file}"
}

@test "Run pick with undefined field" {
  ./__scripts__/makejson.py 1000 "${input_file}" "true" "${seed}"
  ./__scripts__/pick.py "${input_file}" "id,name,age" "${expected_file}" "false"

  run ./AtomicProcessors pick --input1="${input_file}" --output1="${output_file}" --param1 "id,name,age,i_am_undefied"

  test="$(cat ${expected_file})"
  run cat ${output_file}
  assert_success
  assert_output "${test}"

  rm "${input_file}" "${output_file}" "${expected_file}"
}

@test "Run pick with flat input" {
  ./__scripts__/makejson.py 1000 "${input_file}" "true" "${seed}"
  ./__scripts__/pick.py "${input_file}" "id" "${expected_file}" "true"

  run ./AtomicProcessors pick --input1="${input_file}" --output1="${output_file}" --param1 "id" --param2 "true"

  test="$(cat ${expected_file})"
  run cat ${output_file}
  assert_success
  assert_output "${test}"

  # rm "${input_file}" "${output_file}" "${expected_file}"
}
