# Example of ProjectCore

### Try thoses examples !

##### Build and Run examples one by one (Recommended)
Example with `//HelloWorld:HelloWorld` (see below for the list of example)
```
bazelisk run //HelloWorld:HelloWorld

[00:00:00:000] APP-Core >> HelloWorld !
[00:00:00:105] APP-Core >> After 100ms !
```

##### Compile all examples, then run binaries
To compile every example:
```
bazelisk build //...
```

Then you can run a program with (example with `//HelloWorld:HelloWorld`, see below for the list of example)
```
.\bazel-bin\HelloWorld\HelloWorld

[00:00:00:000] APP-Core >> HelloWorld !
[00:00:00:105] APP-Core >> After 100ms !
```

### List Of Example

- `//HelloWorld:HelloWorld`: HelloWorld using the Internal Logger
