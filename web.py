from flask import Flask,  render_template, request, redirect, url_for, send_file
import os
import time
import parser
import _build_gate
from werkzeug.utils import secure_filename
UPLOAD_FOLDER = './tmp'
ALLOWED_EXTENSIONS = set(['pdf', 'png', 'jpg', 'jpeg', 'gif', 'txt', 'csv'])
app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024  # 16MB


def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1] in ALLOWED_EXTENSIONS


@app.route('/', methods=['GET'])
def cal_ans():
    mybench = os.path.isfile("./tmp/mybench.txt")
    myinput = os.path.isfile("./tmp/myinput.txt")
    return '''
    <!doctype html>
    <title>Wellcome to logic-gate-sim </title>
    <h1>Wellcome to logic-gate-sim</h1>
    <a href="/upload_bench">upload bench file</a>
    '''+str(mybench)+'''<br>
    <a href="/upload_input">upload input file</a>
    '''+str(myinput)+'''<br>
    <a href="/download">download outfile file</a>
    '''+'''<br>
    <a href="/del">clean input status file</a>
    '''
@app.route('/del')
def clear_file():
    try:
        os.remove('./tmp/myinput.txt')
        os.remove("./tmp/mybench.txt")
    except:
        pass
    return redirect("/")

@app.route('/download')
def downloadFile():
    inputfile = './tmp/myinput.txt'
    outputfile = './tmp/output.txt'
    benchfile = "./tmp/mybench.txt"
    t=False
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
    path = "./tmp/output.txt"
    return send_file(path, as_attachment=True)

@app.route('/upload', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'],
                                   filename))
            return '''
            <!doctype html>
            <title>Upload new File</title>
            <h1></h1>
            '''
    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form action="" method=post enctype=multipart/form-data>
      <p><input type=file name=file>
         <input type=submit value=Upload>
    </form>
    '''

@app.route('/upload_input', methods=['GET', 'POST'])
def upload_input():
    if request.method == 'POST':
        file = request.files['file']
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'],
                                   "myinput.txt"))
            return redirect("/")
    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form action="" method=post enctype=multipart/form-data>
      <p><input type=file name=file>
         <input type=submit value=Upload>
    </form>
    '''


@app.route('/upload_bench', methods=['GET', 'POST'])
def upload_bench():
    if request.method == 'POST':
        file = request.files['file']
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'],
                                   "mybench.txt"))
            return redirect("/")
    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form action="" method=post enctype=multipart/form-data>
      <p><input type=file name=file>
         <input type=submit value=Upload>
    </form>
    '''



if __name__ == '__main__':
    app.run(host='0.0.0.0')
