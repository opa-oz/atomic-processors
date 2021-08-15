#!/usr/bin/env bats

load 'test_helper/bats-support/load'
load 'test_helper/bats-assert/load'

prefix="./__tests__/runtime/anime-alice"
long_term="./__tests__/long_term_storage"

input_file="${long_term}/aa-example.log"
output_file="${prefix}_output.json"

mixed_json_file="${prefix}_mixed.json"

@test "Run log extraction (JSON/MIXED)" {
    ./__scripts__/aa-extract-logs.py "${input_file}" json all "${mixed_json_file}"
    run ./AtomicProcessors aa-extract --input1 "${input_file}" --output1 "${output_file}" --param1 "json"

    expected=$(cat "${mixed_json_file}")

    run cat ${output_file}
    assert_success
    assert_output "${expected}"

    rm "${output_file}" "${mixed_json_file}"
}

@test "Run log extraction (JSON/IN)" {
    ./__scripts__/aa-extract-logs.py "${input_file}" json user_input "${mixed_json_file}"
    run ./AtomicProcessors aa-extract --input1 "${input_file}" --output1 "${output_file}" --param1 "json" --param2 "in"

    expected=$(cat "${mixed_json_file}")

    run cat ${output_file}
    assert_success
    assert_output "${expected}"

    rm "${output_file}" "${mixed_json_file}"
}

@test "Run log extraction (JSON/OUT)" {
    ./__scripts__/aa-extract-logs.py "${input_file}" json answer_to_user "${mixed_json_file}"
    run ./AtomicProcessors aa-extract --input1 "${input_file}" --output1 "${output_file}" --param1 "json" --param2 "out"

    expected=$(cat "${mixed_json_file}")

    run cat ${output_file}
    assert_success
    assert_output "${expected}"

    rm "${output_file}" "${mixed_json_file}"
}
