---
okf_version: "0.2"
---

# ext-sdl3

1:1 PHP bindings of SDL 3 at the 3.2 API. Version 0.10.0. Linux and macOS.

# API

* [Bindings](api/bindings.md) — Functions, handles, structs and constants by group.

# Architecture

* [Handles](architecture/handles.md) — Identity table, the released flag, and what `keep` holds.
* [Structs](architecture/structs.md) — The four translations, `_from` helpers, and scratch arrays.

# Runbooks

* [Build, install, test](runbooks/build.md) — Mac and Pi, including which SDL the Pi must link.
* [Adding a binding](runbooks/adding-a-binding.md) — Stub, gen_stub, one C file per stub, `config.m4`, the surface test.
