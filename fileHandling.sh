#!/bin/bash

echo "------ File Handling Menu ------"
echo "1. Create File"
echo "2. Write to File"
echo "3. View File"
echo "4. Exit"

while true
do
    read -p "Enter your choice: " choice

    case $choice in
        1)
            read -p "Enter filename: " fname
            touch $fname
            echo "File '$fname' created."
            ;;
        
        2)
            read -p "Enter filename: " fname
            if [ -f $fname ]; then
                read -p "Enter text to write: " text
                echo $text >> $fname
                echo "Text written to '$fname'."
            else
                echo "File does not exist!"
            fi
            ;;
        
        3)
            read -p "Enter filename: " fname
            if [ -f $fname ]; then
                echo "------ File Content ------"
                cat $fname
                echo ""
            else
                echo "File does not exist!"
            fi
            ;;
        
        4)
            echo "Exiting..."
            exit ;;
        
        *)
            echo "Invalid choice! Try again." ;;
    esac
done
