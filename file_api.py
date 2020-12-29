import sys, getopt
import parser
import _build_gate
import time
def main(argv):
    inputfile = ''
    outputfile = ''
    benchfile = ''
    t=False
    try:
        opts, args = getopt.getopt(argv, "thi:o:b:",["ifile=","ofile="])
    except getopt.GetoptError:
        print("file_aip.py -i <inputfile> -o <outputfile> -b <benchfile>")
        sys.exit(2)
    for opt, arg in opts:
        if opt == "-h":
            print("file_aip.py -i <inputfile> -o <outputfile> -b <benchfile>")
            sys.exit(2)
        elif opt == "-t":
            t = True
        elif opt in ("-i","--ifile"):
            inputfile = arg
        elif opt in ("-o", "--ofile"):
            outputfile = arg
        elif opt in ("-b", "--bfile"):
            benchfile = arg
        else:
            pass
    #print(inputfile,outputfile,benchfile )
    S=time.time()
    bench = parser.read_bench(filename=benchfile)
    c_input, c_logic, c_output = parser.parser_bench(bench)
    if t:
        print("parser bench time:", time.time()-S)
    x_input, x_logic, x_output = parser.build_bench(c_input, c_logic, c_output)
    if t:
        print("build bench time:", time.time()-S)
    _build_gate.build_logic(x_input, x_output, x_logic, str(inputfile), str(outputfile))
    if t:
        print("run time:", time.time()-S)

if __name__ == "__main__":
    main(sys.argv[1:])
