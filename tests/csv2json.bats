#!/usr/bin/env bats

prefix="./tests/runtime/csv2json"
input_file="${prefix}_input.csv"
output_file="${prefix}_output.json"

input_file_custom_divider="${prefix}_input_custom_divider.csv"
output_file_custom_divider="${prefix}_output_custom_divider.json"

input_file_mapper="${prefix}_input_mapper.csv"
output_file_mapper="${prefix}_output_mapper.json"

input_file_random="${prefix}_input_random.csv"
output_file_random="${prefix}_output_random.json"
test_file_random="${prefix}_test_random.json"

header_mapping="{\"id\":\"person_id\"}"
header_mapping_file="${prefix}_header_mapping.json"

seed="csv2json"

setup() {
    load 'test_helper/bats-support/load'
    load 'test_helper/bats-assert/load'

    echo "id,name,age" > "${input_file}"
    echo "1,Dany,16" >> "${input_file}"
    echo "2,Marri,26" >> "${input_file}"
    echo "3,\"Arnold\",31" >> "${input_file}"

    cp "${input_file}" "${input_file_mapper}"

    cat "${input_file}" | awk '{gsub(/,/,";")}1' > "${input_file_custom_divider}"

    ./scripts/makecsv.py 5 "${input_file_random}" true "${seed}"
    ./scripts/makejson.py 5 "${test_file_random}" true "${seed}"

    echo "${header_mapping}" > "${header_mapping_file}"
}

@test "Run csv2json" {
    ./build/atomic_processors csv2json --input1 "${input_file}" --output1 "${output_file}" --param1 "{}" --param2 "," --param3 "\""

    run cat ${output_file}
    assert_success
    assert_output '[{"age":16,"id":1,"name":"Dany"},{"age":26,"id":2,"name":"Marri"},{"age":31,"id":3,"name":"Arnold"}]'
}

@test "Run csv2json with custom divider" {
    ./build/atomic_processors csv2json --input1 "${input_file_custom_divider}" --output1 "${output_file_custom_divider}" --param1 "{}" --param2 ";" --param3 "\""

    run cat ${output_file_custom_divider}
    assert_success
    assert_output '[{"age":16,"id":1,"name":"Dany"},{"age":26,"id":2,"name":"Marri"},{"age":31,"id":3,"name":"Arnold"}]'
}

@test "Run csv2json with custom mapper" {
    ./build/atomic_processors csv2json --input1 "${input_file_mapper}" --output1 "${output_file_mapper}" --param1 "${header_mapping}" --param2 "," --param3 "\""


    run cat ${output_file_mapper}
    assert_success
    assert_output '[{"age":16,"name":"Dany","person_id":1},{"age":26,"name":"Marri","person_id":2},{"age":31,"name":"Arnold","person_id":3}]'
}

@test "Run csv2json with custom mapper from file" {
    ./build/atomic_processors csv2json_f --input1 "${input_file_mapper}" --output1 "${output_file_mapper}" --input2 "${header_mapping_file}" --param2 "," --param3 "\""

    run cat ${output_file_mapper}
    assert_success
    assert_output '[{"age":16,"name":"Dany","person_id":1},{"age":26,"name":"Marri","person_id":2},{"age":31,"name":"Arnold","person_id":3}]'
}

@test "Run csv2json on random data" {
    ./build/atomic_processors csv2json --input1 "${input_file_random}" --output1 "${output_file_random}" --param1 "{}" --param2 "," --param3 "\""

    ./scripts/sortjson.py "${test_file_random}"
    ./scripts/unspacejson.py "${test_file_random}"

    test="$(cat ${test_file_random})"
    run cat ${output_file_random}
    assert_success
    assert_output "${test}"
}

function teardown() {
    rm "${input_file}"
    rm "${output_file}"

    rm "${input_file_custom_divider}"
    rm "${output_file_custom_divider}"

    rm "${input_file_mapper}"
    rm "${output_file_mapper}"

    rm "${input_file_random}"
    rm "${output_file_random}"
    rm "${test_file_random}"

    rm "${header_mapping_file}"
}