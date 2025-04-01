# Example of stream

### Try thoses examples !

##### Build and Run examples one by one (Recommended)
Example with `//hello:hello` (see below for the list of example)
```
bazelisk run //hello:hello

[00:00:00:000] APP-Core >> hello !
[00:00:00:105] APP-Core >> After 100ms !
```

##### Compile all examples, then run binaries
To compile every example:
```
bazelisk build //...
```

Then you can run a program with (example with `//hello:hello`, see below for the list of example)
```
.\bazel-bin\hello\hello

[00:00:00:000] APP-Core >> hello !
[00:00:00:105] APP-Core >> After 100ms !
```

### List Of Examples

- `//hello:hello`: hello using the Internal Logger
