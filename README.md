[![Build status](https://badge.buildkite.com/c74bfd00e5543dcb5645acecbfd9d1fc3a0487bc5de13db0b9.svg)](https://buildkite.com/sacha/streamformat)
[![stream](https://github.com/0-Sacha/stream/actions/workflows/stream.yml/badge.svg)](https://github.com/0-Sacha/stream/actions/workflows/stream.yml)

# stream

stream is a C++20 String Formatter, like [&lt;fmt&gt;](https://github.com/fmtlib/fmt)
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

## Using the Lib
It can be used using [Bazel](https://bazel.build/).
A `cc_library` rule has been created: `@stream//:stream`.
You need to add the module `streamformat` to your dependencies.

## Examples
You can check the [Examples](Examples/README.md) to see what you can do with this.
