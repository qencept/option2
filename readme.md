### Option2 (count flow combinations)
Build
```
mkdir build && cmake -Bbuild/ && make -C build
```

Run tests
```
./test.sh "parse_correct parse_wrong smoke overflow sample"
```

Test/Benchmark huge file
```
tar -xf test/huge.tar.bz2 -C test
./test.sh huge
./benchmark.sh huge
```

Process custom CSV file
```
./build/option2 <csv_file>
```

### Benchmarks

Generated huge file 10M lines, 10% empty, random flows [1-200000], random sources [0-15,'E'].
Time elapsed:
- Apple M4 Pro (arm64), macOS 15.4.1: 620 ms
- Intel N100 (x86_64), Ubuntu 24.04.1: 1380 ms