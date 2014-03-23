//
//  main.cpp
//  mom
//
//  Created by Andrew Lovett-Barron on 3/23/14.
//  Copyright (c) 2014 decayio. All rights reserved.
//

#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <dirent.h>

using namespace std;

static char * mom_check_home_dir() {
    char *homeDir = getenv("HOME");
    return homeDir;
}

static int listdir(char *dir) {
    struct dirent *dp;
    DIR *fd;
    int count =0;
    cout << dir << endl;
    
    if ((fd = opendir(dir)) == NULL) {
        fprintf(stderr, "listdir: can't open %s\n", dir);
        return -1;
    }
    while ((dp = readdir(fd)) != NULL) {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
            continue;    /* skip self and parent */
        printf("%s/%s\n", dir, dp->d_name);
        count++;
    }
    closedir(fd);
    return count;
}


static char * mom_get_downloads_dir() {
    const char* homedir = mom_check_home_dir();
    const char* downloaddir = "/Downloads";
    char* dir = new char[sizeof(homedir)+sizeof(downloaddir)+1];//malloc(sizeof(homedir)+sizeof(downloaddir)+1);
    strcpy(dir, homedir);
    strcat(dir,downloaddir);
    free(dir);
    return dir;
}

static const int mom_check_if_downloads_is_messy() {
    const char * dir = mom_get_downloads_dir();
    const int count = listdir((char*)dir);

    return count;
}

int main(int argc, const char * argv[])
{
    int whatMomThinksIsMessy = 100;
    cout << mom_check_home_dir() << endl;;
    if(mom_check_if_downloads_is_messy() > whatMomThinksIsMessy) {
        const char * downloadDir = mom_get_downloads_dir();
        char * momKnowsBest = new char[sizeof(downloadDir)+5+1];
        strcat(momKnowsBest,"open ");
        momKnowsBest = strcat(momKnowsBest, downloadDir);
        
        char * cleanup = " && mkdir !!!_CLEAN_THIS_UP";
        char * orders = new char[sizeof(downloadDir) + 3 + sizeof(cleanup) + 1];
        
        strcat(orders,"cd ");
        strcat(orders,downloadDir);
        strcat(orders,cleanup);
        
        system(momKnowsBest);
        system(orders);
    }
    
    
    
    return 0;
}

