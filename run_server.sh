#!/bin/bash

# Start Python HTTP server in the background
python3 -m http.server 8000 &

# Save the process ID
SERVER_PID=$!

# Wait a moment for the server to start
sleep 2

# Open Chrome to the local server
# This command works on macOS. Adjust for other operating systems if needed.
open http://localhost:8000

# Wait for user input to terminate
echo "Press Enter to terminate the server"
read

# Kill the Python server process
kill $SERVER_PID
