#!/usr/bin/env bats

load 'test_helper/bats-support/load'
load 'test_helper/bats-assert/load'

prefix="./tests/runtime/templater"
input_file="${prefix}_input.txt"
output_file="${prefix}_output.txt"

input_file_multiline="${prefix}_input_multiline.txt"
output_file_multiline="${prefix}_output_multiline.txt"

input_file_f="${prefix}_input_f.txt"
output_file_f="${prefix}_output_f.txt"

json="{\"word\":\"test\"}"
json_multiline="{\"word\":\"test\", \"phone\":\"1234\"}"
json_file_f="${prefix}_json_f.json"


@test "Run templater" {
    echo "My string for \${word} templating" > "${input_file}"

    run ./build/atomic_processors templater --input1 "${input_file}" --output1 "${output_file}" --param1 "${json}"

    run cat ${output_file}
    assert_success
    assert_output "My string for test templating"

    rm "${input_file}" "${output_file}"
}

@test "Run templater with multiline input" {
    echo "My string for \${word} templating" > "${input_file_multiline}"
    echo "This is my phone number \${phone}" >> "${input_file_multiline}"
    echo "This is non existing variablee \${i_am_error}" >> "${input_file_multiline}"

    run ./build/atomic_processors templater --input1 "${input_file_multiline}" --output1 "${output_file_multiline}" --param1 "${json_multiline}"

    run cat ${output_file_multiline}
    assert_success
    assert_output - <<EOF
My string for test templating
This is my phone number 1234
This is non existing variablee \${i_am_error}
EOF

    rm "${input_file_multiline}" "${output_file_multiline}"
}

@test "Run templater using json input" {
    echo "My string for \${word} templating" > "${input_file_f}"
    echo "This is my phone number \${phone}" >> "${input_file_f}"
    echo "This is non existing variablee \${i_am_error}" >> "${input_file_f}"

    echo "${json_multiline}" > "${json_file_f}"

    run ./build/atomic_processors templater_f --input1 "${input_file_f}" --output1 "${output_file_f}" --input2 "${json_file_f}"
    run cat ${output_file_f}
    assert_success
    assert_output - <<EOF
My string for test templating
This is my phone number 1234
This is non existing variablee \${i_am_error}
EOF

    rm "${input_file_f}" "${output_file_f}" "${json_file_f}"
}
