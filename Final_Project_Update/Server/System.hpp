/**
 * @file System.hpp
 * @author Mitchell M. Gresham
 * @brief Abstract class which has methods that are used for interaction between the system, as in the console. And other methods used 
 *        for formatting data in ways which the system understands. 
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream>
#include <string>

using namespace std;

class System {
    public:
        static void println(string message)
        {
            cout << message << endl;
        }
        static void print(string message)
        {
            cout << message;
        }
        static string getInput()
        {
            string standardInput;
            getline(cin, standardInput);
            return standardInput;
        }
        static string ctos(char* charArray, int size)
        {
            string returnString = "";
            for (int i = 0; i < size; i++) {
                if (((int) charArray[i]) <= 127 && ((int) charArray[i]) >= 0)
                {
                    returnString += charArray[i];
                }
            }
            return returnString;
        }
};
#endif // __SYSTEM_H__