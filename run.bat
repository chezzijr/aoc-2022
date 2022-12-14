@echo off
if exist "Day %1"\ (
    cd "Day %1"
    if exist day%1.cpp (
        g++ -std=c++20 day%1.cpp -o day%1.exe && day%1.exe
    ) else if exist day%1.py (
        py day%1.py
    ) else (
        echo Cannot run day %1's code. Please check if there is a day%1.cpp file or day%1.py file.
    )
    cd ..
) else (
    echo No folder 'Day %1' found.
)