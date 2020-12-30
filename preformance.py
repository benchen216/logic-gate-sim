import parser
import _build_gate
import time
S=time.time()
bench = parser.read_bench(filename="testcase/c432.bench.txt")
c_input, c_logic, c_output = parser.parser_bench(bench)
print(time.time()-S)
x_input, x_logic, x_output = parser.build_bench(c_input, c_logic, c_output)
print(time.time()-S)
_build_gate.build_logic(x_input, x_output, x_logic, str("testcase/c432_1m_ip.txt"), str("test_c432_op32.txt"))
print(time.time()-S)