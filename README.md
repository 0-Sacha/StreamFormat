[![Build status](https://badge.buildkite.com/c74bfd00e5543dcb5645acecbfd9d1fc3a0487bc5de13db0b9.svg)](https://buildkite.com/sacha/streamformat)
[![StreamFormat](https://github.com/0-Sacha/StreamFormat/actions/workflows/StreamFormat.yml/badge.svg)](https://github.com/0-Sacha/StreamFormat/actions/workflows/StreamFormat.yml)

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
git clone git@github.com:0-Sacha/StreamFormat.git
```

## Using the Lib
It can be used using [Bazel](https://bazel.build/).
A `cc_library` rule has been created: `@StreamFormat//:StreamFormat`.
You need to add the module `streamformat` to your dependencies.

You will need at least to give an c++ standard to use (at least c++20) since no one have been forced. You can check the [bazelrc](.bazelrc) to see how you can add one.

Not Recommended: There is also a [Premake](https://premake.github.io/docs/using-premake) configuration, thought it is deprecated (and run on a wrapper of mine: [PremakeUtilities](https://github.com/0-Sacha/PremakeUtilities)). I keep it for my Game Engine [Blackbird](https://github.com/0-Sacha/Blackbird) which is using `Premake` as Build system.

## Examples
You can check the [Examples](Examples/README.md) to see what you can do with this.
