# QTranslator

## Build

To build the project, execute the following command :  
```make```

## Manual

```
USAGE:
        ./QTranslator file.io [OPTIONS]

DESCRIPTION:
        file.io         file to be translated into QASM

OPTIONS:
        -h --help       Display this help menu
        -o --output     Name of the generated QASM file
RETURN VALUE:
        0               if transpilation succeed
        1               if transpilation failed
```

## Usage

The custom language must follow this pattern :

```
int i 3
int j 10

add i 5
sub i 5
add i j
```

## Build Tips

If you want to remove all objects files :  
`make clean`  