//
//  Mail.hpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/7/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#ifndef Mail_hpp
#define Mail_hpp

#include <stdio.h>
#include "Arduino.h"

using namespace std;


void newMessage(String message);
int checkForMessage(byte progNum);
	
void readMail(byte progNum, char *buffer, int size);


#endif /* Mail_hpp */

