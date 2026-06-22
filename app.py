from flask import Flask, request, jsonify
import subprocess
import os
import re

app = Flask(__name__, static_folder='.', static_url_path='')
session_history = []

@app.route('/')
def home():
    return app.send_static_file('index.html')

@app.route('/api/chat', methods=['POST'])
def chat():
    user_text = request.json.get('message', '')
    print(f"\n--- 1. NEW MESSAGE RECEIVED: '{user_text}' ---")

    if user_text.upper() == "CLEAR":
        session_history.clear()
        return jsonify({"reply": "Memory cleared. Ready for new data."})

    session_history.append(user_text)
    execution_script = "\n".join(session_history) + "\nQUIT\n"
    
    # Force Python to look in the exact folder for 'peakbot.exe'
    current_folder = os.path.dirname(os.path.abspath(__file__))
    exe_name = os.path.join(current_folder, "peakbot.exe" if os.name == 'nt' else "peakbot")
    
    print(f"--- 2. LOOKING FOR C++ FILE AT: {exe_name} ---")
    
    if not os.path.exists(exe_name):
        print("!!! ERROR: C++ file not found. !!!")
        return jsonify({"reply": "Error: I cannot find peakbot.exe. Please recompile your C++ code."})

    print("--- 3. C++ FILE FOUND. EXECUTING ALGORITHM... ---")
    
    try:
        process = subprocess.run(
            [exe_name],
            input=execution_script,
            text=True,
            capture_output=True,
            timeout=5
        )
        print("--- 4. EXECUTION FINISHED SUCCESSFULLY. ---")
        
        output_lines = process.stdout.split('\n')
        clean_lines = [re.sub(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])', '', line) for line in output_lines]
        bot_responses = [line.replace('Bot: ', '').strip() for line in clean_lines if "Bot:" in line and "Shutting down" not in line]

        if "OPTIMIZE" in user_text.upper() and len(bot_responses) >= 3:
            final_reply = "<br>".join(bot_responses[-3:]) 
        else:
            final_reply = bot_responses[-1] if bot_responses else "Ready."

        print("--- 5. SENDING REPLY TO WEBSITE. ---")
        return jsonify({"reply": final_reply})

    except subprocess.TimeoutExpired:
        print("!!! ERROR: C++ program took too long and was killed. !!!")
        return jsonify({"reply": "Error: The C++ program timed out."})
    except Exception as e:
        print(f"!!! SERVER ERROR: {str(e)} !!!")
        return jsonify({"reply": f"Server Error: {str(e)}"})

if __name__ == '__main__':
    app.run(debug=True, port=5000)