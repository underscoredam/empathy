//
// Created by damo on 2/7/16.
//

/*
 * The function file_read is from the OpenGL Programming wikibook: http://en.wikibooks.org/wiki/OpenGL_Programming
 *
 * */

#ifndef EMPATHY_FILE_UTILS_H
#define EMPATHY_FILE_UTILS_H

#include <iostream>
#include <vector>

char* file_read(const char* filename);
std::vector<std::string> file_readlines(const char* filename);
#endif //EMPATHY_FILE_UTILS_H
