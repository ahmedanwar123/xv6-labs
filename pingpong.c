/*
Name: Ahmed Anwar Mazhar
ID: 120210007
*/

#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int p[2];              // File descriptors for pipe
    char recv_buf[5];     // Buffer to store received data (+1 for null terminator)

    // Create a pipe
    pipe(p);

    if (fork() == 0) {    // Child process
        // Close the write end of the pipe in the child
        close(p[1]);      // Close write end

        // Read from the pipe
        read(p[0], recv_buf, 4);
        recv_buf[4] = '\0'; // Null-terminate the string
        close(p[0]);      // Close read end

        // Print received message (use 1 for STDOUT)
        printf(1, "%d: received %s\n", getpid(), recv_buf);

        // Write response back to the pipe
        write(p[1], "pong", 4);
        close(p[1]);      // Close write end

        exit();           // Exit child process
    } else {              // Parent process
        // Close the read end of the pipe in the parent
        close(p[0]);      // Close read end

        // Write message to child
        write(p[1], "ping", 4);
        close(p[1]);      // Close write end

        // Read response from child
        read(p[0], recv_buf, 4);
        recv_buf[4] = '\0'; // Null-terminate the string
        close(p[0]);      // Close read end

        // Print received message (use 1 for STDOUT)
        printf(1, "%d: received %s\n", getpid(), recv_buf);
        
        // Wait for child process to avoid zombie
        wait();           // Wait for the child process to finish

        exit();           // Exit parent process
    }
}
