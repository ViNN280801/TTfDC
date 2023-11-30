# Installing dependencies
from subprocess import call
call(['python', 'inst_dependencies.py'])

# Now we can use things from the `flask` library
from flask import Flask, request
from random import randint

# Defining the name of the application
app = Flask(__name__)

# Defining directory and available methods
@app.route('/', methods=['GET'])
def greeting() -> str:
    '''
    Description:
        Handles the GET request to the root URL ("/").
        
    Returns:
        4 digit number as a result.
    
    Usage example:
        curl -i -H "Accept: application/json" -H "Content-Type: application/json" -X GET "http://127.0.0.1:5000/"  
    '''
    
    # Using `try-catch` wrapper to make function exception-safe
    try:
        return str(randint(0, 9999))
    except Exception as excp:
        return f'Exception raised: {str(excp)}.\n'

# Ensure that the app only runs if this script is executed directly
if __name__ == '__main__':
    # Running the Flask app on the local development server
    # By the default Flask uses port 5000
    app.run(host='0.0.0.0')
