# Example of ProjectCore

### Try thoses examples !

##### Build and Run examples one by one (Recommended)
Example with `//HelloWorld:HelloWorld` (see below for the list of example)
- On Windows, using msvc:
    ```
    bazelisk run --config=msvc //HelloWorld:HelloWorld
    
    [00:00:00:000] APP-Core >> HelloWorld !
    [00:00:00:105] APP-Core >> After 100ms !
    ```
- On Linux: (This `--config=linux` is not mandatory)
    ```
    bazelisk run --config=linux //HelloWorld:HelloWorld
    
    [00:00:00:000] APP-Core >> HelloWorld !
    [00:00:00:105] APP-Core >> After 100ms !
    ```

##### Compile all examples, then run binaries
To compile every example:
- On Windows, using msvc:
    ```
    bazelisk build --config=msvc //...
    ```
- On Linux: (This `--config=linux` is not mandatory)
    ```
    bazelisk build --config=linux //...
    ```

Then you can run a program with (example with `//HelloWorld:HelloWorld`, see below for the list of example)
```
.\bazel-bin\HelloWorld\HelloWorld

[00:00:00:000] APP-Core >> HelloWorld !
[00:00:00:105] APP-Core >> After 100ms !
```

### List Of Examples

- `//HelloWorld:HelloWorld`: HelloWorld using the Internal Logger
