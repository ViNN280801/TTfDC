# Installing dependencies
from subprocess import call
call(['python', 'inst_dependencies.py'])

# Now we can use things from the `flask` library
from flask import Flask, request

# Defining the name of the application
app = Flask(__name__)

# Defining directory and available methods
@app.route('/', methods=['GET'])
def greeting() -> str:
    '''
    Description:
        Handles the GET request to the root URL ("/").
        Retrieves 'name' and 'message' parameters from the request's query string.
        
    Returns:
        1) If both 'name' and 'message' are provided, it constructs a greeting response.
        2) If either 'name' or 'message' is missing, it returns a warning message.
        3) If an exception occurs during execution, it returns an exception message.
    
    Usage example:
        curl -i -H "Accept: application/json" -H "Content-Type: application/json" -X GET "http://127.0.0.1:5000/?name=Recruto&message=Let%20be%20a%20friends"        
    '''
    
    # Using `try-catch` wrapper to make function exception-safe
    try:
        # Getting name and message arguments from the GET request
        name = str(request.args.get('name'))
        msg = str(request.args.get('message'))

        # If name and message are not empty - return response as a greeting string
        if (name.strip() != '' and msg.strip() != '') and (name.strip() != 'None' and msg.strip() != 'None'):
            return f"Hello {name}! {msg}!\n"
        # Else if any of them is empty - return the warning message
        else:
            # Bruteforcing all possible cases
            if (name.strip() == '' and msg.strip() == '') or (name == 'None' and msg == 'None'):
                return 'Warning: Name and message are empty. Try to rewrite your request.\n'
            elif (name == '' or name == 'None') and msg.strip() != '':
                return 'Warning: Name is empty. Try to rewrite your request.\n'
            elif name.strip() != '' and (msg == '' or msg == 'None'):
                return 'Warning: Message is empty. Try to rewrite your request.\n'
            else:
                return 'Warning: unknown error was occured.\n'
    # If smth goes wrong - do not let our service to work non-properly.
    # Just returning a message with exception information as a response
    except Exception as excp:
        return f'Exception raised: {str(excp)}.\n'

# Ensure that the app only runs if this script is executed directly
if __name__ == '__main__':
    # Running the Flask app on the local development server
    # By the default Flask uses port 5000
    app.run(host='0.0.0.0')
