import unittest
import parser
import _build_gate


class LogicTest(unittest.TestCase):
    def test_file_with_32_input(self):
        bench = parser.read_bench(filename="testcase/c17.bench.txt")
        c_input, c_logic, c_output = parser.parser_bench(bench)
        x_input, x_logic, x_output = parser.build_bench(c_input, c_logic, c_output)
        ans = []
        for i in range(2):
            for j in range(2):
                for k in range(2):
                    for y in range(2):
                        for z in range(2):
                            ans.append(str(i)+str(j)+str(k)+str(y)+str(z)+"\n")
        ans[-1]=ans[-1].strip("\n")
        with open("test_c17_ip32.txt","w") as file:
            file.writelines(ans)
        _build_gate.build_logic(x_input, x_output, str("test_c17_ip32.txt"), str("test_c17_op32.txt"))
        with open("test_c17_op32.txt","r") as file:
            with open("testcase/test_c17_ans32.txt", "r") as ansfile:
                self.assertEqual(file.readlines(),ansfile.readlines())

