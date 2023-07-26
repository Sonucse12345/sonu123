#!/bin/bash

# Function to display an error message and exit the program
display_error() {
    echo "Error: $1"
    exit 1
}

# Prompt the user to enter the name of a directory
read -p "Enter the name of the directory: " input_directory

# Check if the directory exists. If it doesn't, display an error message and exit the program.
if [ ! -d "$input_directory" ]; then
    display_error "Directory '$input_directory' does not exist."
fi

# List all the files in the given directory and sort them alphabetically
file_list=$(ls -p "$input_directory" | grep -v / | sort)

# Check if there are files in the directory
if [ -z "$file_list" ]; then
    display_error "No files found in the directory '$input_directory'."
fi

# Create a new directory named "sorted" inside the given directory
sorted_directory="${input_directory}/sorted"
mkdir -p "$sorted_directory"

# Move each file from the original directory to the "sorted" directory
for file in $file_list; do
    mv "${input_directory}/${file}" "$sorted_directory"
done

# Get the total number of files moved
num_files_moved=$(ls -1 "$sorted_directory" | wc -l)

# Display a success message with the total number of files moved
echo "Successfully moved $num_files_moved files to 'sorted' directory inside '$input_directory'."
