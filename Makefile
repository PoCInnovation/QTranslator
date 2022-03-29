all:
	@cmake . -B build/ -DCMAKE_BUILD_TYPE=Debug
	@cmake --build build/

clean:
	@rm -rf build
	@rm -rf QTranslator

.PHONY: all clean