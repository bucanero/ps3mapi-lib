# PS3 Manager API (PS3MAPI)

PS3 Manager API aka PS3M_API is an API similar to TMAPI or CCAPI, compatible with CEX and DEX consoles. It includes a lot of new features (see below) which can be used in any PS3 plugins (vsh plugin, game plugin, ...), homebrew and it can be used remotely with any PC tools (and Android, iOS, ... is open source so anyone can port the PC library to any other platform) or with the webUI (any device with an internet navigator).

Developer: _NzV_

# PS3MAPI Library

This is a [PSL1GHT](https://github.com/ps3dev/PSL1GHT/) library that allows any PS3 homebrew developer to use PS3MAPI features from within their apps.

## Installation

To install the library, just clone the repository and execute:

```bash
make install
```

## PS3M_API FEATURES

### PROCESS

- Get all process pid.
- Get process name by pid.
- Get process by pid.
- Get current process.

### MEMORY

- Make all memory writable for any process.
- Set process memory.
- Get process memory.

### MODULES

- Get all process module prxid.
- Get module name by prxid.
- Get module filename by prxid.
- Load a process module.
- Unload a process module.

### VSH Plugins

- Unload plugins by name.
- Get plugins info by slot (name and filename).

### SYSCALL

- Disable any syscall.
- Partial disable syscall8.
- Check any syscall.

### EXTRA

- Remove cobra/mamba hook.
- Get and set IDPS/PSID anytime.

## License

`ps3mapi-lib` is released under the [MIT License](LICENSE).
