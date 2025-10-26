# 🧠 MyScanner

## 📁 Project Files
| File | Description |
|------|--------------|
| `main.cpp` | The main file that runs the lexical analyzer. |
| `scanner.cpp` | Contains the functions that check and classify tokens. |
| `scanner.hpp` | Header file for function declarations. |
| `test.txt` | Input file that contains the C-like code to analyze. |
| `images/` | Folder containing example input and output images. |

---

## ⚙️ How to Compile and Run
```bash
g++ main.cpp scanner.cpp -std=c++11 -o scanner
./scanner

⚠️ Important Note

Make sure that the file test.txt is in the same directory as the executable.
Otherwise, the program won’t be able to open it.

If you prefer to use a custom path,
you can edit the file path directly inside main.cpp where the function
lexicalAnalyze("test.txt") is called — just replace "test.txt" with your full path.


## 🖼️ Examples

[Input Example](https://github.com/baraaa00/MyScanner/blob/main/images/input.png)  

[Output Example](https://github.com/baraaa00/MyScanner/blob/main/images/output.png)  

> Click any link above to open the image directly on GitHub.
