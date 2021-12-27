# Synesthesia

## Desciption
Transforms an .io file into QASM. The goal is to create a quantum calculator.

## Summary
  - [Desciption](#desciption)
  - [Summary](#summary)
  - [Install](#install)
    - [:rocket: Clone repository](#rocket-clone-repository)
    - [:warning: Requirement](#warning-requirement)
  - [:writing_hand: How to write .io](#writing_hand-how-to-write-io)
    - [Example](#example)
  - [:checkered_flag: Quick-Start](#checkered_flag-quick-start)
  - [More informations](#more-informations)
    - [Manual](#manual)
    - [Build and run unit tests](#build-and-run-unit-tests)
    - [Build Tips](#build-tips)
  - [Authors](#authors)
  
## Install

### :rocket: Clone repository

```shell
git@github.com:PoCInnovation/QTranslator.git
```

### :warning: Requirement

- [CMake >= 3.17](https://cmake.org/download/)
- [C++20](https://en.cppreference.com/w/cpp/20)

## :writing_hand: How to write .io
### Example
Create a file create **operations.io**.  
The custom language must follow this pattern:  
```python
# operations.io

int i 3
int j 10

add i 5
sub i 5
add i j
```

## :checkered_flag: Quick-Start

```shell
make
./QTranslator operations.io
```

## More informations
### Manual

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


### Build and run unit tests

To build the tests, execute the following command :  
```make tests```

After that, you will be able to run them using the following command :  
```./QTranslatorTests```

### Build Tips

If you want to remove all objects files :  
`make clean`  

## Authors

| [<img src="https://github.com/tocola.png?size=85" width=85><br><sub>Martin OLIVIER</sub>](https://github.com/tocola) | [<img src="https://github.com/jeanbaptistedebize.png?size=85" width=85><br><sub>Jean-Baptiste DEBIZE</sub>](https://github.com/jeanbaptistedebize) | [<img src="https://github.com/Tfourcat.png?size=85" width=85><br><sub>Théo FOURCAt</sub>](https://github.com/Tfourcat)
| :---: | :---: | :---: |
<h2 align=center>