<h1 align="left">Dynamic Array of Structures – ADT Implementation (C)</h1>
<p align="left"> This project implements an <b>Abstract Data Type (ADT)</b> for managing a dynamic array of structures in C.<br><br>

Define and manage a structure <b>Stat</b><br>
Perform full CRUD operations<br>
Dynamically allocate and resize memory<br>
Sort, search, insert, delete elements<br>
Save and load data from files<br><br>

The project follows a modular architecture and demonstrates strong understanding of memory management and structured programming.

</p>
<h2 align="left">Project Architecture</h2>
<p align="left"> The application is divided into three core components: </p> <div align="left">

📄 <b>header.h</b> → Structure definition & function prototypes<br>
📄 <b>functions.c</b> → Implementation of all operations<br>
📄 <b>main.c</b> → Menu-driven user interface<br>

</div>
<h2 align="left">Structure Definition</h2>
<div align="center"> <pre> Stat(Name of country, capital, area, population, PIB); </pre> </div>
<h2 align="left">Application Menu</h2>
<div align="left"> <pre> 
  1) Add data (Firstly / Lasted / After indicated element / Before indicated element) 
  2) view data
  3) Seach element form storage data
  4) Edit data
  5) Switch 2 elements
  6) Sort storage data
  7) Deleted choused element
  8) Save data in file
  9) Read data from file
  h) View menu option
  c) Clean screen panel
  0) EXIT
</pre> </div>
<img height="250" src="https://github.com/ALFA64/PC_and_SDA_project/blob/SDA_project/LAB_1/img/Imagine1.png"/>
<h2 align="left">Core Functionalities</h2>
<div align="left">

✔ Dynamic allocation using <code>malloc()</code><br>
✔ Dynamic resizing using <code>realloc()</code><br>
✔ Memory deallocation using <code>free()</code><br>
✔ Sorting by population<br>
✔ Searching by name<br>
✔ File persistence<br>
✔ Modular clean code structure<br>

</div>
<h2 align="left">Compilation</h2>
<div align="center"> <pre> gcc main.c functions.c -o program.exe </pre> </div>
<h2 align="left">Run program</h2>
<div align="center"> <pre> ./program.exe </pre> </div>
<h2 align="left">Concepts Demonstrated</h2>
<div align="left">

• Abstract Data Types (ADT)<br>
• Structured programming in C<br>
• Pointer manipulation<br>
• Dynamic memory management<br>
• File I/O operations<br>
• Modular software design<br>
</div>
