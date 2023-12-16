#!/bin/bash

while true; do
    # Display the shell prompt
    read -p "$ " command

    # Check if the command is "exit"
    if [ "$command" = "exit" ]; then
        echo "Exiting shell."
        break
    else
        # Execute the command using eval
        eval "$command"
    fi
done

