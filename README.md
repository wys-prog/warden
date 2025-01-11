# **Warden**

## **Compilation**
> You just need a C++ compiler that supports the C++20 standard.

## **Usage**
It's really simple.  
You can provide a password by entering it without any flags (the last argument will be considered the password).  
Four flags are supported:

- `-o`: Add an output.
- `-i`: Add an input.
- `-d`: Decode mode.
- `-c`: Code mode.

> By default, the mode is `-d`.

> However, the CLI version doesn't work properly yet. I'm working on it...  
> The file mode works well.

## **Providing a File as Input for Warden**

```bash
warden -f "file path"
```

## **Creating a Warden File**
*By default, `.wa` is the Warden file extension.*

```bash
$label:
  "Password" -i input1 -i "input 2" -o output1 -o "output 2" -c

$label2:
  "Password" -i "output 2" -o "output 3" -d
```

You don't really have any limitations on inputs or outputs.

Have fun!
