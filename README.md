# py2dec

Python bytecode decompiler that converts compiled Python files (.pyc) back to readable Python source code.

## Build

```bash
make
```

## Usage

```bash
./bin/py2dec [OPTIONS] <file>
```

**Options:**
- `--output-asm <file>` - Output disassembled bytecode to file
- `-o <file>` - Output decompiled code to file (defaults to stdout)

**Example:**
```bash
./bin/py2dec sample.pyc
./bin/py2dec -o output.py sample.pyc
```