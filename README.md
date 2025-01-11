# warden

## Compilation
> You just need a C++ compiler, supporting the C++20 standard.

## Usage
It's really simple.
You can give a password by puting it without flags (last flag will be counted as password)
Four flags are supported. 

- `-o`: add an output
- `-i`: add an input
- `-d`: Decode mode
- `-c`: Code mode

> By default, the mode i `-d`

> However, the CLI version didn't works proprely. I'm working on..
> The file mode works nicely.

## Giving a file as an input for Warden

```bash
warden -f "file path"
```

## Making a warden file
*By default, the `.wa` extention is the Warden's extention*
```bash
$label:
  "Password" -i input1 -i "input 2" -o output1 -o "output 2" -c

$label2:
  "Password" -i "output 2" -o "output  3" -d
```

You don't really have limitation in inputs/outputs

Have fun !!