A program to implement a string reversal client-server user-level application using
TCP/UDP socket API in C. A client-server connection is setup, once
connection setups, server accepts strings from clients and replies with reverse
strings. 
The server uses select system call to select the type of client between TCP and UDP.
fork() is used to create a child to fulfill the client request.
