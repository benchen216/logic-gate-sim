CXX =: g++

.PHONY: default
default:
	g++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` compute.cpp _build_gate.cpp -o _build_gate`python3-config --extension-suffix`

.PHONY: clean
clean:
	rm -fr *.o *.dSYM/ *.so *.txt __pycache

.PHONY: test
test:
	make ; pytest -v