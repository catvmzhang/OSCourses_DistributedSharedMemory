# OSCourses_DistributedSharedMemory

In this assignment, we are going to implement a client-server communication service, which is based on a distributed shared memory architecture. 
For this server, we are going to implement a distributed share memory server.
This server should include:
1. Use multi-threading to implement distributed shared memory.
2. Prevent the race condition problem which means none of the clients will get any same drawing result (number).
3. A random list of the number 1 to 100,000 and use a counter to record the index of the list for current drawing result (number). Because the function of list, like pop(), is thread-safe, if you use those function, you will get no score in this homework.
4. Server can be connected by multiple client.
5. Server should send the drawing result (number) back to client.

simply to say, prevent for the race condition.
