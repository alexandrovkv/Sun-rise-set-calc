# Sun-rise-set-calc
Sun rise/set calculator (based on [Paul Schlyter](http://stjarnhimlen.se/english.html) sunriset code)
## Compile
```
  gcc -Wall -W sunriset.c main.c -o srstable -lm
```
## Usage
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


```
./srstable -l 30 -L 60 -O 10800 -Y 2018 -M 3 -CNA
2018-03-01    05:39:23    06:28:23    07:16:27    07:58:13    18:26:28    19:08:13    19:56:17    20:45:17    10:28:14
2018-03-02    05:36:23    06:25:32    07:13:37    07:55:17    18:29:00    19:10:40    19:58:44    20:47:53    10:33:42
2018-03-03    05:33:21    06:22:40    07:10:45    07:52:21    18:31:31    19:13:07    20:01:12    20:50:30    10:39:10
2018-03-04    05:30:17    06:19:45    07:07:53    07:49:24    18:34:02    19:15:33    20:03:41    20:53:09    10:44:38
2018-03-05    05:27:11    06:16:49    07:04:59    07:46:27    18:36:33    19:18:00    20:06:10    20:55:49    10:50:06
2018-03-06    05:24:02    06:13:52    07:02:05    07:43:29    18:39:03    19:20:27    20:08:40    20:58:30    10:55:34
2018-03-07    05:20:51    06:10:53    06:59:09    07:40:31    18:41:33    19:22:54    20:11:10    21:01:13    11:01:02
2018-03-08    05:17:37    06:07:53    06:56:13    07:37:32    18:44:03    19:25:22    20:13:42    21:03:58    11:06:30
2018-03-09    05:14:21    06:04:51    06:53:16    07:34:33    18:46:32    19:27:49    20:16:14    21:06:44    11:11:59
2018-03-10    05:11:03    06:01:48    06:50:18    07:31:33    18:49:01    19:30:17    20:18:46    21:09:31    11:17:27
2018-03-11    05:07:42    05:58:43    06:47:19    07:28:33    18:51:30    19:32:44    20:21:20    21:12:21    11:22:56
2018-03-12    05:04:19    05:55:37    06:44:19    07:25:33    18:53:58    19:35:12    20:23:54    21:15:12    11:28:25
2018-03-13    05:00:54    05:52:30    06:41:19    07:22:33    18:56:26    19:37:40    20:26:29    21:18:05    11:33:53
2018-03-14    04:57:25    05:49:21    06:38:18    07:19:32    18:58:54    19:40:09    20:29:05    21:21:01    11:39:22
2018-03-15    04:53:55    05:46:11    06:35:16    07:16:31    19:01:22    19:42:37    20:31:42    21:23:58    11:44:51
2018-03-16    04:50:21    05:42:59    06:32:13    07:13:29    19:03:49    19:45:06    20:34:20    21:26:57    11:50:20
2018-03-17    04:46:45    05:39:46    06:29:10    07:10:28    19:06:17    19:47:35    20:36:59    21:29:59    11:55:48
2018-03-18    04:43:07    05:36:31    06:26:06    07:07:26    19:08:44    19:50:04    20:39:39    21:33:03    12:01:17
2018-03-19    04:39:25    05:33:15    06:23:01    07:04:24    19:11:10    19:52:34    20:42:20    21:36:10    12:06:46
2018-03-20    04:35:41    05:29:58    06:19:56    07:01:22    19:13:37    19:55:04    20:45:02    21:39:19    12:12:14
2018-03-21    04:31:53    05:26:39    06:16:50    06:58:20    19:16:04    19:57:34    20:47:45    21:42:31    12:17:43
2018-03-22    04:28:02    05:23:19    06:13:43    06:55:18    19:18:30    20:00:05    20:50:29    21:45:46    12:23:11
2018-03-23    04:24:09    05:19:57    06:10:36    06:52:16    19:20:56    20:02:36    20:53:15    21:49:03    12:28:40
2018-03-24    04:20:12    05:16:34    06:07:29    06:49:14    19:23:23    20:05:07    20:56:02    21:52:24    12:34:09
2018-03-25    04:16:11    05:13:10    06:04:20    06:46:11    19:25:49    20:07:39    20:58:50    21:55:49    12:39:37
2018-03-26    04:12:07    05:09:44    06:01:12    06:43:09    19:28:15    20:10:12    21:01:40    21:59:17    12:45:05
2018-03-27    04:07:59    05:06:17    05:58:03    06:40:07    19:30:41    20:12:45    21:04:31    22:02:49    12:50:34
2018-03-28    04:03:47    05:02:48    05:54:53    06:37:04    19:33:07    20:15:18    21:07:23    22:06:24    12:56:02
2018-03-29    03:59:31    04:59:18    05:51:43    06:34:02    19:35:33    20:17:52    21:10:17    22:10:04    13:01:30
2018-03-30    03:55:10    04:55:46    05:48:32    06:31:00    19:37:59    20:20:27    21:13:13    22:13:49    13:06:58
2018-03-31    03:50:45    04:52:12    05:45:21    06:27:58    19:40:25    20:23:02    21:16:11    22:17:38    13:12:26
```
In CSV foemat
```
./srstable -l 60 -L 30 -O 10800 -Y 2018 -M 3 -nCNA -c
data,astr_end,naut_end,civ_end,rise,noon,set,civ_start,naut_start,astr_start,day_length
2018-03-01,05:39:23,06:28:23,07:16:27,07:58:13,13:12:20,18:26:28,19:08:13,19:56:17,20:45:17,10:28:14
2018-03-02,05:36:23,06:25:32,07:13:37,07:55:17,13:12:08,18:29:00,19:10:40,19:58:44,20:47:53,10:33:42
2018-03-03,05:33:21,06:22:40,07:10:45,07:52:21,13:11:56,18:31:31,19:13:07,20:01:12,20:50:30,10:39:10
2018-03-04,05:30:17,06:19:45,07:07:53,07:49:24,13:11:43,18:34:02,19:15:33,20:03:41,20:53:09,10:44:38
2018-03-05,05:27:11,06:16:49,07:04:59,07:46:27,13:11:30,18:36:33,19:18:00,20:06:10,20:55:49,10:50:06
2018-03-06,05:24:02,06:13:52,07:02:05,07:43:29,13:11:16,18:39:03,19:20:27,20:08:40,20:58:30,10:55:34
2018-03-07,05:20:51,06:10:53,06:59:09,07:40:31,13:11:02,18:41:33,19:22:54,20:11:10,21:01:13,11:01:02
2018-03-08,05:17:37,06:07:53,06:56:13,07:37:32,13:10:47,18:44:03,19:25:22,20:13:42,21:03:58,11:06:30
2018-03-09,05:14:21,06:04:51,06:53:16,07:34:33,13:10:32,18:46:32,19:27:49,20:16:14,21:06:44,11:11:59
2018-03-10,05:11:03,06:01:48,06:50:18,07:31:33,13:10:17,18:49:01,19:30:17,20:18:46,21:09:31,11:17:27
2018-03-11,05:07:42,05:58:43,06:47:19,07:28:33,13:10:02,18:51:30,19:32:44,20:21:20,21:12:21,11:22:56
2018-03-12,05:04:19,05:55:37,06:44:19,07:25:33,13:09:46,18:53:58,19:35:12,20:23:54,21:15:12,11:28:25
2018-03-13,05:00:54,05:52:30,06:41:19,07:22:33,13:09:30,18:56:26,19:37:40,20:26:29,21:18:05,11:33:53
2018-03-14,04:57:25,05:49:21,06:38:18,07:19:32,13:09:13,18:58:54,19:40:09,20:29:05,21:21:01,11:39:22
2018-03-15,04:53:55,05:46:11,06:35:16,07:16:31,13:08:56,19:01:22,19:42:37,20:31:42,21:23:58,11:44:51
2018-03-16,04:50:21,05:42:59,06:32:13,07:13:29,13:08:39,19:03:49,19:45:06,20:34:20,21:26:57,11:50:20
2018-03-17,04:46:45,05:39:46,06:29:10,07:10:28,13:08:22,19:06:17,19:47:35,20:36:59,21:29:59,11:55:48
2018-03-18,04:43:07,05:36:31,06:26:06,07:07:26,13:08:05,19:08:44,19:50:04,20:39:39,21:33:03,12:01:17
2018-03-19,04:39:25,05:33:15,06:23:01,07:04:24,13:07:47,19:11:10,19:52:34,20:42:20,21:36:10,12:06:46
2018-03-20,04:35:41,05:29:58,06:19:56,07:01:22,13:07:30,19:13:37,19:55:04,20:45:02,21:39:19,12:12:14
2018-03-21,04:31:53,05:26:39,06:16:50,06:58:20,13:07:12,19:16:04,19:57:34,20:47:45,21:42:31,12:17:43
2018-03-22,04:28:02,05:23:19,06:13:43,06:55:18,13:06:54,19:18:30,20:00:05,20:50:29,21:45:46,12:23:11
2018-03-23,04:24:09,05:19:57,06:10:36,06:52:16,13:06:36,19:20:56,20:02:36,20:53:15,21:49:03,12:28:40
2018-03-24,04:20:12,05:16:34,06:07:29,06:49:14,13:06:18,19:23:23,20:05:07,20:56:02,21:52:24,12:34:09
2018-03-25,04:16:11,05:13:10,06:04:20,06:46:11,13:06:00,19:25:49,20:07:39,20:58:50,21:55:49,12:39:37
2018-03-26,04:12:07,05:09:44,06:01:12,06:43:09,13:05:42,19:28:15,20:10:12,21:01:40,21:59:17,12:45:05
2018-03-27,04:07:59,05:06:17,05:58:03,06:40:07,13:05:24,19:30:41,20:12:45,21:04:31,22:02:49,12:50:34
2018-03-28,04:03:47,05:02:48,05:54:53,06:37:04,13:05:06,19:33:07,20:15:18,21:07:23,22:06:24,12:56:02
2018-03-29,03:59:31,04:59:18,05:51:43,06:34:02,13:04:47,19:35:33,20:17:52,21:10:17,22:10:04,13:01:30
2018-03-30,03:55:10,04:55:46,05:48:32,06:31:00,13:04:29,19:37:59,20:20:27,21:13:13,22:13:49,13:06:58
2018-03-31,03:50:45,04:52:12,05:45:21,06:27:58,13:04:12,19:40:25,20:23:02,21:16:11,22:17:38,13:12:26
```
