[![Buildkite](https://badge.buildkite.com/c74bfd00e5543dcb5645acecbfd9d1fc3a0487bc5de13db0b9.svg)](https://buildkite.com/sacha/streamformat)

[![](https://github.com/0-Sacha/streamformat/actions/workflows/linter.yml/badge.svg)](https://github.com/0-Sacha/streamformat/actions/workflows/linter.yml)
[![](https://github.com/0-Sacha/streamformat/actions/workflows/tests_linux.yml/badge.svg)](https://github.com/0-Sacha/streamformat/actions/workflows/tests_linux.yml)
[![](https://github.com/0-Sacha/streamformat/actions/workflows/tests_windows.yml/badge.svg)](https://github.com/0-Sacha/streamformat/actions/workflows/tests_windows.yml)

# StreamFormat

StreamFormat is a C++20 String Formatter, like [&lt;fmt&gt;](https://github.com/fmtlib/fmt)
Using this formatter, it define others functionalities:
- Logger like [spdlog](https://github.com/gabime/spdlog)
- Json Serializer
- Profiler
- Test Suite

## Warnings
This project is mostly an educational project of mine that I have started to learn about C++. Some features are not finished to be implemented/tested. I highly not recomend using this for a serious project.
**Do not hesitate to open an issue if you have any suggestions or review to make.**

## Docs / Comments
Like said above, I have begun this project when learning C++, and at the time my projects where absolutely not documented. I am trying to fix this error whenever I got the time. A doc and comments will come one day...

For now, at least, you have the [Examples](Examples/README.md) (and maybe the Tests/) folders to understand what you can do with it. More examples are coming, but again, I am trying to do this whenever I have the time to do it.

## Download
```
git clone git@github.com:0-Sacha/stream.git
```

## Integration
### [Bazel](https://bazel.build/)
`MODULE.bazel`
```python
git_override(module_name="streamformat", remote="https://github.com/0-Sacha/streamformat.git")
bazel_dep(name = "streamformat")
```

`BUILD.bazel`: In your `cc_binary` / `cc_library`
```python
deps = [ "@streamformat//:stream" ],
```

## Examples
You can check the [examples](examples/README.md) to see what you can do with this.
