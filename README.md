# QTranslator

## :speech_balloon: Desciption
Transforms an .asm file into QASM. The goal is to create a quantum calculator.

## :computer: Install

### :rocket: Clone repository

```shell
git@github.com:PoCInnovation/QTranslator.git
```

### :warning: Requirement

- [CMake >= 3.17](https://cmake.org/download/)
- [C++20](https://en.cppreference.com/w/cpp/20)

## :writing_hand: How to write .asm
### :clipboard: Example
Create a file **operations.asm**:
```asm
; operations.asm

xor rax, rax

cmp BYTE[rax], 0
je endl
inc rax

endl:
ret
```

## :checkered_flag: Quick-Start

```shell
make
./QTranslator operations.asm
```

## :information_source: More informations
### :ledger: Manual

```
USAGE:
        ./QTranslator file.asm [OPTIONS]

DESCRIPTION:
        file.io         ASM source code to be translated into QASM

OPTIONS:
        -h --help       Display this help menu
        -o --output     Name of the generated QASM file
RETURN VALUE:
        0               if transpilation succeed
        1               if transpilation failed
```


### :white_check_mark: Build and run unit tests

To build the tests, execute the following command :  
```make tests```

After that, you will be able to run them using the following command :  
```./QTranslatorTests```

### :bulb: Build Tips

If you want to remove all objects files :  
`make clean`  

## :bust_in_silhouette: Authors

| [<img src="https://github.com/martin-olivier.png?size=85" width=85><br><sub>Martin OLIVIER</sub>](https://github.com/martin-olivier) | [<img src="https://github.com/jeanbaptistedebize.png?size=85" width=85><br><sub>Jean-Baptiste DEBIZE</sub>](https://github.com/jeanbaptistedebize) | [<img src="https://github.com/Tfourcat.png?size=85" width=85><br><sub>Théo FOURCAT</sub>](https://github.com/Tfourcat)
| :---: | :---: | :---: |
<h2 align=center>
