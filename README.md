# QtAsciiArt

**QtAsciiArt** is a program written using the Qt framework that converts BMP images into ASCII art.

### Description

QtAsciiArt allows users to load BMP format images and convert them into ASCII art. The program uses algorithms to analyze the image and transform it into a textual form, preserving the main visual elements.

### Installation

1. Clone the repository:
```bash
git clone https://github\.com/Silvarious9862/QtAsciiArt\.git
```

2. Navigate to the project directory:
```bash
cd QtAsciiArt
```

3. Build the project using Qt:
```bash
qmake
make
```

### Usage

1. Run the program:
```bash
\./QtAsciiArt
```

2. Load a BMP format image using the program's interface. You can use stock images from ./samples/
3. Select the quality of the artwork and specify the characters used for generation.
4. Click the "Generate" button to generate the ASCII art version of the image.
5. Copy art to clipboard with *Copy* button or save the result to a text file if needed.

### Samples
##### Road in the field
![normal1](https://github.com/user-attachments/assets/68bbbef7-d734-44c6-a334-9034aa22ed2e)
![image](https://github.com/user-attachments/assets/d7e67294-fcb6-4c9a-8d67-f35fc985e18a)

##### Cherries
![normal3](https://github.com/user-attachments/assets/6582f74e-e153-4d38-b75f-820e71f7227a)
![image](https://github.com/user-attachments/assets/b7f467bf-2cc1-4e46-bfbc-7c2c52c9685c)

##### Beaver
![normal7](https://github.com/user-attachments/assets/a97f77bf-c3db-483e-8ab4-b5f3e69eea5e)
![image](https://github.com/user-attachments/assets/8c9a5b8e-6ffe-4b07-960d-e6497468ca47)


### Requirements

Qt 5.15 or higher
A compiler that supports C++
