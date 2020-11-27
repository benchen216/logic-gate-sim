import _build_gate

bench = []
try:
    with open("c17.bench.txt") as file:
        bench = [i.strip("\n") for i in file.readlines()]
except:
    pass
c_input = []
c_output = []
c_logic = []
c_logic2 = dict()
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
        c_logic.append([a[0], b[0], c])
        c_logic2[a[0]] = [b[0], c]
    else:
        pass

# print(c_logic2['G16gat'])
x_input = dict()
x_logic = dict()
x_output = dict()
def build(t):
    gate = None
    if t in x_input:
        return x_input[t]
    elif t in x_logic:
        return x_logic[t]
    if c_logic2[t][0]=="nand":
        gate = _build_gate.mynand
    elif c_logic2[t][0]=="and":
        gate = _build_gate.myand
    elif c_logic2[t][0]=="or":
        gate = _build_gate.myor
    elif c_logic2[t][0]=="xor":
        gate = _build_gate.myxor
    elif c_logic2[t][0]=="nor":
        gate = _build_gate.mynor
    elif c_logic2[t][0]=="not":
        gate = _build_gate.mynot
    elif c_logic2[t][0]=="buf":
        gate = _build_gate.mybuf
    ans = _build_gate.node(gate,[build(i) for i in c_logic2[t][1]])
    x_logic[t]=ans
    return ans

for i in c_input:
    x_input[i] = _build_gate.node()
#print(x_input)
for i in c_output:
    x_output[i]=build(i)
#print(len(x_logic))
#print(x_output)
for i in x_input.values():
    i.str_set("1")
    #i.output()

for i in x_logic.values():
    print(i)
for i in x_output.values():
    #pass
    i.no_run()
print(123)
for i in c_output:
    print(i)
    x_output[i].output()
'''
z=_build_gate.node()
z.str_set("1111")
_build_gate.build_logic([z])
'''