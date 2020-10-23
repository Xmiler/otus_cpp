tests
```
$ cd build

$ echo "10.20.30.40" | ./ip_filter 
10.20.30.40

$ echo "10.20.30.a" | ./ip_filter 
Error! Unacceptable format of input: 10.20.30.a

$ echo "10.20.30.-3" | ./ip_filter 
Error! Unacceptable format of input: 10.20.30.-3

$ echo "10.20.30.256" | ./ip_filter 
Error! Unacceptable format of input: 10.20.30.256

$ echo "10.20.30.1000000" | ./ip_filter 
Error! Unacceptable format of input: 10.20.30.1000000

$ cat ../tutor_data/ip_filter.tsv | ./ip_filter | md5sum
24e7a7b2270daee89c64d3ca5fb3da1a  -
```
