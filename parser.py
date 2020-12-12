import _build_gate

def read_bench(filename="c17.bench.txt"):
    try:
        with open(filename) as file:
            bench = [i.strip("\n") for i in file.readlines()]
    except:
        print("I/O error")
    return bench


def parser_bench(bench):
    c_input = []
    c_output = []
    c_logic = dict()
    for i in bench:
        if "#" in i:
            pass
        elif "INPUT" in i:
            c_input.append(i.strip("INPUT(").strip(")"))
        elif "OUTPUT" in i:
            c_output.append(i.strip("OUTPUT(").strip(")"))
        elif "=" in i:
            a = i.split(" = ")
            b = a[1].split("(")
            c = b[1].strip(")").split(", ")
            c_logic[a[0]] = [b[0], c]
        else:
            pass
    return c_input, c_logic, c_output


def build_bench(c_input, c_logic, c_output):
    x_input = dict()
    x_logic = dict()
    x_output = dict()

    def build(t):
        gate = None
        if t in x_input:
            return x_input[t]
        elif t in x_logic:
            return x_logic[t]
        if c_logic[t][0] == "nand":
            gate = _build_gate.mynand
        elif c_logic[t][0] == "and":
            gate = _build_gate.myand
        elif c_logic[t][0] == "or":
            gate = _build_gate.myor
        elif c_logic[t][0] == "xor":
            gate = _build_gate.myxor
        elif c_logic[t][0] == "nor":
            gate = _build_gate.mynor
        elif c_logic[t][0] == "not":
            gate = _build_gate.mynot
        elif c_logic[t][0] == "buf":
            gate = _build_gate.mybuf
        ans = _build_gate.node(gate, [build(i) for i in c_logic[t][1]])
        x_logic[t] = ans
        return ans

    for i in c_input:
        x_input[i] = _build_gate.node()
    for i in c_output:
        x_output[i] = build(i)
    return x_input, x_logic, x_output




def set_value(node, value):
    node.str_set(value)


# print(x_input)
# print(len(x_logic))
# print(x_output)


if __name__ == "__main__":
    bench = read_bench()
    c_input, c_logic, c_output = parser_bench(bench)
    x_input, x_logic, x_output = build_bench(c_input, c_logic, c_output)

    #z = [i for i in x_input]
    #print(x_input,x_logic,x_output)

    _build_gate.build_logic(x_input, x_output)
    '''
    t1=["1111","11110","10111","11011","11101"]
    for j,i in enumerate(x_input.values()):
        set_value(i,t1[j])

    # i.output()
    for i in x_output.values():
        i.no_run()
    for i in c_output:
        print(i)
        #x_output[i].output()
        print(x_output[i].__str__())
    print(x_output)
'''

'''
z=_build_gate.node()
z.str_set("1111")
_build_gate.build_logic([z])
'''
