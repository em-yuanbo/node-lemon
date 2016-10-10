{
  "targets": [{
    "target_name": "lemon",
      "sources": [ 
        "src/lemon.cc",
        "src/lemon/parse.c",
        "src/lemon/delete.c",
        "src/lemon/insert.c",
        "src/lemon/select.c",
        "src/lemon/update.c",
        "src/lemon/util.c",
        "src/lemon/where.c",
        "src/lemon/tokenize.c",
        "src/lemon/printf.c",
        "src/lemon/expr.c",
        "src/lemon/build.c",
        "src/lemon/trigger.c",
        "src/lemon/alter.c",
        "src/lemon/os_unix.c",
        "src/lemon/callback.c"
        ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
  }]
}
