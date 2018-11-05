# TME
TME (short for Text-Math-Editor) is a program for writing technical documentations, programmed in Qt.
Beside the WYSIWYG-document view there's an integrated computer algebra system (uses ALGLIB), which, as of the first release, solves simple algebraic formulas. The results and formulas themselves can be integrated into the document and get updated automatically when exporting or saving  the file as a pdf.

![alt tag](https://raw.githubusercontent.com/nfbyfm/TME/master/docs/screenshot.jpg)

The program is translated into german and english (above is the german version). Absolutely no guarantees provided. License: GPL V3. No liability can be accepted for any damage caused by software and/or the use of the software.

## Links

- [Wiki](https://github.com/nfbyfm/TME/wiki)
- [Releases](https://github.com/nfbyfm/TME/releases)
- [Source-Code-Documentation](https://nfbyfm.github.io/TME/)

## Capabilities

This application can solve simple (linear) equations, defined in the toolbar on the right hand side. 
Each equation or single variable can then be liked into the main text-document. When one of the print functions (creation of a pdf as well)
 gets called, the results from the math-solver get plugged into the text.

## Usage

With the application technical documentations can be written. The formatation can be changed similar to any other 
word processing-software. A special addon however is the possiblity to define mathematical formulas (written in the [ASCII-Math](http://asciimath.org/#syntax)-style), 
which will get automatically solved and plugged into the text-document, once one of the print-functions gets called.

Adding images and tables is possible as well, though with not many functions as of yet.


## How it works

The program is based on Qt (programmed in C++) and uses the [ALGLIB](http://www.alglib.net/)-Library for solving the equations. 
The lexer and parser (parts of the math-engine) need [ASCII-Math](http://asciimath.org/#syntax)-formated formulas in order to function correctly.
