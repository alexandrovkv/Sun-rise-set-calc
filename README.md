# Sun-rise-set-calc
Sun rise/set calculator (based on [Paul Schlyter](http://stjarnhimlen.se/english.html) sunriset code)
## Compile
```
  gcc -Wall -W sunriset.c main.c -o srstable -lm
```
## Usage
```
  ./srstable -l 30 -L 60 -O 10800
```
### Command line options
```
  -l <num>,  --latitude=<num>    - latitude (in decimal degrees, + is north)
  -L <num>,  --longitude=<num>   - longitude (in decimal degrees, + is east)
  -O <num>,  --offset=<num>      - offset from UTC (in seconds)
  -Y <num>,  --year=<num>        - set year (default - current)
  -M <num>,  --month=<num>       - set month (default - all)
  -D <num>,  --day=<num>         - set day (default - all)
  -n,        --noon              - print noon time
  -C,        --civil             - print civil twilight times
  -N,        --nautical          - print nautical twilight times
  -A,        --astronomical      - print astronomical twilight times
  -e,        --eot               - print Equation of Time
  -c,        --csv               - out in CSV format
```
