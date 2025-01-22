#!/usr/bin/env python3

import subprocess

commands = [
    """mosquitto_sub -h 188.245.235.247 --cafile ~/Downloads/ca.crt --cert ~/Downloads/client.crt --key ~/Downloads/client.key -p 8883 -t 'lnola/sensor/light-level' """,
    """mosquitto_sub -h 188.245.235.247 --cafile ~/Downloads/ca.crt --cert ~/Downloads/client.crt --key ~/Downloads/client.key -p 8883 -t 'lnola/sensor/temperature' """,
    """mosquitto_sub -h 188.245.235.247 --cafile ~/Downloads/ca.crt --cert ~/Downloads/client.crt --key ~/Downloads/client.key -p 8883 -t 'lnola/sensor/humidity' """,
    """mosquitto_sub -h 188.245.235.247 --cafile ~/Downloads/ca.crt --cert ~/Downloads/client.crt --key ~/Downloads/client.key -p 8883 -t 'lnola/sensor/flame' """,
]

def run_iterm_commands(commands):
    script = """
    tell application "iTerm2"
        activate
        set newWindow to (create window with default profile)
    """
    for index, command in enumerate(commands):
        if index == 0:
            # First command runs in the initial tab
            script += f"""
            tell current session of newWindow
                write text "{command.replace('"', '\\"')}"
            end tell
            """
        else:
            # Subsequent commands open in new tabs
            script += f"""
            tell newWindow
                create tab with default profile
                tell current session
                    write text "{command.replace('"', '\\"')}"
                end tell
            end tell
            """
    script += "end tell"

    # Execute the AppleScript
    subprocess.run(["osascript", "-e", script])


# Run the script
run_iterm_commands(commands)
