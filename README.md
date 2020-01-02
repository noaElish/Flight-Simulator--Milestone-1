 <img src="https://upload.wikimedia.org/wikipedia/commons/3/34/FlightGear_Logo.svg" width="100" height="100">

## EX3 Project- Flight Simulatur 

###### Submitted by- Shira Turgeman & Noa Elishmereni

#### **Basic information**
* Purpose of this extercise-
Create code that allows remote control of an aircraft.

* Links we used for this project:
   * ‫‪Download the flightgear simulator- [flightGear](https://www.flightgear.org/)

* Files we used for this project:
   * fly.txt- 
   * generic_small.xml- 

### **important classes, variables and objects:**
1. class command

#### **how does it work?**
Our program receives a file and breaks it into parts using the **lexer** function. We checked which of the strings were commands, and created a map that holds commands as the key, and a value that is a command variable from Of the right type. 
  -for example: we inserted the command "open data server" into the map, with a variable "OpenServerCommand" as the value.
after inserting the map with all the right commands, we started to execute each commnad by turn usuing the **parser** function. for the server and the client, we opened two different threads that runs simultaneously, and two different sockets.
next, the parser executed all of the variables.
through the whole run of the programm, we received values from the simulator (using the server socket), 
