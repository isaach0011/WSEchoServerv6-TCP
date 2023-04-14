// Author: Isaac Hill
// Assignment: CS 2690 Program 2
// File: ProcessClient.c
// Instructor: Imtiaz Parvez
// Class: CS 2690  Section: 001
// Date Written: 3/16/2023
// Last update: 3/16/2023
// Windows Version: Windows 10    Visual Studio Version: Visual Studio Community 2019
// Description: This file contains the ProcessClient function that will receive the message sent 
//              by the client and then send the message back.
// ----------------------------------------------------------------------------

#include <winsock2.h>	// for Winsock2 functions

#define RCVBUFSIZ 50    // using a default of 50

void DisplayFatalErr(char* errMsg); // writes error message before abnormal termination

void ProcessClient(SOCKET clientSock) // clientSock contains information about the client's socket
{
	char rcvBuffer[RCVBUFSIZ];  // contains the received message from the client
	int rcvRead = 0;            // contains the amount of bytes received from the client

	// Run at least once and continue looping until the client as closed the connection
	do
	{
		// Call recv() and update rcvRead to equal the amount of bytes received from the client
		// If rcvRead contains a number less than 0, an error has occured
		if ((rcvRead = recv(clientSock, rcvBuffer, RCVBUFSIZ - 1, 0)) < 0)
		{
			DisplayFatalErr("recv() function failed.");
		}

		// Check if rcvRead is more than 0
		// If so, there is a message that was received
		// Else, the client has closed the connection
		if (rcvRead > 0)
		{
			// If the amount of sent bytes doesn't equal the amoung received, and error has occured
			if (send(clientSock, rcvBuffer, rcvRead, 0) != rcvRead)
			{
				DisplayFatalErr("send() function failed.");
			}
		}

	} while (rcvRead != 0); // If rcvRead == 0, the client has closed the connection

	// Close the client socket
	closesocket(clientSock);
}