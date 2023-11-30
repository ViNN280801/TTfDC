# InfotecsTestTask
This is client-server application written on sockets.

Program No. 1.
It should consist of two streams and one shared buffer.
Stream 1. Accepts the string that the user enters. There should be a check that the string consists only of digits and does not exceed 64 characters. After checking, the string should be sorted in descending order and all elements whose value is even are replaced with Latin letters "KV". After that, this line is placed in the shared buffer and the stream should wait for further user input.
Stream 2. Must process data that is placed in a shared buffer. After receiving the data, the shared buffer is overwritten. The stream should display the received data on the screen, calculate the total sum of all the elements that are numerical values. Transfer the received amount to Program No. 2. After that, the thread waits for the following data.
Note #1 on Program #1: The interaction of threads must be synchronized, thread #2 should not constantly poll the shared buffer. The synchronization mechanism should not be a global variable.
Note No. 2 on Program No. 1: The operation of the program should be as independent as possible from the launch status of program No. 2. This means that the sudden shutdown of program No. 2 should not lead to immediate input problems for the user.
When restarting program No. 2, it is necessary to reconnect.


Program No. 2.
Waits for data from Program #1. When data is received, an analysis is performed of how many characters the transmitted value consists of. If it is more than 2 characters and if it is a multiple of 32, it displays a message about the received data, otherwise an error message is displayed. Then the program continues to wait for data.
Note No. 1 on Program No. 2: The operation of the program should be as independent as possible from the launch status of program No. 1. A sudden shutdown of program #1 should not lead to immediate display problems. It is necessary to expect the connection of program No. 1 when the connection between the programs is lost.
Note on the assignment: It is not necessary to place everything in one class. A hierarchy of classes can be developed. The more functional the interface of the class, the better.
