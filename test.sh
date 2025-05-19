#!/bin/bash
for name in $1; do
  echo "Test "${name}
  ./build/option2 test/${name}.csv | sort -k2 -g | diff test/${name}.sorted -
done
