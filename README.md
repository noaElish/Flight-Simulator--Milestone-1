 <p align="center">
 <img src="https://upload.wikimedia.org/wikipedia/commons/3/34/FlightGear_Logo.svg" width="80" height="80">
</p>
<p align="center">
# Flight Simulatur 
</p>


#### Creators: 
##### Shira Turgeman & Noa Elishmereni

### **Basic information**
* Purpose of this extercise-
Create code that allows remote control of an aircraft.

* Links we used for this project:
   * [FlightGear simulator](https://www.flightgear.org/)

* Files we used for this project:
   * Fly.txt
   * Generic_small.xml

### **important classes, variables and objects:**
* Class command
* Class SymbolTable- holds Three maps:
   * symbolMap: for the variables objects.
   * simMap: for the simulator objects.
   * commandMap: for all the command variable.
   
### **how does it work?**
Our program receives a file and breaks it into parts using the **lexer** function. We checked which of the strings were commands, and created a map that holds commands as the key, and a value that is a command variable from Of the right type. 
  * for example: we inserted the command "open data server" into the map, with a variable "OpenServerCommand" as the value.
  
after inserting the map with all the right commands, we started to execute each commnad by turn usuing the **parser** function. for the server and the client, we opened two different threads that runs simultaneously, and two different sockets.
next, the parser executed all of the variables. for each one, we check the direction of the arrow, and accordingly changes the values in the maps.

through the whole run of the programm, we received values from the simulator (using the server socket), and sending value to the simulator (using the client socket). that way, the connection stay open through the whole run.

after wer'e done with the file, the programm prints "done" and we can close the sockets, and the threads.

