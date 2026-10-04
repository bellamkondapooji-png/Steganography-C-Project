🔐 Steganography in C — Hiding Data in Plain Sight

A low-level C implementation of image steganography using the Least Significant Bit (LSB) technique.

🧩 What is this project?

What if an image could carry a secret message without visibly changing its appearance?
This project explores that idea by hiding secret text inside a BMP image using the Least Significant Bit (LSB) technique.
The program provides two operations:
Encode 🔒 — Hide secret data inside an image
Decode 🔓 — Extract the hidden data from the encoded image

The goal was not just to make it work, but to understand what happens at the byte and bit level while manipulating real files using C.

⚙️ How It Works
🔒 Encoding
Secret Message
      ↓
Read Secret File
      ↓
Read BMP Image
      ↓
Store Data in Image Bits
      ↓
Generate Stego Image

The program modifies the least significant bits of image data to store the secret information.

Because only the least significant bits are changed, the visual appearance of the image remains practically unchanged.

🔓 Decoding
Stego Image
     ↓
Read Embedded Data
     ↓
Extract Bits
     ↓
Reconstruct Secret Data
     ↓
Original Secret Message

🚀 Running the Project
Compile
gcc *.c
Encode a secret message
./a.out -e beautiful.bmp secret.txt
Decode the hidden message
./a.out -d stego.bmp

🛠️ Built With
Area	Concepts
Language	C
Data Hiding	LSB Steganography
File Processing	File Handling / Binary Files
Memory	Pointers
Data Organization	Structures
Low-Level Operations	Bitwise Operations
Interface	Command-Line Arguments
Image Format	BMP

📂 Project Structure
Steganography-C-Project/
│
├── main.c          → Program entry point
├── encode.c        → Encoding implementation
├── encode.h        → Encoding declarations
├── decode.c        → Decoding implementation
├── decode.h        → Decoding declarations
├── common.h        → Common definitions
├── types.h         → Data types and structures
│
├── beautiful.bmp   → Sample input image
└── secret.txt      → Sample secret data

💡 What I Learned
This project helped me move beyond basic C syntax and understand how C can interact directly with files and binary data.

Key takeaways:
Working with binary files, Understanding BMP image structure, Manipulating individual bits, 
Using pointers and structures, Handling files using C, Passing information through command-line arguments,
Designing separate encoding and decoding modules, Understanding how data can be represented at the bit level.

🎯 Why I Built This

I built this project as part of my journey toward Embedded Systems development.
Steganography gave me an opportunity to practice concepts that are important in low-level programming:
Memory → Bytes → Bits → Data
Instead of treating files as just text, this project helped me understand how information can be manipulated at a much lower level.


