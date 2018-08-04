//
//  Core.cpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/7/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "Mail.h"
#include "FS.h"
#include "Arduino.h"

#define MAX_MAIL_SIZE 0

int mailCount[1] = {0};
int readCount[1] = {0};

void newMessage(String message){
	if (message.length() > MAX_MAIL_SIZE){
		Serial.println("FILING AWAY :: " + message);
		byte progNum = message[0] - '0';
		char b[10]; 
		itoa(mailCount[progNum], b, 10);
		String name = String("/p") + String(message[0]) + String("m") + String(b) + String(".txt");
		File f = SPIFFS.open(name, "w");
		f.print(message);
		f.close();
		mailCount[progNum]++;
	}
}

int checkForMessage(byte progNum){
	if (mailCount[progNum] > readCount[progNum]){

		char b[10]; 
		itoa(readCount[progNum], b, 10);
		String name = String("/p") + String(progNum) + String("m") + String(b) + String(".txt");
		File f = SPIFFS.open(name, "r");
		int size = f.size();
		f.close();
		return size;
	}
	return 0;
}

void readMail(byte progNum, char *buffer, int size){
	if (mailCount[progNum] > readCount[progNum]){
		char b[10]; 
		itoa(readCount[progNum], b, 10);
		String name = String("/p") + String(progNum) + String("m") + String(b) + String(".txt");
		File f = SPIFFS.open(name, "r");
		//Serial.println("READING OUT ::" + f.readString());
		f.readBytes(buffer, size);
		buffer[size] = '\0';
		f.close();
		readCount[progNum]++;
	}
}

