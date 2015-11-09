### what

simple master volume tuning on OpenBSD using the [audio(4)](http://www.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man4/audio.4) driver layer


### get

```sh
git clone https://github.com/tkriik/mixerctl-master.git
cd mixerctl-master
make
```


### use

increase master volume by 5%:
```sh
./mixerctl-master +5
```

decrease master volume by 10%:
```sh
./mixerctl-master -10
```
