# ASU Math Lab

Mathematical library software. Similar to Matlab and Octave . It supports basic and advanced operations 
```
Basic Operations
1- Matrix creation
2- Addition,Subtraction
3- multiplication ,divison and transpose
```

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.


### Installing

A step by step series of examples that tell you have to get a development enviroment running.
In terminal run these commands


```
git clone https://github.com/Team10-cse/AsuMathLabG10.git
cd AsuMathLabG10

```

## Running the tests

Repository already contain files for testing (bigexample.m) (example.m)

### Testing files step by step

these commands will test basic  operations in example.m and print result 

```
 make 
./matrix ./example.m
 make clean
```
### testing without using files

```
make 
./matrix 
```
then write your matrices in this form 
```
A = [8.9 7.3 4.8 2.4; 2.3 6.5 8.9 1.2; 4.9 3.8 7.2 7.5; 9.8 3.4 7.5 8.9]
B = [1.2 5.7 4.2 1.4; 6.3 2.5 8.1 3.1; 6.4 2.8 7.1 8.1; 3.2 5.1 7.2 6.2]
```
then write the operations like this 
```
C = A + B 
D = A * B 

```


## Created by 
```
Team leader :Mohamed Ahmed Selim
Members : Mohamed Morsey 
          Mohamed Osama Mostafa
          Maged Mabrouk
          Basma Mauad
          Salma Khaled 
          Amira Ayman
          Sarah Hamed
          Roba Medhat
```
