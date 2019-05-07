package(default_visibility = ["//visibility:public"])


cc_binary(
    name = "libffi.so",
    srcs = ["lib.cc"],
    linkopts = ["-shared"],
    deps = [
        "//zetasql/base",
        "//zetasql/base:status",
        "//zetasql/parser",
    ],
)
