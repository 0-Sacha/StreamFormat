"""
"""

load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

refresh_compile_commands(
    name = "compile_commands",
    exclude_external_sources = True,
    exclude_headers = "external",
    targets = {
        "//:StreamFormat": "",
    },
)
