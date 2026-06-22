# 1. Use a lightweight Linux environment with Python pre-installed
FROM python:3.10-slim

# 2. Install the C++ Compiler (g++) inside the Linux container
RUN apt-get update && apt-get install -y g++

# 3. Set up a working folder inside the container
WORKDIR /app

# 4. Copy all your files (HTML, C++, Python) from GitHub into the container
COPY . .

# 5. Install Flask and Gunicorn
RUN pip install -r requirements.txt

# 6. Compile the C++ program specifically for Linux!
# (Notice we are compiling it as 'peakbot', not 'peakbot.exe')
RUN g++ main.cpp -o peakbot

# 7. Start the server using Gunicorn and bind it to the port Render gives us
CMD gunicorn app:app --bind 0.0.0.0:$PORT