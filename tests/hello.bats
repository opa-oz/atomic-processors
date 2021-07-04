#!/usr/bin/env bats

@test "Test for fun" {
  result="$(echo 2+2 | bc)"
  [ "$result" -eq 4 ]
}