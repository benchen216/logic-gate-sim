#import _build_gate
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

#print(c_logic2['G16gat'])
x_input = dict()
print(c_input)
for i in c_input:
    pass
    #x_input[].(_build_gate.node())
for i in c_output:
    print(c_logic2[i])
def build(t):
    c_logic2[t]
