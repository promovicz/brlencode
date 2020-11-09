## Using Unicode Braille to represent binary data

### Why?

I noticed the possibility of doing this while reading through a Unicode book.

### Example

```
$ echo fnord | ./bin2brl; echo
⡦⡮⡯⡲⡤⠊
$ md5sum /bin/ls
de3433d0c5b7dd77562927eb4fbedb3b  /bin/ls
$ cat /bin/ls | ./bin2brl | ./brl2bin | md5sum -
de3433d0c5b7dd77562927eb4fbedb3b  -
```

