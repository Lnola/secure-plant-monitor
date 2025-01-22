#!/usr/bin/env python3

import subprocess

commands = [
    """mosquitto_sub -h 188.245.235.247 --cafile ~/Downloads/ca.crt --cert ~/Downloads/client.crt --key ~/Downloads/client.key -p 8883 -t 'lnola/sensor/light-level' """,
    """mosquitto_sub -h 188.245.235.247 --cafile ~/Downloads/ca.crt --cert ~/Downloads/client.crt --key ~/Downloads/client.key -p 8883 -t 'lnola/sensor/temperature' """,
    """mosquitto_sub -h 188.245.235.247 --cafile ~/Downloads/ca.crt --cert ~/Downloads/client.crt --key ~/Downloads/client.key -p 8883 -t 'lnola/sensor/humidity' """,
    """mosquitto_sub -h 188.245.235.247 --cafile ~/Downloads/ca.crt --cert ~/Downloads/client.crt --key ~/Downloads/client.key -p 8883 -t 'lnola/sensor/flame' """,
]

def open_tab_with_horizontal_splits_and_run_commands(commands):
    applescript = """
    tell application "iTerm2"
        activate
        tell current window
            create tab with default profile
            tell current session
                split horizontally with default profile
                split horizontally with default profile
                split horizontally with default profile
            end tell
    """
    # Run the commands in the respective panes
    for index, command in enumerate(commands):
        applescript += f"""
            tell session {index + 1} of current tab
                write text "{command.replace('"', '\\"')}"
            end tell
        """
    applescript += """
        end tell
    end tell
    """

    # Execute the AppleScript
    subprocess.run(["osascript", "-e", applescript])

# Run the function
open_tab_with_horizontal_splits_and_run_commands(commands)
