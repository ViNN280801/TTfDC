# Installing dependencies
from subprocess import call
call(['python', 'inst_dependencies.py'])

# Now we can use things from the `flask` library
from flask import Flask,redirect, render_template, request, session
from random import randint

app = Flask(__name__)
app.secret_key = 'my_secret_key'

def is_authenticated(username: str, psswd: str) -> bool:
    '''
    Description:
        Authentificator for the user. Contains default values to sign in.
        (str): Accepts `username` and `psswd` as a params. 
        
    Returns:
        `True` if sign in was successful, otherwise `False`.
    '''
    return username == 'root' and psswd == 'toor'

@app.route('/', methods=['GET', 'POST'])
def sign_in():
    if request.method == 'POST':
        usrname = request.form.get('username')
        psswd = request.form.get('psswd')
        
        if is_authenticated(usrname, psswd):
            session['signed_in'] = True
            return redirect('/index')
        else:
            return render_template('login.html', message='Invalid username or password')
    
    return render_template('login.html')

@app.route('/index', methods=['GET'])
def main_page() -> str:    
    if session.get('signed_in'):
        number = str(randint(0, 9999))
        session['signed_in'] = False
        return render_template('index.html', number=number)
    else:
        return redirect('/')
    
@app.route('/index', methods=['GET'])
def logout():
    if session['signed_in'] == False:
        return redirect('/')

# Ensure that the app only runs if this script is executed directly
if __name__ == '__main__':
    # Running the Flask app on the local development server
    # By the default Flask uses port 5000
    app.run(host='0.0.0.0')
